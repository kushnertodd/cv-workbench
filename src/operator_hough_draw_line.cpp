//
// Created by kushn on 7/13/2022.
//

#include <iostream>
#include "hough.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"
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
                                   Errors &errors) {
  if (debug) {
    std::cout << "Operator_hough_draw_line::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_hough_draw_line::run", "", "missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_hough_draw_line::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_hough_draw_line::run", "", "missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_hough_draw_line::run", "", "too many output data sources");
  else {
    if (!Operator_utils::has_parameter(operator_parameters, "theta_inc")) {
      errors.add("Operator_hough_draw_line::run", "", "missing 'theta_inc' parameter");
    }
    if (!Operator_utils::has_parameter(operator_parameters, "threshold")) {
      errors.add("Operator_hough_draw_line::run", "", "missing 'threshold' parameter");
    }
    if (!Operator_utils::has_parameter(operator_parameters, "rho")) {
      errors.add("Operator_hough_draw_line::run", "", "missing 'rho' parameter");
    }
    if (!Operator_utils::has_parameter(operator_parameters, "theta_index")) {
      errors.add("Operator_hough_draw_line::run", "", "missing 'theta_index' parameter");
    }
    if (!Operator_utils::has_parameter(operator_parameters, "pixel_value")) {
      errors.add("Operator_hough_draw_line::run", "", "missing 'pixel_value' parameter");
    }
    if (errors.error_ct == 0) {

      std::string theta_inc_str = Operator_utils::get_parameter(operator_parameters, "theta_inc");
      int theta_inc = 0;
      if (!wb_utils::string_to_int(theta_inc_str, theta_inc))
        errors.add("Operator_hough_draw_line::run", "", "non-numeric 'theta_inc' parameter");
      else {
        std::string threshold_str = Operator_utils::get_parameter(operator_parameters, "threshold");
        int threshold = 0;
        if (!wb_utils::string_to_int(threshold_str, threshold))
          errors.add("Operator_hough_draw_line::run", "", "non-numeric 'threshold' parameter");
        else {
          std::string rho_str = Operator_utils::get_parameter(operator_parameters, "rho");
          double rho = 0;
          if (!wb_utils::string_to_double(rho_str, rho))
            errors.add("Operator_hough_draw_line::run", "", "non-numeric 'rho' parameter");
          else {
            std::string theta_index_str = Operator_utils::get_parameter(operator_parameters, "theta_index");
            int theta_index = 0;
            if (!wb_utils::string_to_int(theta_index_str, theta_index))
              errors.add("Operator_hough_draw_line::run", "", "non-numeric 'theta_index' parameter");
            else {
              double pixel_value = 0;
              if (Operator_utils::has_parameter(operator_parameters, "pixel_value")) {
                std::string min_value_str = Operator_utils::get_parameter(operator_parameters, "pixel_value");
                if (!wb_utils::string_to_double(min_value_str, pixel_value))
                  errors.add("Operator_hough_draw_line::run", "", "non-numeric 'pixel_value' parameter");
              }
              int out_component = 1;
              if (Operator_utils::has_parameter(operator_parameters, "out_component")) {
                std::string out_component_str = Operator_utils::get_parameter(operator_parameters, "out_component");
                if (!wb_utils::string_to_int(out_component_str, out_component))
                  errors.add("Operator_hough_draw_line::run", "", "non-numeric 'out_component' parameter");
              }
              Data_source_descriptor *input_data_source = input_data_sources.front();
              Data_source_descriptor *hough_line_output_data_store = output_data_stores.front();

              Image *input = nullptr;
              if (input_data_source->data_format == CV_data_format::format::JPEG)
                input = input_data_source->read_image_jpeg(errors);
              else if (input_data_source->data_format == CV_data_format::format::BINARY)
                input = input_data_source->read_image(errors);
              else
                errors.add("Operator_hough_draw_line::run", "", "invalid data format: " +
                    CV_data_format::data_format_enum_to_string(input_data_source->data_format));
              if (errors.error_ct == 0 && input != nullptr)
                input->check_grayscale(errors);
              if (errors.error_ct == 0) {
                Hough* hough = Hough::create_image(input, theta_inc, threshold);
                int rho_index = hough->hough_accum->rho_to_index(rho);
                Polar_line polar_line(rho_index,
                                      rho,
                                      theta_index,
                                      hough->hough_accum->get_cos(theta_index),
                                      hough->hough_accum->get_sin(theta_index),
                                      0);
                Line_segment line_segment;
                if (!hough->hough_accum->clip_window(line_segment, polar_line)) {
                  errors.add("Operator_hough_draw_line::run", "", "failed clipping (rho, theta_index) against image ");
                } else {
                  Variance_stats stats;
                  input->get_stats(stats);
                  input->draw_line_segment(line_segment, pixel_value);
                  if (hough_line_output_data_store->data_format == CV_data_format::format::JPEG) {
                    hough_line_output_data_store->write_image_jpeg(input, errors);
                  } else if (hough_line_output_data_store->data_format == CV_data_format::format::BINARY) {
                    hough_line_output_data_store->write_image(input, errors);
                  } else {
                    errors.add("Operator_hough_draw_line::run",
                               "",
                               "invalid data format '"
                                   + CV_data_format::data_format_enum_to_string(hough_line_output_data_store->data_format) + "'");
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}