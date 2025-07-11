#ifndef CV_WORKBENCH_SRC_EXPERIMENT_HPP_
#define CV_WORKBENCH_SRC_EXPERIMENT_HPP_

#include <json-c/json.h>
#include <string>
#include <vector>
#include "errors.hpp"
#include "experiment_step.hpp"
#include "histogram.hpp"
#include "wb_json_utils.hpp"

class Experiment {
    std::vector<Experiment_step *> experiment_steps;
    std::string path{};

public:
    virtual ~Experiment();
    Experiment();
    explicit Experiment(std::string m_path);
    static std::unique_ptr<Experiment> from_json(json_object *jobj, std::string path, Errors &errors);
    static void log_experiment(json_object *json_experiment);
    void run(Errors &errors);
};

#endif // CV_WORKBENCH_SRC_EXPERIMENT_HPP_
