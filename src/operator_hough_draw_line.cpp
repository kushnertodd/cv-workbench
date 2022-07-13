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

Operator_hough_draw_line::Operator_hough_draw_line() {}

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
  if (input_data_sources.size() < 1)
    errors.add("Operator_hough_draw_line::run", "", "missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_hough_draw_line::run", "", "too many input data sources");
  else if (output_data_stores.size() < 1)
    errors.add("Operator_hough_draw_line::run", "", "missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_hough_draw_line::run", "", "too many output data sources");
  else {
    if (!Operator_utils::has_parameter(operator_parameters, "theta_inc")) {
      errors.add("Operator_hough_draw_line::run", "", "missing 'theta_inc' parameter");
    }
    if (!Operator_utils::has_parameter(operator_parameters, "theta_index")) {
      errors.add("Operator_hough_draw_line::run", "", "missing 'theta_index' parameter");
    }
    if (!Operator_utils::has_parameter(operator_parameters, "rho")) {
      errors.add("Operator_hough_draw_line::run", "", "missing 'rho' parameter");
    }
    if (errors.error_ct == 0) {
      std::string theta_inc_str = Operator_utils::get_parameter(operator_parameters, "theta_inc");
      int theta_inc = 0;
      if (!wb_utils::string_to_int(theta_inc_str, theta_inc))
        errors.add("Operator_hough_draw_line::run", "", "non-numeric 'theta_inc' parameter");
      else {
        std::string theta_index_str = Operator_utils::get_parameter(operator_parameters, "theta_index");
        int theta_index = 0;
        if (!wb_utils::string_to_int(theta_index_str, theta_index))
          errors.add("Operator_hough_draw_line::run", "", "non-numeric 'theta_index' parameter");
        else {
          std::string rho_str = Operator_utils::get_parameter(operator_parameters, "rho");
          int rho = 0;
          if (!wb_utils::string_to_int(rho_str, rho))
            errors.add("Operator_hough_draw_line::run", "", "non-numeric 'rho' parameter");
          else {
            Data_source_descriptor *input_data_source = input_data_sources.front();
            Data_source_descriptor *hough_line_output_data_store = output_data_stores.front();

            Image *input = input_data_source->read_image(errors);
            if (errors.error_ct == 0 && input != nullptr)
              input->check_grayscale(errors);
            if (errors.error_ct == 0) {
              Hough hough(input, theta_inc);
              int rho_index = hough.accum->rho_to_index(rho);
              Polar_line *polar_line = hough.accum->make_polar_line(rho_index, theta_index);
              Line_segment *line_segment = hough.accum->clip_window(polar_line);
              if (line_segment == nullptr) {
                errors.add("Operator_hough_draw_line::run", "", "failed clipping (theta_index, rho against image ");
              } else {
                Image *output = Image::scale_image(input,
                                                   input->bounds.min_value,
                                                   input->bounds.min_value,
                                                   pixel_8U_MIN,
                                                   pixel_8U_MAX,
                                                   cv_enums::CV_8U);
                output->draw_line_segment(line_segment, 0);
                hough_line_output_data_store->write_image(output, errors);
              }
            }
          }
        }
      }
    }
  }
}