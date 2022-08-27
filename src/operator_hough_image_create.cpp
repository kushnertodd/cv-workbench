//
// Created by kushn on 7/13/2022.
//

#include <iostream>
#include <memory>
#include "hough.hpp"
#include "operator_utils.hpp"
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
                                      std::list<WB_log_entry> &log_entries,
                                      Errors &errors) {
  if (debug) {
    std::cout << "Operator_hough_image_create::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_hough_image_create::run", "", "input data source required");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_hough_image_create::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_hough_image_create::run", "", "output data source required");
  int theta_inc = 0;
  Operator_utils::get_int_parameter("Operator_hough_image_create::run",
                                    operator_parameters, "theta_inc", theta_inc, errors);
  int threshold = 0;
  Operator_utils::get_int_parameter("Operator_hough_image_create::run",
                                    operator_parameters, "threshold", threshold, errors);
  int ulc_row = 0;
  Operator_utils::get_int_parameter("Operator_hough_image_create::run",
                                    operator_parameters, "ulc_row", ulc_row, errors);
  int ulc_col = 0;
  Operator_utils::get_int_parameter("Operator_hough_image_create::run",
                                    operator_parameters, "ulc_col", ulc_col, errors);
  int lrc_row = 0;
  bool saw_lrc_row = Operator_utils::get_int_parameter("Operator_hough_image_create::run",
                                                       operator_parameters, "lrc_row", lrc_row, errors);
  int lrc_col = 0;
  bool saw_lrc_col = Operator_utils::get_int_parameter("Operator_hough_image_create::run",
                                                       operator_parameters, "lrc_col", lrc_col, errors);
  Data_source_descriptor *input_data_source = input_data_sources.front();
  Image *input_ptr = nullptr;
  if (!errors.has_error()) {
    input_ptr = input_data_source->read_operator_image("Operator_hough_image_create::run", errors);
    std::unique_ptr<Image> input(input_ptr);
    if (!errors.has_error() && input_ptr != nullptr)
      input->check_grayscale("Operator_hough_image_create::run", errors);
    if (!errors.has_error()) {
      if (!saw_lrc_row)
        lrc_row = input->get_rows() - 1;
      if (!saw_lrc_col)
        lrc_col = input->get_cols() - 1;
      std::unique_ptr<Hough> hough(Hough::create_image(input.get(), theta_inc, threshold));
      for (Data_source_descriptor *hough_output_data_store: output_data_stores)
        hough_output_data_store->write_operator_hough(hough.get(), "Operator_hough_image_create::run", errors);
    }
  }
}
