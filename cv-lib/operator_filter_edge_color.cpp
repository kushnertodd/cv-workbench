//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_edge_color.hpp"

//

Operator_filter_edge_color::~Operator_filter_edge_color() = default;

/**
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_edge_color::run(std::list<Data_source_descriptor *> &input_data_sources,
                                     std::list<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters,
                                     std::list<WB_log_entry> &log_entries,
                                     Errors &errors) {
    if (input_data_sources.empty())
        errors.add("Operator_filter_edge_color::run", "", "input data source required");
    if (input_data_sources.size() > 1)
        errors.add("Operator_filter_edge_color::run", "", "too many input data sources");
    if (output_data_stores.empty())
        errors.add("Operator_filter_edge_color::run", "", "output data source required");
    std::string extent_str;
    bool extent_missing = Operator_utils::get_string_parameter("Operator_filter_edge_color::run",
                                                               operator_parameters,
                                                               "extent",
                                                               extent_str, errors);
    if (extent_missing)
        extent_str = "adjacent";
    Data_source_descriptor *input_data_source = input_data_sources.front();
    Image *input_ptr = nullptr;
    if (!errors.has_error())
        input_ptr = input_data_source->read_operator_image("Operator_filter_edge_color::run", errors);
    std::unique_ptr<Image> input(input_ptr);
    if (!errors.has_error() && input_ptr != nullptr)
        input->check_color("Operator_filter_edge_color::run", errors);
    if (!errors.has_error() && input_ptr != nullptr) {
        Image *output_ptr = input_ptr->color_edge(errors);
        std::unique_ptr<Image> output(output_ptr);

        if (!errors.has_error() && output_ptr != nullptr)
            for (Data_source_descriptor *output_data_store: output_data_stores)
                output_data_store->write_operator_image(output.get(), "Operator_filter_edge_color::run", errors);
        if (!errors.has_error() && output_ptr != nullptr)
            output_ptr->log(log_entries);
    }
}
