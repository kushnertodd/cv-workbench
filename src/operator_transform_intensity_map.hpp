//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_INTENSITY_MAP_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_INTENSITY_MAP_HPP_

#include "operator.hpp"

using namespace std;

class Operator_transform_intensity_map : public Operator {
 public:
  Operator_transform_intensity_map();
  void run(list<Data_source_descriptor *> &input_data_sources,
           list<Data_source_descriptor *> &output_data_stores,
           String_map &operator_parameters,
           Errors &errors);
};

#endif //CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_INTENSITY_MAP_HPP_