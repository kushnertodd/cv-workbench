//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_EXPERIMENT_HPP_
#define CV_WORKBENCH_SRC_EXPERIMENT_HPP_

#include <list>
#include <string>
#include <json-c/json.h>
#include "wb_defs.hpp"
#include "errors.hpp"
#include "image.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "experiment_step.hpp"
#include "wb_json_utils.hpp"

class Experiment {
 public:
  std::list<Experiment_step *> experiment_steps;
  std::string path{};
  virtual ~Experiment();
  Experiment();
  explicit Experiment(std::string m_path);
  /**
  * Parse experiment json
  * @param jobj  json-c parsed json
  * @param errors experiment parse errors
  */
  static Experiment *from_json(json_object *jobj, std::string path, Errors &errors);
  static void log_experiment(json_object *json_experiment);
  void run(Errors &errors);
};

#endif //CV_WORKBENCH_SRC_EXPERIMENT_HPP_
