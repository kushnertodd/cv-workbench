//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_EXPERIMENT_HPP_
#define CV_WORKBENCH_SRC_EXPERIMENT_HPP_

#include <list>
#include <string>
#include <json-c/json.h>
#include "wb_enums.hpp"
#include "errors.hpp"
#include "image.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "experiment_step.hpp"
#include "wb_json_utils.hpp"

class Experiment {
 public:
  list<Experiment_step *> experiment_steps;
  Experiment();
  /**
  * Parse experiment json
  * @param jobj  json-c parsed json
  * @param errors experiment parse errors
  */
  static Experiment *json_parse(json_object *jobj, Errors &errors);
};

#endif //CV_WORKBENCH_SRC_EXPERIMENT_HPP_
