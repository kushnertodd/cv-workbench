//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_edge_kirsch.hpp"

//

extern bool debug;

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
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_edge_kirsch::run(std::list<Data_source_descriptor *> &input_data_sources,
                                      std::list<Data_source_descriptor *> &output_data_stores,
                                      String_map &operator_parameters,
                                      std::list<WB_log_entry> &log_entries,
                                      Errors &errors) {
  if (input_data_sources.empty())
    errors.add("Operator_filter_edge_kirsch::run", "", "input data source required");
  if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_kirsch::run", "", "too many input data sources");
  if (output_data_stores.empty())
    errors.add("Operator_filter_edge_kirsch::run", "", "output data source required");
  if (output_data_stores.size() > 1)
    errors.add("Operator_filter_edge_kirsch::run", "", "too many output data sources");
  if (!Operator_utils::has_parameter(operator_parameters, "orientation"))
    errors.add("Operator_filter_edge_kirsch::run", "", "missing orientation parameter");
  std::string orientation_str;
  if (!errors.has_error()) {
    orientation_str = Operator_utils::get_parameter(operator_parameters, "orientation");
    if (orientation_str != "N"
        && orientation_str != "NW"
        && orientation_str != "W"
        && orientation_str != "SW"
        && orientation_str != "S"
        && orientation_str != "SE"
        && orientation_str != "E"
        && orientation_str != "NE")
      errors.add("Operator_filter_edge_kirsch",
                 "",
                 "orientation parameter not E, N, NE, NW, S, SE, SW, or W");
  }
  Data_source_descriptor *input_data_source = input_data_sources.front();
  Data_source_descriptor *output_data_store = output_data_stores.front();
  if (output_data_store->data_format != WB_data_format::Data_format::BINARY)
    errors.add("Operator_filter_edge_kirsch::run", "", "only binary output data format supported");
  Image *input = nullptr;
  if (!errors.has_error()) {
    if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
      input = input_data_source->read_image_jpeg(errors);
    else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
      input = input_data_source->read_image(errors);
    else
      errors.add("Operator_filter_edge_kirsch::run", "", "input data format must be jpeg or binary, not " +
          WB_data_format::to_string(input_data_source->data_format));
  }
  if (!errors.has_error() && input != nullptr)
    input->check_grayscale(errors);
  if (!errors.has_error() && input != nullptr) {
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
    Image *output = kirsch_kernel->convolve_numeric(input, errors);
    if (!errors.has_error() && output != nullptr)
      output_data_store->write_image(output, errors);
    if (!errors.has_error() && output != nullptr)
      output->log(log_entries);
    delete output;
  }
  delete input;
}
