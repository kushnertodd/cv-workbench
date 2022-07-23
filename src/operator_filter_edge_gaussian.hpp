//
// Created by kushn on 7/23/2022.
//

#ifndef SRC__OPERATOR_FILTER_EDGE_GAUSSIAN_HPP_
#define SRC__OPERATOR_FILTER_EDGE_GAUSSIAN_HPP_

#include "operator.hpp"

class Operator_filter_edge_gaussian : public Operator {
 public:
  ~Operator_filter_edge_gaussian() override;
  void run(std::list<Data_source_descriptor *> &input_data_sources,
           std::list<Data_source_descriptor *> &output_data_stores,
           String_map &operator_parameters,
           Errors &errors) override;

};

#endif //SRC__OPERATOR_FILTER_EDGE_GAUSSIAN_HPP_
