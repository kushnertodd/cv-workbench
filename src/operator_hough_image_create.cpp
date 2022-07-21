//
// Created by kushn on 7/13/2022.
//

#include <iostream>
#include "berkeley_db_data_source_descriptor.hpp"
#include "hough.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"
#include "operator_hough_image_create.hpp"

extern bool debug;

/**
 * theta_inc: hough accumulator theta increment (no. thetas = 180/theta_inc)
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_hough_image_create::run(std::list<Data_source_descriptor *> &input_data_sources,
                                            std::list<Data_source_descriptor *> &output_data_stores,
                                            String_map &operator_parameters,
                                            Errors &errors) {
  if (debug) {
    std::cout << "Operator_hough_image_create::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_hough_image_create::run", "", "missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_hough_image_create::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_hough_image_create::run", "", "missing output data source");
  else if (output_data_stores.size() > 2)
    errors.add("Operator_hough_image_create::run", "", "too many output data sources");
  else {

    if (!Operator_utils::has_parameter(operator_parameters, "theta_inc")) {
      errors.add("Operator_hough_image_create::run", "", "missing 'theta_inc' parameter");
    } else {
      std::string theta_inc_str = Operator_utils::get_parameter(operator_parameters, "theta_inc");
      int theta_inc = 0;
      if (!wb_utils::string_to_int(theta_inc_str, theta_inc))
        errors.add("Operator_hough_image_create::run", "", "non-numeric 'theta_inc' parameter");
      else {
        if (!Operator_utils::has_parameter(operator_parameters, "threshold")) {
          errors.add("Operator_hough_image_create::run", "", "missing 'threshold' parameter");
        } else {
          std::string threshold_str = Operator_utils::get_parameter(operator_parameters, "threshold");
          int threshold = 0;
          if (!wb_utils::string_to_int(threshold_str, threshold))
            errors.add("Operator_hough_image_create::run", "", "non-numeric 'threshold' parameter");
          else {
            Data_source_descriptor *input_data_source = input_data_sources.front();
            Image *input = nullptr;
            if (input_data_source->data_format == cv_enums::JPEG)
              input = input_data_source->read_image_jpeg(errors);
            else if (input_data_source->data_format == cv_enums::BINARY)
              input = input_data_source->read_image(errors);
            else
              errors.add("Operator_hough_image_create::run", "", "invalid data format: " +
                  wb_utils::data_format_to_string(input_data_source->data_format));
            if (errors.error_ct == 0 && input != nullptr)
              input->check_grayscale(errors);
            if (errors.error_ct == 0) {
              Hough hough(input, theta_inc, threshold);
              for (Data_source_descriptor *hough_output_data_store: output_data_stores) {
                if (hough_output_data_store->data_format == cv_enums::BINARY) {
                  hough_output_data_store->write_hough(&hough, errors);
                } else if (hough_output_data_store->data_format == cv_enums::TEXT) {
                  hough_output_data_store->write_hough_text(&hough, errors);
                } else {
                  errors.add("Operator_hough_image_create::run", "", "invalid data format "
                      + wb_utils::data_format_to_string(hough_output_data_store->data_format));
                }
              }
            }
          }
        }
      }
    }
  }
}