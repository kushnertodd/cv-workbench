//
// Created by kushn on 7/23/2022.
//

#ifndef SRC__OPERATOR_FILTER_SMOOTH_MEDIAN_HPP_
#define SRC__OPERATOR_FILTER_SMOOTH_MEDIAN_HPP_

#include "operator.hpp"

class Operator_filter_smooth_median : public Operator {
 public:
  ~Operator_filter_smooth_median() override;
  void run(std::list<Data_source_descriptor *> &input_data_sources,
           std::list<Data_source_descriptor *> &output_data_stores,
           String_map &operator_parameters,
           std::list<WB_log_entry> &log_entries,
           Errors &errors) override;

};

#endif //SRC__OPERATOR_FILTER_SMOOTH_MEDIAN_HPP_
