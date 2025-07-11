#include "operator_filter_edge_sobel_maximal.hpp"
#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"

/**
 * @brief
 */
Operator_filter_edge_sobel_maximal::~Operator_filter_edge_sobel_maximal() = default;

/**
 * orientation:
 *      0 = [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]
 *     90 = [1, 2, 1],  [0, 0, 0],  [-1, -2, -1]
 * references:
 * https://homepages.inf.ed.ac.uk/rbf/HIPR2/sobel.htm
 * https://en.wikipedia.org/wiki/Sobel_operator
 * https://en.wikipedia.org/wiki/Separable_filter
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_edge_sobel_maximal::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                             std::vector<Data_source_descriptor *> &output_data_stores,
                                             String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                             Errors &errors) {
    if (input_data_sources.size() != 1)
        errors.add("Operator_filter_edge_sobel_maximal::run", "", "one input data source required");
    if (output_data_stores.empty())
        errors.add("Operator_filter_edge_sobel_maximal::run", "", "output data source required");
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources[0];
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_filter_edge_sobel_maximal::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_filter_edge_sobel_maximal::run", errors);
        if (!errors.has_error()) {
            std::unique_ptr<Image> output_image(input_image->sobel_maximal(errors));
            if (!errors.has_error()) {
                for (Data_source_descriptor *output_data_store: output_data_stores)
                    output_data_store->write_operator_image(output_image.get(),
                                                            "Operator_filter_edge_sobel_maximal::run", errors);
                if (!errors.has_error())
                    output_image->log(log_entries);
            }
        }
    }
}
