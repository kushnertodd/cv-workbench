//
// Created by kushn on 7/23/2022.
//

#ifndef CV_WORKBENCH_SRC__OPERATOR_FILTER_EDGE_LINEAR_HPP_
#define CV_WORKBENCH_SRC__OPERATOR_FILTER_EDGE_LINEAR_HPP_

#include "operator.hpp"

/**
 * Linear edge operator
 */
class Operator_filter_edge_linear : public Operator {
 public:
  ~Operator_filter_edge_linear() override;
  void run(std::list<Data_source_descriptor *> &input_data_sources,
           std::list<Data_source_descriptor *> &output_data_stores,
           String_map &operator_parameters,
           std::list<WB_log_entry> &log_entries,
           Errors &errors) override;

};

#endif //CV_WORKBENCH_SRC__OPERATOR_FILTER_EDGE_LINEAR_HPP_
