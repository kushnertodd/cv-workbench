//
// Created by kushn on 7/23/2022.
//

#ifndef SRC__OPERATOR_TRANSFORM_IMAGE_COPY_HPP_
#define SRC__OPERATOR_TRANSFORM_IMAGE_COPY_HPP_

#include "operator.hpp"

class Operator_transform_image_copy : public Operator {
 public:
  ~Operator_transform_image_copy() override;
  void run(std::list<Data_source_descriptor *> &input_data_sources,
           std::list<Data_source_descriptor *> &output_data_stores,
           String_map &operator_parameters,
           std::list<WB_log_entry> &log_entries,
           Errors &errors) override;

};

#endif //SRC__OPERATOR_TRANSFORM_IMAGE_COPY_HPP_
