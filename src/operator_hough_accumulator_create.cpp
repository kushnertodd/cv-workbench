//
// Created by kushn on 7/13/2022.
//

#include <iostream>
#include "hough.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"
#include "operator_hough_accumulator_create.hpp"

extern bool debug;

Operator_hough_accumulator_create::Operator_hough_accumulator_create() {}

/**
 * theta_inc: hough accumulator theta increment (no. thetas = 180/theta_inc)
 *
 * references:
 * https://homepages.inf.ed.ac.uk/rbf/HIPR2/sobel.htm
 * https://en.wikipedia.org/wiki/Sobel_operator
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_hough_accumulator_create::run(std::list<Data_source_descriptor *> &input_data_sources,
                                            std::list<Data_source_descriptor *> &output_data_stores,
                                            String_map &operator_parameters,
                                            Errors &errors) {
  if (debug) {
    std::cout << "Operator_hough_accumulator_create::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.size() < 1)
    errors.add("Operator_hough_accumulator_create::run", "", "missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_hough_accumulator_create::run", "", "too many input data sources");
  else if (output_data_stores.size() < 2)
    errors.add("Operator_hough_accumulator_create::run", "", "missing output data source");
  else if (output_data_stores.size() > 2)
    errors.add("Operator_hough_accumulator_create::run", "", "too many output data sources");
  else {
    if (!Operator_utils::has_parameter(operator_parameters, "theta_inc")) {
      errors.add("Operator_hough_accumulator_create::run", "", "missing 'theta_inc' parameter");
    } else {
      std::string theta_inc_str = Operator_utils::get_parameter(operator_parameters, "theta_inc");
      int theta_inc = 0;
      if (!wb_utils::string_to_int(theta_inc_str, theta_inc))
        errors.add("Operator_hough_accumulator_create::run", "", "non-numeric 'theta_inc' parameter");
      else {
        Data_source_descriptor *input_data_source = input_data_sources.front();
        std::list<Data_source_descriptor *>::iterator it = output_data_stores.begin();
        Data_source_descriptor *hough_text_output_data_store = *it;
        std::advance(it, 1);
        Data_source_descriptor *hough_lines_output_data_store = *it;

        Image *input = input_data_source->read_image(errors);
        if (errors.error_ct == 0 && input != nullptr)
          input->check_grayscale(errors);
        if (errors.error_ct == 0) {
          Hough hough(input, theta_inc);
          hough_text_output_data_store->write_hough(&hough, errors);
          if (errors.error_ct == 0) {
            Image *output = Image::scale_image(input,
                                               input->bounds.min_value,
                                               input->bounds.min_value,
                                               pixel_8U_MIN,
                                               pixel_8U_MAX,
                                               cv_enums::CV_8U);
            hough.find_lines();
            output->draw_line_segments(hough.line_segments, 0);
            hough_lines_output_data_store->write_image(output, errors);
          }
        }
      }
    }
  }

}