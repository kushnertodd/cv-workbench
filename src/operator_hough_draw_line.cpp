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
            bool saw_min_value = false;
            int min_value = 0;
            if (Operator_utils::has_parameter(operator_parameters, "min_value")) {
              std::string min_value_str = Operator_utils::get_parameter(operator_parameters, "min_value");
              if (!wb_utils::string_to_int(min_value_str, min_value))
                errors.add("Operator_hough_draw_line::run", "", "non-numeric 'min_value' parameter");
              else
                saw_min_value = true;
            }
            bool saw_max_value = false;
            int max_value = 0;
            if (Operator_utils::has_parameter(operator_parameters, "max_value")) {
              std::string max_value_str = Operator_utils::get_parameter(operator_parameters, "max_value");
              if (!wb_utils::string_to_int(max_value_str, max_value))
                errors.add("Operator_hough_draw_line::run", "", "non-numeric 'max_value' parameter");
              else
                saw_max_value = true;
            }
            Data_source_descriptor *input_data_source = input_data_sources.front();
            Data_source_descriptor *hough_line_output_data_store = output_data_stores.front();

            Image *input = input_data_source->read_image(errors);
            if (errors.error_ct == 0 && input != nullptr)
              input->check_grayscale(errors);
            if (errors.error_ct == 0) {
              Hough hough(input, theta_inc);
              int rho_index = hough.accum->rho_to_index(rho);
              Polar_line polar_line(rho_index, rho, theta_index,
                  hough.accum->get_cos(theta_index), hough.accum->get_sin(theta_index),0);
              Line_segment line_segment; if (!hough.accum->clip_window(line_segment, polar_line)) {
                errors.add("Operator_hough_draw_line::run", "", "failed clipping (theta_index, rho against image ");
              } else {
                Variance_stats stats;
                input->get_stats(stats);
                if (!saw_min_value)
                  min_value = stats.bounds.min_value;
                if (!saw_max_value)
                  max_value = stats.bounds.max_value;
                Image *output = Image::scale_image(input,
                                                   min_value,
                                                   max_value,
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