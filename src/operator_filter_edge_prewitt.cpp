//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_edge_prewitt.hpp"

//

extern bool debug;

Operator_filter_edge_prewitt::~Operator_filter_edge_prewitt() = default;

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
void Operator_filter_edge_prewitt::run(std::list<Data_source_descriptor *> &input_data_sources,
                                       std::list<Data_source_descriptor *> &output_data_stores,
                                       String_map &operator_parameters,
                                       std::list<WB_log_entry> &log_entries,
                                       Errors &errors) {

  if (debug) {
    std::cout << "Operator_filter_edge_prewitt::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_filter_edge_prewitt::run", "", "input data source required");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_prewitt::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_filter_edge_prewitt::run", "", "output data source required");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_filter_edge_prewitt::run", "", "too many output data sources");
  else if (!Operator_utils::has_parameter(operator_parameters, "orientation")) {
    errors.add("Operator_filter_edge_prewitt::run", "", "orientation parameter required");
  } else {
    std::string orientation_str = Operator_utils::get_parameter(operator_parameters, "orientation");
    if (orientation_str != "0" && orientation_str != "90") {
      errors.add("Operator_filter_edge_prewitt", "", "orientation parameter not 0 or 90");
    } else {
      Data_source_descriptor *input_data_source = input_data_sources.front();
      Data_source_descriptor *output_data_store = output_data_stores.front();
      Image *input = nullptr;
      Image *output;
      if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
        input = input_data_source->read_image_jpeg(errors);
      else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
        input = input_data_source->read_image(errors);
      else
        errors.add("Operator_filter_edge_prewitt::run", "", "input data format must be jpeg or binary, not " +
            WB_data_format::to_string(input_data_source->data_format));
      if (!errors.has_error() && input != nullptr)
        input->check_grayscale(errors);
      if (!errors.has_error() && input != nullptr) {
        //Kernel *prewitt_kernel = nullptr;
        Kernel *prewitt_kernel_row_ptr = nullptr;
        Kernel *prewitt_kernel_col_ptr = nullptr;
        if (orientation_str == "90") {
          //      0 = [-1, 0, 1], [-1, 0, 1], [-1, 0, 1]
          //int coeffs_32S[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
          //prewitt_kernel = Kernel::create_32S(3, 3, coeffs_32S);
          int coeffs_32S_row[] = {1, 0, -1};
          prewitt_kernel_row_ptr = Kernel::create_32S(3, 1, coeffs_32S_row);
          int coeffs_32S_col[] = {1, 1, 1};
          prewitt_kernel_col_ptr = Kernel::create_32S(1, 3, coeffs_32S_col);
        } else if (orientation_str == "0") {
          //     90 = [1, 1, 1],  [0, 0, 0],  [-1, -1, -1]
          //int coeffs_32S[] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
          //prewitt_kernel = Kernel::create_32S(3, 3, coeffs_32S);
          int coeffs_32S_row[] = {1, 1, 1};
          prewitt_kernel_row_ptr = Kernel::create_32S(3, 1, coeffs_32S_row);
          // this is reversed from the separable filter reference
          int coeffs_32S_col[] = {-1, 0, 1};
          prewitt_kernel_col_ptr = Kernel::create_32S(1, 3, coeffs_32S_col);
        }
        //output = prewitt_kernel->convolve_numeric(input, errors);
        std::unique_ptr<Kernel> prewitt_kernel_row(prewitt_kernel_row_ptr);
        std::unique_ptr<Kernel> prewitt_kernel_col(prewitt_kernel_col_ptr);
        output = prewitt_kernel_row->convolve_numeric(input, errors);
        output = prewitt_kernel_col->convolve_numeric(output, errors);
        if (!errors.has_error() && output != nullptr)
          Operator_utils::write_operator_image(output_data_store, output, "Operator_filter_edge_prewitt::run", errors);
        if (!errors.has_error() && output != nullptr) {
          output->log(log_entries);
        }
        delete output;
      }
      delete input;
    }
  }
}

