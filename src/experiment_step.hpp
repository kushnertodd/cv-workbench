//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_EXPERIMENT_STEP_HPP_
#define CV_WORKBENCH_SRC_EXPERIMENT_STEP_HPP_

#include <map>
#include <string>
#include <json-c/json.h>
#include "wb_defs.hpp"
#include "errors.hpp"
#include "image.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "data_source_descriptor.hpp"
#include "wb_log.hpp"

class Experiment_step {
 public:
  int id;
  std::string operator_name;
  std::list<Data_source_descriptor *> input_data_sources;
  std::list<Data_source_descriptor *> output_data_stores;
  String_map operator_parameters;
  json_object *json_experiment_step;
  ~Experiment_step();
  Experiment_step();
  explicit Experiment_step(json_object *m_json_experiment_step);
  Experiment_step(int m_id, std::string m_operator_name);
  void log_experiment_step(const std::list<WB_log_entry> &log_entries, Errors &errors) const;
  void run(Errors &errors);
  std::string to_string();
/**
 * Parse experiment json
 * @param jobj  json-c parsed json
 * @param errors experiment parse errors
 */
  static Experiment_step *from_json(json_object *json_experiment_step, Errors &errors);
};

#endif //CV_WORKBENCH_SRC_EXPERIMENT_STEP_HPP_
