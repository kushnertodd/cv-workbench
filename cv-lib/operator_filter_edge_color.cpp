#include "operator_filter_edge_color.hpp"
#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"

/**
 * @brief
 */
Operator_filter_edge_color::~Operator_filter_edge_color() = default;
/**
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_edge_color::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                     std::vector<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                     Errors &errors) {
    if (input_data_sources.size() != 1)
        errors.add("Operator_filter_edge_color::run", "", "one input data source required");
    if (output_data_stores.empty())
        errors.add("Operator_filter_edge_color::run", "", "output data sources required");
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources[0];
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_filter_edge_color::run", errors));
        if (!errors.has_error()) {
            input_image->check_color("Operator_filter_edge_color::run", errors);
            if (!errors.has_error()) {
                std::unique_ptr<Image> output_image(input_image->color_edge(errors));
                if (!errors.has_error())
                    for (Data_source_descriptor *output_data_store: output_data_stores)
                        output_data_store->write_operator_image(output_image.get(), "Operator_filter_edge_color::run",
                                                                errors);
                if (!errors.has_error())
                    output_image->log(log_entries);
            }
        }
    }
}
