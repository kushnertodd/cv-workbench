//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "operator_filter_edge_prewitt.hpp"

using namespace std;

extern bool debug;

Operator_filter_edge_prewitt::Operator_filter_edge_prewitt() {}

/**
 * orientation:
 *      0 = [-1, 0, 1], [-1, 0, 1], [-1, 0, 1]
 *     90 = [1, 1, 1],  [0, 0, 0],  [-1, -1, -1]
 * references:
 * https://en.wikipedia.org/wiki/Prewitt_operator
 * PREWITT, J. M. S. "Object enhancemen t and extraction." In Picture Processing and Psychopictorics,
 *     B. S. Lipkin and A. Rosenfeld (Eds.) . New York: Academic Press, 1970.
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_edge_prewitt::run(list<Data_source_descriptor *> &input_data_sources,
                                     list<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters,
                                     Errors &errors) {

  if (debug) {
    cout << "Operator_filter_edge_prewitt::run parameters: "
         << Operator_utils::parameters_to_string(operator_parameters) << endl;
  }
  if (input_data_sources.size() == 0)
    errors.add("Operator_filter_edge_prewitt::run missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_prewitt::run too many input data sources");
  else if (output_data_stores.size() == 0)
    errors.add("Operator_filter_edge_prewitt::run missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_filter_edge_prewitt::run too many output data sources");
  else {
    if (!Operator_utils::has_parameter(operator_parameters, "orientation")) {
      errors.add("Operator_filter_edge_prewitt::run: missing 'orientation' parameter");
    } else {
      string orientation_str = Operator_utils::get_parameter(operator_parameters, "orientation");
      if (orientation_str != "0" && orientation_str != "90") {
        errors.add("Operator_filter_edge_prewitt: invalid 'orientation' parameter not 0 or 90");
      } else {
        Kernel *prewitt_kernel = nullptr;
        if (orientation_str == "0") {
          //      0 = [-1, 0, 1], [-1, 0, 1], [-1, 0, 1]
          int coeffs_32S[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
          prewitt_kernel = Kernel::create_32S(3, 3, coeffs_32S);
        } else if (orientation_str == "90") {
          //     90 = [1, 1, 1],  [0, 0, 0],  [-1, -1, -1]
          int coeffs_32S[] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
          prewitt_kernel = Kernel::create_32S(3, 3, coeffs_32S);
        }
        Data_source_descriptor *input_data_source = input_data_sources.front();
        Data_source_descriptor *output_data_store = output_data_stores.front();
        Image *input = input_data_source->read_image(errors);
        if (errors.error_ct == 0) {
          Image *output = prewitt_kernel->convolve(input);
          output_data_store->write_image(output, errors);
        }
      }
    }
  }
}
