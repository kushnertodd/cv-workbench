//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_edge_sobel.hpp"

//


Operator_filter_edge_sobel::~Operator_filter_edge_sobel() = default;

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
void Operator_filter_edge_sobel::run(std::list<Data_source_descriptor *> &input_data_sources,
                                     std::list<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters,
                                     std::list<WB_log_entry> &log_entries,
                                     Errors &errors) {
  if (input_data_sources.empty())
    errors.add("Operator_filter_edge_sobel::run", "", "input data source required");
  if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_sobel::run", "", "too many input data sources");
  if (output_data_stores.empty())
    errors.add("Operator_filter_edge_sobel::run", "", "output data source required");
  std::string orientation_str;
  bool orientation_missing = Operator_utils::get_string_parameter("Operator_filter_edge_sobel::run",
                                                                  operator_parameters,
                                                                  "orientation",
                                                                  orientation_str, errors);
  if (!orientation_missing && orientation_str != "0" && orientation_str != "90")
    errors.add("Operator_filter_edge_sobel::run", "", "orientation not 0 or 90");
  Data_source_descriptor *input_data_source = input_data_sources.front();
  Image *input_ptr = nullptr;
  if (!errors.has_error())
    input_ptr = input_data_source->read_operator_image("Operator_filter_edge_sobel::run", errors);
  std::unique_ptr<Image> input(input_ptr);
  if (!errors.has_error() && input_ptr != nullptr)
    input->check_grayscale("Operator_filter_edge_sobel::run", errors);
  if (!errors.has_error() && input_ptr != nullptr) {
    Kernel *sobel_kernel_row_ptr = nullptr;
    Kernel *sobel_kernel_col_ptr = nullptr;
    if (orientation_str == "90") {
      pixel_32F coeffs_32F_row[] = {1, 0, -1};
      sobel_kernel_row_ptr = Kernel::create_32F(3, 1, coeffs_32F_row);
      pixel_32F coeffs_32F_col[] = {0.25, 0.5, 0.25};
      sobel_kernel_col_ptr = Kernel::create_32F(1, 3, coeffs_32F_col);
    } else if (orientation_str == "0") {
      pixel_32F coeffs_32F_row[] = {0.25, 0.5, 0.25};
      sobel_kernel_row_ptr = Kernel::create_32F(3, 1, coeffs_32F_row);
      // this is reversed from the separable filter reference
      pixel_32F coeffs_32F_col[] = {-1, 0, 1};
      sobel_kernel_col_ptr = Kernel::create_32F(1, 3, coeffs_32F_col);
    }
    std::unique_ptr<Kernel> sobel_kernel_row(sobel_kernel_row_ptr);
    std::unique_ptr<Kernel> sobel_kernel_col(sobel_kernel_col_ptr);
    Image *output1_ptr = sobel_kernel_row->convolve_numeric(input.get(), errors);
    std::unique_ptr<Image> output1(output1_ptr);
    Image *output2_ptr = nullptr;
    if (!errors.has_error() && output1_ptr != nullptr)
      output2_ptr = sobel_kernel_col->convolve_numeric(output1.get(), errors);
    std::unique_ptr<Image> output2(output2_ptr);
    if (!errors.has_error() && output2_ptr != nullptr)

      for (Data_source_descriptor *output_data_store: output_data_stores)
        output_data_store->write_operator_image(output2.get(), "Operator_filter_edge_sobel::run", errors);
    if (!errors.has_error() && output2_ptr != nullptr)
      output2->log(log_entries);
	}
}