#include "operator_filter_edge_roberts.hpp"
#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"

/**
 * @brief
 */
Operator_filter_edge_roberts::~Operator_filter_edge_roberts() = default;

/**
 * orientation:
 *      0 = [0, 1], [-1, 0]
 *     90 = [1, 0],  [0, -1]
 * references:
 * https://en.wikipedia.org/wiki/Roberts_cross
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_edge_roberts::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                       std::vector<Data_source_descriptor *> &output_data_stores,
                                       String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                       Errors &errors) {
    if (input_data_sources.size() != 1)
        errors.add("Operator_filter_edge_roberts::run", "", "one input data source required");
    if (output_data_stores.empty())
        errors.add("Operator_filter_edge_roberts::run", "", "output data source required");
    std::string orientation_str;
    bool have_orientation = Operator_utils::get_string_parameter(
            "Operator_filter_edge_roberts::run", operator_parameters, "orientation", orientation_str, errors);
    if (have_orientation && orientation_str != "0" && orientation_str != "90")

        errors.add("Operator_filter_edge_roberts::run", "", "orientation not 0 or 90");
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources[0];
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_filter_edge_roberts::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_filter_edge_roberts::run", errors);
        if (!errors.has_error()) {
            Kernel *roberts_kernel_ptr = nullptr;
            if (orientation_str == "0") {
                //     0 = [0, 1], [-1, 0]
                int coeffs_32S[] = {0, 1, -1, 0};
                roberts_kernel_ptr = Kernel::create_32S(2, 2, coeffs_32S);
            } else if (orientation_str == "90") {
                //     90 = [1, 0],  [0, -1]
                int coeffs_32S[] = {1, 0, 0, -1};
                roberts_kernel_ptr = Kernel::create_32S(2, 2, coeffs_32S);
            }
            std::unique_ptr<Kernel> roberts_kernel(roberts_kernel_ptr);
            std::unique_ptr<Image> output_image(roberts_kernel->convolve_numeric(input_image.get(), errors));
            if (!errors.has_error())
                for (Data_source_descriptor *output_data_store: output_data_stores)
                    output_data_store->write_operator_image(output_image.get(), "Operator_filter_edge_roberts::run",
                                                            errors);
            if (!errors.has_error())
                output_image->log(log_entries);
        }
    }
}
