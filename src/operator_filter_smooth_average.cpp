//
// Created by kushn on 7/23/2022.
//

#include "operator_filter_smooth_average.hpp"

Operator_filter_smooth_average::~Operator_filter_smooth_average() = default;
void Operator_filter_smooth_average::run(std::list<Data_source_descriptor *> &input_data_sources,
                                         std::list<Data_source_descriptor *> &output_data_stores,
                                         String_map &operator_parameters,
                                         std::list<WB_log_entry> &log_entries,
                                         Errors &errors) {
  errors.add("", "", "Operator filter_smooth_average not yet implemented");
}
