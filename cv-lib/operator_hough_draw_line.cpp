//
// Created by kushn on 7/13/2022.
//

#include <iostream>
#include "hough.hpp"
#include "operator_utils.hpp"
#include "wb_window.hpp"
#include "operator_hough_draw_line.hpp"

extern bool debug;

/**
 * theta_inc: hough accumulator theta increment (no. thetas = 180/theta_inc)
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_hough_draw_line::run(std::list<Data_source_descriptor *> &input_data_sources,
                                   std::list<Data_source_descriptor *> &output_data_stores,
                                   String_map &operator_parameters,
                                   std::list<WB_log_entry> &log_entries,
                                   Errors &errors) {
  if (debug) {
    std::cout << "Operator_hough_draw_line::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_hough_draw_line::run", "", "input data source required");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_hough_draw_line::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_hough_draw_line::run", "", "output data source required");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_hough_draw_line::run", "", "too many output data sources");
  int theta_inc;
  Operator_utils::get_int_parameter("Operator_transform_image_create::run",
                                    operator_parameters, "theta_inc", theta_inc, errors);
  double rho;
  Operator_utils::get_real_parameter("Operator_transform_image_create::run",
                                     operator_parameters, "rho", rho, errors);
  int theta_index;
  Operator_utils::get_int_parameter("Operator_transform_image_create::run",
                                    operator_parameters, "theta_index", theta_index, errors);
  double pixel_value;
  Operator_utils::get_real_parameter("Operator_transform_image_create::run",
                                     operator_parameters, "pixel_value", pixel_value, errors);
  int out_component;
  if (Operator_utils::has_parameter(operator_parameters, "out_component")) {
    Operator_utils::get_int_parameter("Operator_transform_image_create::run",
                                      operator_parameters, "out_component", out_component, errors);
  } else
    out_component = 1;
  Data_source_descriptor *input_data_source = input_data_sources.front();
  Data_source_descriptor *hough_line_output_data_store = output_data_stores.front();

  Image *input = input_data_source->read_operator_image("Operator_hough_draw_line::run", errors);
  if (!errors.has_error() && input != nullptr)
    input->check_grayscale("Operator_hough_draw_line::run", errors);
  if (!errors.has_error() && input != nullptr) {
    int rows = input->get_rows();
    int cols = input->get_cols();
    auto *hough_accum = new Hough_accum(theta_inc, rows, cols);
    int rho_index = Polar_trig::rho_to_index(rho, hough_accum->get_nrhos());
    Polar_line polar_line(rho_index,
                          rho,
                          theta_index,
                          Polar_trig::to_cos(theta_index),
                          Polar_trig::to_sin(theta_index),
                          0);
    Line_segment line_segment;
    if (!WB_window::clip_window(rows, cols, line_segment, polar_line, hough_accum->get_nrhos())) {
      errors.add("Operator_hough_draw_line::run", "", "failed clipping (rho, theta_index) against image ");
    } else {
      input->draw_line_segment(line_segment, pixel_value);
      if (input_data_source->data_format == WB_data_format::Data_format::JPEG) {
        hough_line_output_data_store->write_image_jpeg(input, errors);
      } else if (input_data_source->data_format == WB_data_format::Data_format::BINARY) {
        hough_line_output_data_store->write_image(input, errors);
      } else {
        errors.add("Operator_hough_draw_line::run",
                   "",
                   "invalid data format '"
                       + WB_data_format::to_string(hough_line_output_data_store->data_format) + "'");
      }
    }
  }
}
