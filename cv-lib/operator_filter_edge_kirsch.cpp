#include "operator_filter_edge_kirsch.hpp"
#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"

/**
 * @brief
 */
Operator_filter_edge_kirsch::~Operator_filter_edge_kirsch() = default;

/**
 * orientation:
 *     N = [-3, -3, 5], [-3, 0, 5], [-3, -3, 5]
 *    NW = [-3, 5, 5], [-3, 0, 5], [-3, -3, -3]
 *    W = [5, 5, 5], [-3, 0, -3], [-3, -3, -3]
 *    SW = [5, 5, -3], [5, 0, -3], [-3, -3, -3]
 *    S = [5, -3, -3], [5, 0, -3], [5, -3, -3]
 *    SE = [-3, -3, -3], [5, 0, -3], [5, 5, -3]
 *    E = [-3, -3, -3], [-3, 0, -3], [5, 5, 5]
 *    NE = [-3, -3, -3], [-3, 0, 5], [-3, 5, 5]
 * references:
 * https://en.wikipedia.org/wiki/Kirsch_operator
 * https://www.tutorialspoint.com/dip/krisch_compass_mask.htm
 *
 * @param input_data_sources input binary or jpeg image
 * @param output_data_stores output binary, jpeg, or test images
 * @param operator_parameters parameters
 * @param errors any run errors
 */
void Operator_filter_edge_kirsch::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                      std::vector<Data_source_descriptor *> &output_data_stores,
                                      String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                      Errors &errors) {
    if (input_data_sources.size() != 1)
        errors.add("Operator_filter_edge_kirsch::run", "", "one input data source required");
    if (output_data_stores.empty())
        errors.add("Operator_filter_edge_kirsch::run", "", "output data sources required");
    std::string orientation_str{};
    bool have_orientation = Operator_utils::get_string_parameter(
            "Operator_filter_edge_kirsch::run", operator_parameters, "orientation", orientation_str, errors);
    if (have_orientation && !wb_utils::string_in_list(orientation_str, {"E", "N", "NE", "NW", "S", "SE", "SW", "W"}))
        errors.add("Operator_filter_edge_kirsch::run", "", "orientation not E, N, NE, NW, S, SE, SW, or W");
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources.front();
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_filter_edge_kirsch::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_filter_edge_kirsch::run", errors);
        if (!errors.has_error()) {
            Kernel *kirsch_kernel_ptr = nullptr;
            if (orientation_str == "N") {
                //      N = [-3, -3, 5], [-3, 0, 5], [-3, -3, 5]
                int coeffs_32S[] = {-3, -3, 5, -3, 0, 5, -3, -3, 5};
                kirsch_kernel_ptr = Kernel::create_32S(3, 3, coeffs_32S);
            } else if (orientation_str == "NW") {
                //      NW = [-3, 5, 5], [-3, 0, 5], [-3, -3, -3]
                int coeffs_32S[] = {-3, 5, 5, -3, 0, 5, -3, -3, -3};
                kirsch_kernel_ptr = Kernel::create_32S(3, 3, coeffs_32S);
            } else if (orientation_str == "W") {
                //      W = [5, 5, 5], [-3, 0, -3], [-3, -3, -3]
                int coeffs_32S[] = {5, 5, 5, -3, 0, -3, -3, -3, -3};
                kirsch_kernel_ptr = Kernel::create_32S(3, 3, coeffs_32S);
            } else if (orientation_str == "SW") {
                //      SW = [5, 5, -3], [5, 0, -3], [-3, -3, -3]
                int coeffs_32S[] = {5, 5, -3, 5, 0, -3, -3, -3, -3};
                kirsch_kernel_ptr = Kernel::create_32S(3, 3, coeffs_32S);
            } else if (orientation_str == "S") {
                //      S = [5, -3, -3], [5, 0, -3], [5, -3, -3]
                int coeffs_32S[] = {5, -3, -3, 5, 0, -3, 5, -3, -3};
                kirsch_kernel_ptr = Kernel::create_32S(3, 3, coeffs_32S);
            } else if (orientation_str == "SE") {
                //      SE = [-3, -3, -3], [5, 0, -3], [5, 5, -3]
                int coeffs_32S[] = {-3, -3, -3, 5, 0, -3, 5, 5, -3};
                kirsch_kernel_ptr = Kernel::create_32S(3, 3, coeffs_32S);
            } else if (orientation_str == "E") {
                //      E = [-3, -3, -3], [-3, 0, -3], [5, 5, 5]
                int coeffs_32S[] = {-3, -3, -3, -3, 0, -3, 5, 5, 5};
                kirsch_kernel_ptr = Kernel::create_32S(3, 3, coeffs_32S);
            } else if (orientation_str == "NE") {
                //      NE = [-3, -3, -3], [-3, 0, 5], [-3, 5, 5]
                int coeffs_32S[] = {-3, -3, -3, -3, 0, 5, -3, 5, 5};
                kirsch_kernel_ptr = Kernel::create_32S(3, 3, coeffs_32S);
            }
            std::unique_ptr<Kernel> kirsch_kernel(kirsch_kernel_ptr);
            std::unique_ptr<Image> output_image(kirsch_kernel->convolve_numeric(input_image.get(), errors));
            if (!errors.has_error())
                for (Data_source_descriptor *output_data_store: output_data_stores)
                    output_data_store->write_operator_image(output_image.get(), "Operator_filter_edge_kirsch::run",
                                                            errors);
            if (!errors.has_error())
                output_image->log(log_entries);
        }
    }
}
