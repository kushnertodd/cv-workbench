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
        Kernel *color_kernel_row_ptr = nullptr;
        Kernel *color_kernel_col_ptr = nullptr;
        if (extent_str == "adjacent") {
            pixel_32F coeffs_32F_row[] = {1, 0, -1};
            color_kernel_row_ptr = Kernel::create_32F(3, 1, coeffs_32F_row);
            pixel_32F coeffs_32F_col[] = {0.25, 0.5, 0.25};
            color_kernel_col_ptr = Kernel::create_32F(1, 3, coeffs_32F_col);
        } else if (extent_str == "0") {
            pixel_32F coeffs_32F_row[] = {0.25, 0.5, 0.25};
            color_kernel_row_ptr = Kernel::create_32F(3, 1, coeffs_32F_row);
            // this is reversed from the separable filter reference
            pixel_32F coeffs_32F_col[] = {-1, 0, 1};
            color_kernel_col_ptr = Kernel::create_32F(1, 3, coeffs_32F_col);
        }
        std::unique_ptr<Kernel> color_kernel_row(color_kernel_row_ptr);
        std::unique_ptr<Kernel> color_kernel_col(color_kernel_col_ptr);
        Image *output1_ptr = color_kernel_row->convolve_numeric(input.get(), errors);
        std::unique_ptr<Image> output1(output1_ptr);
        Image *output2_ptr = nullptr;
        if (!errors.has_error() && output1_ptr != nullptr)
            output2_ptr = color_kernel_col->convolve_numeric(output1.get(), errors);
        std::unique_ptr<Image> output2(output2_ptr);
        if (!errors.has_error() && output2_ptr != nullptr)

            for (Data_source_descriptor *output_data_store: output_data_stores)
                output_data_store->write_operator_image(output2.get(), "Operator_filter_edge_color::run", errors);
        if (!errors.has_error() && output2_ptr != nullptr)
            output2->log(log_entries);
    }
}
