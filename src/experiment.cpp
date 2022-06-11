//
// Created by kushn on 6/11/2022.
//

#include "experiment.hpp"

Experiment::Experiment() {}
/**
* Parse experiment json
* @param jobj  json-c parsed json
* @param errors experiment parse errors
*/
Experiment *Experiment::json_parse(json_object *jobj, Errors &errors) {
  // parse: ' "experiment": { ... `
  Experiment *experiment = new Experiment();
  json_object *json_experiment =
      get_json_object("Experiment::json_parse", jobj, "experiment", json_type_object, errors);
  if (json_experiment != nullptr) {
    // parse: ' "steps": [ ... '
    json_object
        *json_steps = get_json_object("Experiment::json_parse", json_experiment, "steps", json_type_array, errors);
    if (json_steps != nullptr) {
      int nsteps = json_object_array_length(json_steps);
      for (int i = 0; i < nsteps; i++) {
        json_object *json_step = json_object_array_get_idx(json_steps, i);
        if (error_check_type("Experiment::json_parse", "step", json_step, json_type_object, errors)) {
          Experiment_step *experiment_step = Experiment_step::json_parse(json_step, errors);
          if (experiment_step != nullptr) {
            experiment->experiment_steps.push_back(experiment_step);
          }
        }
      }
    }
  }
  return experiment;
}

