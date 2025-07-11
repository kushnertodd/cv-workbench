#include "experiment.hpp"
#include <utility>
#include "runtime.hpp"

/**
 * @brief
 */
Experiment::~Experiment() {
    for (Experiment_step *step: experiment_steps) {
        delete step;
    }
}
/**
 * @brief
 */
Experiment::Experiment() = default;
/**
 * @brief
 * @param m_path
 */
Experiment::Experiment(std::string m_path) : path(std::move(m_path)) {}
/**
 * Parse experiment json
 * @param jobj  json-c parsed json
 * @param errors experiment parse errors
 */
std::unique_ptr<Experiment> Experiment::from_json(json_object *jobj, std::string path, Errors &errors) {
    // parse: ' "experiment": { ... `
    std::unique_ptr<Experiment> experiment = std::make_unique<Experiment>(std::move(path));
    json_object *json_experiment =
            get_json_object("Experiment::from_json", jobj, "experiment", json_type_object, errors);
    if (json_experiment != nullptr) {
        log_experiment(json_experiment);
        // parse: ' "steps": [ ... '
        json_object *json_experiment_steps =
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
/**
 * @brief
 * @param json_experiment
 */
void Experiment::log_experiment(json_object *json_experiment) {
    json_object *run = Runtime::to_log();
    json_object_object_add(json_experiment, "run", run);
}
/**
 * @brief
 * @param errors
 */
void Experiment::run(Errors &errors) {
    for (Experiment_step *step: experiment_steps) {
        step->run(errors);
    }
}
