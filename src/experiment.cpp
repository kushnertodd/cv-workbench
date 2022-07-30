//
// Created by kushn on 6/11/2022.
//

#include "experiment.hpp"

Experiment::~Experiment() {
  for (Experiment_step *step: experiment_steps) {
    delete step;
  }
}
Experiment::Experiment() = default;

Experiment::Experiment(json_object *m_jobj) :
jobj(m_jobj) {}

/**
* Parse experiment json
* @param jobj  json-cR parsed json
* @param errors experiment parse errors
*/
Experiment *Experiment::from_json(json_object *jobj, Errors &errors) {
  // parse: ' "experiment": { ... `
  auto *experiment = new Experiment(jobj);
  json_object *json_experiment =
      get_json_object("Experiment::from_json", jobj, "experiment", json_type_object, errors);
  if (json_experiment != nullptr) {
    // parse: ' "steps": [ ... '
    json_object
        *json_steps = get_json_object("Experiment::from_json", json_experiment, "steps", json_type_array, errors);
    if (json_steps != nullptr) {
      size_t nsteps = json_object_array_length(json_steps);
      for (int i = 0; i < nsteps; i++) {
        json_object *json_step = json_object_array_get_idx(json_steps, i);
        if (error_check_type("Experiment::from_json", "step", json_step, json_type_object, errors)) {
          Experiment_step *experiment_step = Experiment_step::from_json(json_step, errors);
          if (experiment_step != nullptr) {
            experiment->experiment_steps.push_back(experiment_step);
          }
        }
      }
    }
  }
  return experiment;
}

void Experiment::run(Errors &errors) {
  for (Experiment_step *step: experiment_steps) {
    step->run(errors);
  }
}

