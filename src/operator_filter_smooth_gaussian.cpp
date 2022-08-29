//
// Created by kushn on 7/23/2022.
//

#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_smooth_gaussian.hpp"

Operator_filter_smooth_gaussian::~Operator_filter_smooth_gaussian() = default;
void Operator_filter_smooth_gaussian::run(std::list<Data_source_descriptor *> &input_data_sources,
                                          std::list<Data_source_descriptor *> &output_data_stores,
                                          String_map &operator_parameters,
                                          std::list<WB_log_entry> &log_entries,
                                          Errors &errors) {
  if (input_data_sources.empty())
    errors.add("Operator_filter_smooth_gaussian::run", "", "input data source required");
  if (input_data_sources.size() > 1)
    errors.add("Operator_filter_smooth_gaussian::run", "", "too many input data sources");
  if (output_data_stores.empty())
    errors.add("Operator_filter_smooth_gaussian::run", "", "output data source required");
  int rows;
  Operator_utils::get_int_parameter("Operator_filter_smooth_gaussian::run",
                                    operator_parameters, "rows", rows, errors);
  int cols;
  Operator_utils::get_int_parameter("Operator_filter_smooth_gaussian::run",
                                    operator_parameters, "cols", cols, errors);
  double sigma_x;
  Operator_utils::get_real_parameter("Operator_filter_smooth_gaussian::run",
                                     operator_parameters, "sigma-x", sigma_x, errors);
  double sigma_y;
  Operator_utils::get_real_parameter("Operator_filter_smooth_gaussian::run",
                                     operator_parameters, "sigma-y", sigma_y, errors);
  if (!errors.has_error()) {
    Data_source_descriptor *input_data_source = input_data_sources.front();
    std::unique_ptr<Image>
        input(input_data_source->read_operator_image("Operator_filter_smooth_gaussian::run", errors));
    if (!errors.has_error())
      input->check_grayscale("Operator_filter_smooth_gaussian::run", errors);
    if (!errors.has_error())
      Operator_utils::get_subimage_parameters(input.get(),
                                              "Operator_hough_image_create::run",
                                              operator_parameters,
                                              errors);
    if (!errors.has_error()) {
      std::unique_ptr<Kernel> gaussian_kernel_y(Kernel::create_gaussian_y(rows, sigma_y));
      std::unique_ptr<Kernel> gaussian_kernel_x(Kernel::create_gaussian_x(cols, sigma_x));
      std::unique_ptr<Image> output_pass1(gaussian_kernel_y->convolve_numeric(input.get(), errors));
      if (!errors.has_error()) {
        std::unique_ptr<Image> output2(gaussian_kernel_x->convolve_numeric(output_pass1.get(), errors));
        if (!errors.has_error())
          for (Data_source_descriptor *output_data_store: output_data_stores)
            output_data_store->write_operator_image(output2.get(),
                                                    "Operator_filter_smooth_gaussian::run",
                                                    errors);
        if (!errors.has_error()) {
          output2->log(log_entries);
        }
      }
    }
  }
}