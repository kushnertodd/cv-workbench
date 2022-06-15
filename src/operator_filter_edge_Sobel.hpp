//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_SOBEL_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_SOBEL_HPP_

#include "operator.hpp"

using namespace std;

class Operator_filter_edge_sobel : public Operator {
 public:
  Operator_filter_edge_sobel();
  void run(list<Data_source_descriptor *> &input_data_sources,
           list<Data_source_descriptor *> &output_data_stores,
           map<string, string> &operator_parameters,
           Errors &errors);
};

#endif //CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_SOBEL_HPP_
