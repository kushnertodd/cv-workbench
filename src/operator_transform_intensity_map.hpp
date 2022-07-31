//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_INTENSITY_MAP_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_INTENSITY_MAP_HPP_

#include "operator.hpp"

//

class Operator_transform_intensity_map : public Operator {
 public:
  void run(std::list<Data_source_descriptor *> &input_data_sources,
           std::list<Data_source_descriptor *> &output_data_stores,
           String_map &operator_parameters,
           std::list<WB_log_entry> &log_entries,
           Errors &errors) override;
};

#endif //CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_INTENSITY_MAP_HPP_
