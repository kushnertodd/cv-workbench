//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "operator_filter_edge_sobel.hpp"

using namespace std;

extern bool debug;

Operator_filter_edge_sobel::Operator_filter_edge_sobel() {}

/**
 * orientation:
 *      0 = [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]
 *     90 = [1, 2, 1],  [0, 0, 0],  [-1, -2, -1]
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_edge_sobel::run(list<Data_source_descriptor *> &input_data_sources,
                                     list<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters,
                                     Errors &errors) {

  if (debug) {
    cout << "Operator_filter_edge_sobel::run parameters: "
         << Operator_utils::parameters_to_string(operator_parameters) << endl;
  }
  if (input_data_sources.size() == 0)
    errors.add("Operator_filter_edge_sobel::run missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_sobel::run too many input data sources");
  else if (output_data_stores.size() == 0)
    errors.add("Operator_filter_edge_sobel::run missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_filter_edge_sobel::run too many output data sources");
  else {
    if (!Operator_utils::has_parameter(operator_parameters, "orientation")) {
      errors.add("Operator_filter_edge_sobel::run: missing 'orientation' parameter");
    } else {
      string orientation_str = Operator_utils::get_parameter(operator_parameters,"orientation");
      if (orientation_str != "0" && orientation_str != "1") {
        errors.add("Operator_filter_edge_sobel: invalid 'orientation' parameter not 0 or 1");
      } else {
        Kernel *sobel_kernel = nullptr;
        if (orientation_str == "0") {
          //      0 = [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]
          int coeffs_32S[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
          sobel_kernel=          Kernel::create_32S(3, 3, coeffs_32S);
        } else if (orientation_str == "1") {
          //     90 = [1, 2, 1],  [0, 0, 0],  [-1, -2, -1]
          float coeffs_32F[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
          sobel_kernel=              Kernel::create_32F(3, 3, coeffs_32F);
        }
        Data_source_descriptor *input_data_source = input_data_sources.front();
        Data_source_descriptor *output_data_store = output_data_stores.front();
        Image *input = input_data_source->read_image(errors);
        Image *output = sobel_kernel->convolve(input);
        output_data_store->write_image(output, errors);
      }
    }
  }
}
