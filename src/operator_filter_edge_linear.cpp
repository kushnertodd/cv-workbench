//
// Created by kushn on 7/23/2022.
//

#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "operator_filter_edge_linear.hpp"
#include "wb_linear_config_mask.hpp"

Operator_filter_edge_linear::~Operator_filter_edge_linear() = default;
/**
 * run image gaussian smooth operator
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param log_entries
 * @param errors
 */
void Operator_filter_edge_linear::run(std::list<Data_source_descriptor *> &input_data_sources,
                                      std::list<Data_source_descriptor *> &output_data_stores,
                                      String_map &operator_parameters,
                                      std::list<WB_log_entry> &log_entries,
                                      Errors &errors) {
  if (input_data_sources.empty())
    errors.add("Operator_filter_edge_linear::run", "", "input data source required");
  if (input_data_sources.size() > 1)
    errors.add("Operator_filter_edge_linear::run", "", "too many input data sources");
  if (output_data_stores.empty())
    errors.add("Operator_filter_edge_linear::run", "", "output data source required");
  int theta_degrees;
  Operator_utils::get_int_parameter("Operator_filter_edge_linear::run",
                                    operator_parameters, "theta-degrees", theta_degrees, errors);
  int height;
  Operator_utils::get_int_parameter("Operator_filter_edge_linear::run",
                                    operator_parameters, "height", height, errors);
  int width_left;
  Operator_utils::get_int_parameter("Operator_filter_edge_linear::run",
                                    operator_parameters, "width-left", width_left, errors);
  double value_left;
  Operator_utils::get_real_parameter("Operator_filter_edge_linear::run",
                                     operator_parameters, "value-left", value_left, errors);
  int width_center;
  Operator_utils::get_int_parameter("Operator_filter_edge_linear::run",
                                    operator_parameters, "width-center", width_center, errors);
  double value_center;
  Operator_utils::get_real_parameter("Operator_filter_edge_linear::run",
                                     operator_parameters, "value-center", value_center, errors);
  int width_right;
  Operator_utils::get_int_parameter("Operator_filter_edge_linear::run",
                                    operator_parameters, "width-right", width_right, errors);
  double value_right;
  Operator_utils::get_real_parameter("Operator_filter_edge_linear::run",
                                     operator_parameters, "value-right", value_right, errors);

  if (!errors.has_error()) {
    Data_source_descriptor *input_data_source = input_data_sources.front();
    std::unique_ptr<Image>
        input(input_data_source->read_operator_image("Operator_filter_edge_linear::run", errors));
    if (!errors.has_error())
      input->check_grayscale("Operator_filter_edge_linear::run", errors);
    if (!errors.has_error())
      Operator_utils::get_subimage_parameters(input.get(),
                                              "Operator_hough_image_create::run",
                                              operator_parameters,
                                              errors);
    if (!errors.has_error()) {
      std::unique_ptr<Kernel> linear_mask(
          Kernel::create_linear_mask(input->get_rows(), input->get_cols(),
                                     theta_degrees,
                                     height,
                                     width_left,
                                     value_left,
                                     width_center,
                                     value_center,
                                     width_right,
                                     value_right));
      if (!errors.has_error()) {
        std::unique_ptr<Image> output(linear_mask->convolve_numeric(input.get(), errors));
        for (Data_source_descriptor *output_data_store: output_data_stores)
          if (!errors.has_error())
            output_data_store->write_operator_image(output.get(),
                                                    "Operator_filter_edge_linear::run",
                                                    errors);
        if (!errors.has_error()) {
          output->log(log_entries);
        }
      }
    }
  }
}