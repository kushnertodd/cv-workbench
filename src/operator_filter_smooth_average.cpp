//
// Created by kushn on 7/23/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_smooth_average.hpp"

Operator_filter_smooth_average::~Operator_filter_smooth_average() = default;
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
  if (output_data_stores.size() > 1)
    errors.add("Operator_filter_smooth_average::run", "", "too many output data sources");
  int rows;
  if (Operator_utils::has_parameter(operator_parameters, "rows"))
    Operator_utils::get_int_parameter("Operator_transform_image_create::run",
                                      operator_parameters, "rows", rows, errors);
  int cols;
  if (Operator_utils::has_parameter(operator_parameters, "cols"))
    Operator_utils::get_int_parameter("Operator_transform_image_create::run",
                                      operator_parameters, "cols", cols, errors);
  Data_source_descriptor *input_data_source = input_data_sources.front();
  Data_source_descriptor *output_data_store = output_data_stores.front();
  if (output_data_store->data_format != WB_data_format::Data_format::BINARY)
    errors.add("Operator_filter_smooth_average::run", "", "only binary output data format supported");
  Image *input = nullptr;
  if (!errors.has_error()) {
    if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
      input = input_data_source->read_image_jpeg(errors);
    else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
      input = input_data_source->read_image(errors);
    else
      errors.add("Operator_filter_smooth_average::run", "", "input data format must be jpeg or binary, not " +
          WB_data_format::to_string(input_data_source->data_format));
  }
  if (!errors.has_error() && input != nullptr)
    input->check_grayscale(errors);
  // TODO: implement separable filter
  if (!errors.has_error() && input != nullptr) {
    auto *coeffs_32F = new pixel_32F[rows * cols];
    double correction = 1.0 / (rows * cols);
    for (int i = 0; i < rows * cols; i++)
      coeffs_32F[i] = wb_utils::double_to_float(correction);
    std::unique_ptr<Kernel> average_kernel(Kernel::create_32F(rows, cols, coeffs_32F));
    Image *output = average_kernel->convolve_numeric(input, errors);
    if (!errors.has_error() && output != nullptr)
      Operator_utils::write_operator_image(output_data_store,
                                           output,
                                           "Operator_filter_smooth_average::run",
                                           errors);
    if (!errors.has_error() && output != nullptr) {
      output->log(log_entries);
    }
    delete[] coeffs_32F;
    delete output;
  }
  delete input;
}
