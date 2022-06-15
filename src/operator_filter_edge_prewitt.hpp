//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_PREWITT_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_PREWITT_HPP_

#include "operator.hpp"

using namespace std;

class Operator_filter_edge_prewitt : public Operator {
 public:
  Operator_filter_edge_prewitt();
  void run(list<Data_source_descriptor *> &input_data_sources,
           list<Data_source_descriptor *> &output_data_stores,
           map<string, string> operator_parameters,
           Errors &errors);
};

#endif //CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_PREWITT_HPP_
