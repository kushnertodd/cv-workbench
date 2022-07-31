//
// Created by kushn on 6/11/2022.
//

#include <cstdlib>
#include <utility>
#include "wb_version.hpp"
#include "experiment.hpp"

Experiment::~Experiment() {
  for (Experiment_step *step: experiment_steps) {
    delete step;
  }
}
Experiment::Experiment() = default;

Experiment::Experiment(json_object *m_jobj, std::string m_path) :
    jobj(m_jobj),
    path(std::move(m_path)) {}

/**
* Parse experiment json
* @param jobj  json-c parsed json
* @param errors experiment parse errors
*/
Experiment *Experiment::from_json(json_object *jobj, std::string path, Errors &errors) {
  // parse: ' "experiment": { ... `
  auto *experiment = new Experiment(jobj, std::move(path));
  json_object *json_experiment =
      get_json_object("Experiment::from_json", jobj, "experiment", json_type_object, errors);
  if (json_experiment != nullptr) {
    experiment->log_experiment(json_experiment);
    // parse: ' "steps": [ ... '
    json_object
        *json_experiment_steps =
        get_json_object("Experiment::from_json", json_experiment, "steps", json_type_array, errors);
    if (json_experiment_steps != nullptr) {
      size_t nsteps = json_object_array_length(json_experiment_steps);
      for (int i = 0; i < nsteps; i++) {
        json_object *json_experiment_step = json_object_array_get_idx(json_experiment_steps, i);
        if (error_check_type("Experiment::from_json", "step", json_experiment_step, json_type_object, errors)) {
          Experiment_step *experiment_step = Experiment_step::from_json(json_experiment_step, errors);
          if (experiment_step != nullptr) {
            experiment->experiment_steps.push_back(experiment_step);
          }
        }
      }
    }
  }
  return experiment;
}

void Experiment::log_experiment(json_object *json_experiment) const {
  json_object *run = json_object_new_object();
  json_object_object_add(run, "script-path", json_object_new_string(path.c_str()));
  json_object_object_add(run, "run-time", json_object_new_string(wb_utils::timestamp().c_str()));
  json_object_object_add(run, "username", json_object_new_string(std::getenv("USER")));
  json_object_object_add(run, "version", json_object_new_string(WB_version::version()));
  json_object_object_add(json_experiment, "run", run);
}

void Experiment::run(Errors &errors) {
  for (Experiment_step *step: experiment_steps) {
    step->run(errors);
  }
}

