//
// Created by kushn on 7/23/2022.
//

#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_smooth_average.hpp"
#include "wb_utils.hpp"

Operator_filter_smooth_average::~Operator_filter_smooth_average() = default;
/**
 * Run image average smooth operator
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param log_entries
 * @param errors
 */
void Operator_filter_smooth_average::run(std::list<Data_source_descriptor *> &input_data_sources,
                                         std::list<Data_source_descriptor *> &output_data_stores,
                                         String_map &operator_parameters,
                                         std::list<WB_log_entry> &log_entries,
                                         Errors &errors) {
  if (input_data_sources.empty())
    errors.add("Operator_filter_smooth_average::run", "", "input data source required");
  if (input_data_sources.size() > 1)
    errors.add("Operator_filter_smooth_average::run", "", "too many input data sources");
  if (output_data_stores.empty())
    errors.add("Operator_filter_smooth_average::run", "", "output data source required");
  int rows;
  Operator_utils::get_int_parameter("Operator_filter_smooth_average::run",
                                    operator_parameters, "rows", rows, errors);
  int cols;
  Operator_utils::get_int_parameter("Operator_filter_smooth_average::run",
                                    operator_parameters, "cols", cols, errors);
  if (!errors.has_error()) {
    Data_source_descriptor *input_data_source = input_data_sources.front();
    std::unique_ptr<Image> input(input_data_source->read_operator_image("Operator_filter_smooth_average::run", errors));
    if (!errors.has_error())
      input->check_grayscale("Operator_filter_smooth_average::run", errors);
    if (!errors.has_error())
      Operator_utils::get_subimage_parameters(input.get(),
                                              "Operator_hough_image_create::run",
                                              operator_parameters,
                                              errors);
    // TODO: implement separable filter
    if (!errors.has_error()) {
      auto *coeffs_32F = new pixel_32F[rows * cols];
      double correction = 1.0 / (rows * cols);
      for (int i = 0; i < rows * cols; i++)
        coeffs_32F[i] = wb_utils::double_to_float(correction);
      std::unique_ptr<Kernel> average_kernel(Kernel::create_32F(rows, cols, coeffs_32F));
      std::unique_ptr<Image> output(average_kernel->convolve_numeric(input.get(), errors));
      if (!errors.has_error())
        for (Data_source_descriptor *output_data_store: output_data_stores)
          output_data_store->write_operator_image(output.get(),
                                                  "Operator_filter_smooth_average::run",
                                                  errors);
      if (!errors.has_error()) {
        output->log(log_entries);
      }
      delete[] coeffs_32F;
    }
  }
}
