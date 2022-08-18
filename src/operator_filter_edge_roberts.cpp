//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_edge_roberts.hpp"

//

extern bool debug;

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
  if (output_data_stores.size() > 1)
    errors.add("Operator_filter_edge_roberts::run", "", "too many output data sources");
  if (!Operator_utils::has_parameter(operator_parameters, "orientation"))
    errors.add("Operator_filter_edge_roberts::run", "", "orientation parameter required");
  std::string orientation_str;
  if (!errors.has_error()) {
    orientation_str = Operator_utils::get_parameter(operator_parameters, "orientation");
    if (orientation_str != "0" && orientation_str != "90")
      errors.add("Operator_filter_edge_roberts::run", "", "orientation parameter not 0 or 90");
  }
  Data_source_descriptor *input_data_source = input_data_sources.front();
  Data_source_descriptor *output_data_store = output_data_stores.front();
  if (output_data_store->data_format != WB_data_format::Data_format::BINARY)
    errors.add("Operator_filter_edge_roberts::run", "", "only binary output data format supported");
  Image *input = nullptr;
  if (!errors.has_error()) {
    if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
      input = input_data_source->read_image_jpeg(errors);
    else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
      input = input_data_source->read_image(errors);
    else
      errors.add("Operator_filter_edge_roberts::run", "", "invalid data format: " +
          WB_data_format::to_string(input_data_source->data_format));
  }
  if (!errors.has_error() && input != nullptr)
    input->check_grayscale(errors);
  if (!errors.has_error() && input != nullptr) {
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
    Image *output = roberts_kernel->convolve_numeric(input, errors);
    if (!errors.has_error() && output != nullptr)
      Operator_utils::write_operator_image(output_data_store, output, "Operator_filter_edge_roberts::run", errors);
    if (!errors.has_error() && output != nullptr) {
      output->log(log_entries);
    }
    delete output;
  }
  delete input;
}
