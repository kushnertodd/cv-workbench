//
// Created by kushn on 7/23/2022.
//

#include "operator_transform_image_morphology.hpp"

Operator_filter_image_morphology::~Operator_filter_image_morphology() = default;
void Operator_filter_image_morphology::run(std::list<Data_source_descriptor *> &input_data_sources,
                                           std::list<Data_source_descriptor *> &output_data_stores,
                                           String_map &operator_parameters,
                                           std::list<WB_log_entry> &log_entries,
                                           Errors &errors) {
  errors.add("", "", "Operator transform_image_morphology not yet implemented");
}
