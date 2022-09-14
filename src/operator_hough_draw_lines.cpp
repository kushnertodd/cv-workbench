//
// Created by kushn on 7/13/2022.
//

#include <iostream>
#include <memory>
#include "hough.hpp"
#include "operator_utils.hpp"
#include "wb_window.hpp"
#include "operator_hough_draw_lines.hpp"

/**
 * theta_inc: hough accumulator theta increment (no. thetas = 180/theta_inc)
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_hough_draw_lines::run(std::list<Data_source_descriptor *> &input_data_sources,
                                    std::list<Data_source_descriptor *> &output_data_stores,
                                    String_map &operator_parameters,
                                    std::list<WB_log_entry> &log_entries,
                                    Errors &errors) {
  if (input_data_sources.empty())
    errors.add("Operator_hough_draw_lines::run", "", "input data source required");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_hough_draw_lines::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_hough_draw_lines::run", "", "output data source required");
  Image *image_ptr = nullptr;
  std::list<Hough_peak> hough_peaks;
  double pixel_value;
  Operator_utils::get_real_parameter("Operator_hough_draw_line::run",
                                     operator_parameters, "pixel_value", pixel_value, errors);
  int out_component = 1;
  Operator_utils::get_int_parameter("Operator_hough_draw_line::run",
                                    operator_parameters, "out_component",
                                    out_component, errors, true);
  bool read_image = false;
  bool read_peaks = false;
  if (!errors.has_error()) {
    for (Data_source_descriptor *input_data_source: input_data_sources) {
      if (input_data_source->id == 1) {
        read_image = true;
        image_ptr = input_data_source->read_operator_image("Operator_transform_image_combine::run", errors);
      } else if (input_data_source->id == 2) {
        read_peaks = true;
        input_data_source->read_operator_hough_peaks(hough_peaks, "Operator_transform_image_combine::run", errors);
      }
    }
    std::unique_ptr<Image> input(image_ptr);
    if (!errors.has_error()) {
      int rows = input->get_rows();
      int cols = input->get_cols();
      for (Hough_peak hough_peak: hough_peaks) {
        Line_segment line_segment;
        if (!WB_window::clip_window(rows, cols, line_segment, hough_peak.polar_line)) {
          errors.add("Operator_hough_draw_lines::run", "", "failed clipping (rho, theta) against image ");
        } else {
          // user components are 1-3
          input->draw_line_segment(line_segment, pixel_value, out_component - 1);
          for (Data_source_descriptor *histogram_output_data_store: output_data_stores)
            histogram_output_data_store->write_operator_image(input.get(),
                                                              "Operator_hough_draw_lines::run",
                                                              errors);
          if (!errors.has_error()) {
            input->log(log_entries);
          }
        }
      }
    }
  }
}
