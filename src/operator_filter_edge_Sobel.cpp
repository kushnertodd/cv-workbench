//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "operator_filter_edge_sobel.hpp"

//

extern bool debug;

Operator_filter_edge_sobel::~Operator_filter_edge_sobel() = default;

/**
 * orientation:
 *      0 = [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]
 *     90 = [1, 2, 1],  [0, 0, 0],  [-1, -2, -1]
 * references:
 * https://homepages.inf.ed.ac.uk/rbf/HIPR2/sobel.htm
 * https://en.wikipedia.org/wiki/Sobel_operator
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_edge_sobel::run(std::list<Data_source_descriptor *> &input_data_sources,
                                     std::list<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters,
                                     Errors &errors) {

  if (debug) {
    std::cout << "Operator_filter_edge_sobel::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_filter_edge_sobel::run", "", "missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_sobel::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_filter_edge_sobel::run", "", "missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_filter_edge_sobel::run", "", "too many output data sources");
  else {
    if (!Operator_utils::has_parameter(operator_parameters, "orientation")) {
      errors.add("Operator_filter_edge_sobel::run", "", "missing 'orientation' parameter");
    } else {
      std::string orientation_str = Operator_utils::get_parameter(operator_parameters, "orientation");
      if (orientation_str != "0" && orientation_str != "90") {
        errors.add("Operator_filter_edge_sobel::run", "", "invalid 'orientation' parameter not 0 or 90");
      } else {
        Kernel *sobel_kernel = nullptr;
        if (orientation_str == "0") {
          //      0 = [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]
          int coeffs_32S[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
          sobel_kernel = Kernel::create_32S(3, 3, coeffs_32S);
        } else if (orientation_str == "90") {
          //     90 = [1, 2, 1],  [0, 0, 0],  [-1, -2, -1]
          int coeffs_32S[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
          sobel_kernel = Kernel::create_32S(3, 3, coeffs_32S);
        }
        Data_source_descriptor *input_data_source = input_data_sources.front();
        Data_source_descriptor *output_data_store = output_data_stores.front();
        Image *input = nullptr;
        if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
          input = input_data_source->read_image_jpeg(errors);
        else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
          input = input_data_source->read_image(errors);
        else
          errors.add("Operator_filter_edge_sobel::run", "", "invalid data format: " +
              WB_data_format::to_string(input_data_source->data_format));
        if (errors.error_ct == 0 && input != nullptr)
          input->check_grayscale(errors);
        if (errors.error_ct == 0) {
          Image *output = sobel_kernel->convolve(input);
          if (output_data_store->data_format == WB_data_format::Data_format::JPEG) {
            output_data_store->write_image_jpeg(output, errors);
          } else if (output_data_store->data_format == WB_data_format::Data_format::BINARY) {
            output_data_store->write_image(output, errors);
          } else {
            errors.add("Operator_filter_edge_sobel::run", "", "invalid data format '"
                           + WB_data_format::to_string(output_data_store->data_format) + "'");
          }
        }
      }
    }
  }
}
