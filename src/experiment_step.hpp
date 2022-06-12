//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_EXPERIMENT_STEP_HPP_
#define CV_WORKBENCH_SRC_EXPERIMENT_STEP_HPP_

#include <map>
#include <string>
#include <json-c/json.h>
#include "wb_enums.hpp"
#include "errors.hpp"
#include "image.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "data_source_descriptor.hpp"

class Experiment_step {
 public:
  int id;
  string step_operator;
  list<Data_source_descriptor *> input_data_sources;
  list<Data_source_descriptor *> output_data_stores;
  map<string, string> Operator_parameters;
  ~Experiment_step();
  Experiment_step();
  Experiment_step(int m_id, string m_step_operator);
  void run();
/**
 * Parse experiment json
 * @param jobj  json-c parsed json
 * @param errors experiment parse errors
 */
  static Experiment_step *json_parse(json_object *json_step, Errors &errors);
};

#endif //CV_WORKBENCH_SRC_EXPERIMENT_STEP_HPP_
