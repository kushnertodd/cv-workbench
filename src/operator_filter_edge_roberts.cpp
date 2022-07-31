//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
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

  if (debug) {
    std::cout << "Operator_filter_edge_roberts::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_filter_edge_roberts::run", "", "missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_roberts::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_filter_edge_roberts::run", "", "missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_filter_edge_roberts::run", "", "too many output data sources");
  else {
    if (!Operator_utils::has_parameter(operator_parameters, "orientation")) {
      errors.add("Operator_filter_edge_roberts::run", "", "missing 'orientation' parameter");
    } else {
      std::string orientation_str = Operator_utils::get_parameter(operator_parameters, "orientation");
      if (orientation_str != "0" && orientation_str != "90") {
        errors.add("Operator_filter_edge_roberts::run", "", "invalid 'orientation' parameter not 0 or 90");
      } else {
        Kernel *roberts_kernel = nullptr;
        if (orientation_str == "0") {
          //     0 = [0, 1], [-1, 0]
          int coeffs_32S[] = {0, 1, -1, 0};
          roberts_kernel = Kernel::create_32S(2, 2, coeffs_32S);
        } else if (orientation_str == "90") {
          //     90 = [1, 0],  [0, -1]
          int coeffs_32S[] = {1, 0, 0, -1};
          roberts_kernel = Kernel::create_32S(2, 2, coeffs_32S);
        }
        Data_source_descriptor *input_data_source = input_data_sources.front();
        Data_source_descriptor *output_data_store = output_data_stores.front();
        Image *input = nullptr;
        Image *output = nullptr;
        if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
          input = input_data_source->read_image_jpeg(errors);
        else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
          input = input_data_source->read_image(errors);
        else
          errors.add("Operator_filter_edge_roberts::run", "", "invalid data format: " +
              WB_data_format::to_string(input_data_source->data_format));
        if (errors.error_ct == 0 && input != nullptr)
          input->check_grayscale(errors);
        if (errors.error_ct == 0 && roberts_kernel != nullptr) {
          output = roberts_kernel->convolve(input);
          if (output_data_store->data_format == WB_data_format::Data_format::JPEG) {
            output_data_store->write_image_jpeg(output, errors);
          } else if (output_data_store->data_format == WB_data_format::Data_format::BINARY) {
            output_data_store->write_image(output, errors);
          } else {
            errors.add("Operator_filter_edge_roberts::run", "", "invalid data format '"
                + WB_data_format::to_string(output_data_store->data_format) + "'");
          }
        }
        if (!errors.has_error() && output != nullptr) {
          output->log(log_entries);
        }
      }
    }
  }
}
