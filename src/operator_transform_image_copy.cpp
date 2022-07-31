//
// Created by kushn on 7/23/2022.
//

#include "operator_transform_image_copy.hpp"

Operator_transform_image_copy::~Operator_transform_image_copy() = default;
void Operator_transform_image_copy::run(std::list<Data_source_descriptor *> &input_data_sources,
                                        std::list<Data_source_descriptor *> &output_data_stores,
                                        String_map &operator_parameters,
                                        std::list<WB_log_entry> &log_entries,
                                        Errors &errors) {
  errors.add("", "", "Operator transform_image_copy not yet implemented");
}
