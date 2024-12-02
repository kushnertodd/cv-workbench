//
// Created by kushn on 7/13/2022.
//

#ifndef SRC__OPERATOR_HOUGH_ACCUMULATOR_CREATE_HPP_
#define SRC__OPERATOR_HOUGH_ACCUMULATOR_CREATE_HPP_

#include "wb_defs.hpp"
#include "operator.hpp"

class Operator_histogram_image_create : public Operator {
 public:
  void run(std::list<Data_source_descriptor *> &input_data_sources,
           std::list<Data_source_descriptor *> &output_data_stores,
           String_map &operator_parameters,
           std::list<WB_log_entry> &log_entries,
           Errors &errors) override;
};

#endif //SRC__OPERATOR_HOUGH_ACCUMULATOR_CREATE_HPP_
