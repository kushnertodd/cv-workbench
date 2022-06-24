//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_KIRSCH_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_KIRSCH_HPP_

#include "wb_defs.hpp"
#include "operator.hpp"

using namespace std;

class Operator_filter_edge_kirsch : public Operator {
 public:
  Operator_filter_edge_kirsch();
  void run(list<Data_source_descriptor *> &input_data_sources,
           list<Data_source_descriptor *> &output_data_stores,
           String_map &operator_parameters,
           Errors &errors);
};

#endif //CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_KIRSCH_HPP_
