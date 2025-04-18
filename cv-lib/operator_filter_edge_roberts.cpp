//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_edge_roberts.hpp"

//

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
void Operator_filter_edge_roberts::run(std::list<Data_source_descriptor *> &input_data_sources,
                                       std::list<Data_source_descriptor *> &output_data_stores,
                                       String_map &operator_parameters,
                                       std::list<WB_log_entry> &log_entries,
                                       Errors &errors) {
  if (input_data_sources.empty())
    errors.add("Operator_filter_edge_roberts::run", "", "input data source required");
  if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_roberts::run", "", "too many input data sources");
  if (output_data_stores.empty())
    errors.add("Operator_filter_edge_roberts::run", "", "output data source required");
  std::string orientation_str;
  bool orientation_missing = Operator_utils::get_string_parameter("Operator_filter_edge_roberts::run",
                                                                  operator_parameters,
                                                                  "orientation",
                                                                  orientation_str, errors);
  if (!orientation_missing && orientation_str != "0" && orientation_str != "90")

    errors.add("Operator_filter_edge_roberts::run", "", "orientation not 0 or 90");
  Data_source_descriptor *input_data_source = input_data_sources.front();
  Image *input_ptr = nullptr;
  if (!errors.has_error())
    input_ptr = input_data_source->read_operator_image("Operator_filter_edge_roberts::run", errors);
  std::unique_ptr<Image> input(input_ptr);
  if (!errors.has_error() && input_ptr != nullptr)
    input->check_grayscale("Operator_filter_edge_roberts::run", errors);
  if (!errors.has_error() && input_ptr != nullptr) {
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
    Image *output_ptr = roberts_kernel->convolve_numeric(input.get(), errors);
    std::unique_ptr<Image> output(output_ptr);
    if (!errors.has_error() && output_ptr != nullptr)
      for (Data_source_descriptor *output_data_store: output_data_stores)
        output_data_store->write_operator_image(output.get(), "Operator_filter_edge_roberts::run", errors);
    if (!errors.has_error() && output_ptr != nullptr)
      output->log(log_entries);
  }
}
