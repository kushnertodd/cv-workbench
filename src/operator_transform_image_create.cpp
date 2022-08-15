//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <regex>
#include "operator_transform_image_create.hpp"
#include "operator_utils.hpp"
#include "wb_data_format.hpp"
#include "wb_image_depth.hpp"
#include "wb_defs.hpp"

extern bool debug;

/**
   create new image from an existing image
   parameters:
     depth_enum depth
       depth of output image
       optional: defaults to input image depth
         WB_image_depth::Image_depth::CV_8U   unsigned byte
         WB_image_depth::Image_depth::CV_32S  int
         WB_image_depth::Image_depth::CV_32F  float
     real lower_in
     real upper_in
     real lower_out
     real upper_out
       pixel intensity mapping parameters
       optional: all omitted defaults to no mapping
       else: all required
         pixel_in <= in_lower -> out_lower
         pixel_in >= in_upper -> out_upper;
         else -> out_lower + (pixel_in-in_lower) * (out_upper-out_lower) / (in_upper-in_lower)
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_transform_image_create::run(std::list<Data_source_descriptor *> &input_data_sources,
                                          std::list<Data_source_descriptor *> &output_data_stores,
                                          String_map &operator_parameters,
                                          std::list<WB_log_entry> &log_entries,
                                          Errors &errors) {

  if (debug) {
    std::cout << "Operator_transform_image_create::run:parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  bool input_data_sources_missing = input_data_sources.empty();
  if (output_data_stores.empty())
    errors.add("Operator_transform_image_create::run", "", "missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_transform_image_create::run", "", "too many output data sources");
  WB_image_depth::Image_depth depth;
  int rows;
  int cols;
  double background;
  double foreground;
  std::string param_point_str;
  std::string param_line_str;
  std::string param_rectangle_str;
  std::string param_rectangle_filled_str;
  bool saw_rows = false;
  bool saw_cols = false;
  bool saw_point = false;
  bool saw_line = false;
  bool saw_rectangle = false;
  bool saw_rectangle_filled = false;
  if (Operator_utils::has_parameter(operator_parameters, "rows")) {
    saw_rows = true;
    Operator_utils::get_int_parameter("Operator_transform_image_create::run",
                                      operator_parameters, "rows", rows, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "cols")) {
    saw_cols = true;
    Operator_utils::get_int_parameter("Operator_transform_image_create::run",
                                      operator_parameters, "cols", cols, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "background"))
    Operator_utils::get_real_parameter("Operator_transform_image_create::run",
                                       operator_parameters, "background", background, errors);
  else
    background = 0;
  if (Operator_utils::has_parameter(operator_parameters, "foreground"))
    Operator_utils::get_real_parameter("Operator_transform_image_create::run",
                                       operator_parameters, "foreground", foreground, errors);
  else
    foreground = 255;
  if (Operator_utils::has_parameter(operator_parameters, "point")) {
    saw_point = true;
    param_point_str = Operator_utils::get_parameter(operator_parameters, "point");
  }
  if (Operator_utils::has_parameter(operator_parameters, "line")) {
    saw_line = true;
    param_line_str = Operator_utils::get_parameter(operator_parameters, "line");
  }
  if (Operator_utils::has_parameter(operator_parameters, "rectangle")) {
    saw_rectangle = true;
    param_rectangle_str = Operator_utils::get_parameter(operator_parameters, "rectangle");
  }
  if (Operator_utils::has_parameter(operator_parameters, "rectangle-filled")) {
    saw_rectangle_filled = true;
    param_rectangle_filled_str = Operator_utils::get_parameter(operator_parameters, "rectangle-filled");
  }
  Image *image;
  Data_source_descriptor *input_data_source;
  Data_source_descriptor *output_data_store = output_data_stores.front();
  if (input_data_sources_missing && (!saw_rows || !saw_cols)) {
    errors.add("Operator_transform_image_create::run",
               "",
               "'rows' and 'cols' parameters required if no input data source");
  }
  if (!errors.has_error()) {
    if (input_data_sources_missing) {
      image = new Image(rows, cols, 1, WB_image_depth::Image_depth::CV_32S);
    } else {
      input_data_source = input_data_sources.front();
      if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
        image = input_data_source->read_image_jpeg(errors);
      else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
        image = input_data_source->read_image(errors);
      else
        errors.add("Operator_filter_edge_prewitt::run", "", "invalid data format: " +
            WB_data_format::to_string(input_data_source->data_format));
      if (image != nullptr && !errors.has_error())
        image->check_grayscale(errors);
    }
  }
  if (!errors.has_error() && saw_point) {
    std::vector<std::string> points = wb_utils::tokenize(param_point_str, "|");
    if (points.empty()) {
      errors.add("Operator_transform_image_create::run", "", "invalid point parameter value");
    }
    if (!errors.has_error()) {
      std::regex point_pat("\\(([0-9]+),([0-9]+)\\)");
      for (const std::string &point_str: points) {
        std::smatch msm;
        if (!std::regex_match(point_str, msm, point_pat)) {
          errors.add("Operator_transform_image_create::run", "", "invalid point parameter value");
        } else if (msm.size() != 3) {
          errors.add("Operator_transform_image_create::run", "", "invalid point parameter value");
        } else {
          std::string row_str = msm[1];
          std::string col_str = msm[2];
          int row;
          int col;
          if (!wb_utils::string_to_int(row_str, row))
            errors.add("Operator_transform_image_create::run", "", "invalid point parameter row value");
          if (!wb_utils::string_to_int(col_str, col))
            errors.add("Operator_transform_image_create::run", "", "invalid point parameter col value");
          if (!errors.has_error()) {
            image->set(row, col, foreground);
          }
        }
      }
    }
  }
  if (!errors.has_error() && saw_line) {
    std::vector<std::string> lines = wb_utils::tokenize(param_line_str, "|");
    if (lines.empty()) {
      errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
    }
    if (!errors.has_error()) {
      std::regex line_pat(R"(\(([0-9]+),([0-9]+)\):\(([0-9]+),([0-9]+)\))");
      for (const std::string &line_str: lines) {
        std::smatch msm;
        if (!std::regex_match(line_str, msm, line_pat)) {
          errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
        } else if (msm.size() != 5) {
          errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
        } else {
          std::string row1_str = msm[1];
          std::string col1_str = msm[2];
          std::string row2_str = msm[3];
          std::string col2_str = msm[4];
          int row1;
          int col1;
          int row2;
          int col2;
          if (!wb_utils::string_to_int(row1_str, row1))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter row value");
          if (!wb_utils::string_to_int(col1_str, col1))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter col value");
          if (!wb_utils::string_to_int(row2_str, row2))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter row value");
          if (!wb_utils::string_to_int(col2_str, col2))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter col value");
          if (!errors.has_error()) {
//            Line_segment line_segment(row1, col1, row2, col2);
//            image->draw_line_segment(line_segment, foreground);
            image->draw_line_segment(row1, col1, row2, col2, foreground);
          }
        }
      }
    }
  }
  if (!errors.has_error() && saw_rectangle) {
    std::vector<std::string> rect_lines = wb_utils::tokenize(param_rectangle_str, "|");
    if (rect_lines.empty()) {
      errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
    }
    if (!errors.has_error()) {
      std::regex line_pat(R"(\(([0-9]+),([0-9]+)\):\(([0-9]+),([0-9]+)\))");
      for (const std::string &rect_line_str: rect_lines) {
        std::smatch msm;
        if (!std::regex_match(rect_line_str, msm, line_pat)) {
          errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
        } else if (msm.size() != 5) {
          errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
        } else {
          std::string row1_str = msm[1];
          std::string col1_str = msm[2];
          std::string row2_str = msm[3];
          std::string col2_str = msm[4];
          int row1;
          int col1;
          int row2;
          int col2;
          if (!wb_utils::string_to_int(row1_str, row1))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter row value");
          if (!wb_utils::string_to_int(col1_str, col1))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter col value");
          if (!wb_utils::string_to_int(row2_str, row2))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter row value");
          if (!wb_utils::string_to_int(col2_str, col2))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter col value");
          if (!errors.has_error()) {
            image->draw_rectangle(row1, col1, row2, col2, foreground);
          }
        }
      }
    }
  }
  if (!errors.has_error() && saw_rectangle_filled) {
    std::vector<std::string> rect_lines = wb_utils::tokenize(param_rectangle_filled_str, "|");
    if (rect_lines.empty()) {
      errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
    }
    if (!errors.has_error()) {
      std::regex line_pat(R"(\(([0-9]+),([0-9]+)\):\(([0-9]+),([0-9]+)\))");
      for (const std::string &rect_line_str: rect_lines) {
        std::smatch msm;
        if (!std::regex_match(rect_line_str, msm, line_pat)) {
          errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
        } else if (msm.size() != 5) {
          errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
        } else {
          std::string row1_str = msm[1];
          std::string col1_str = msm[2];
          std::string row2_str = msm[3];
          std::string col2_str = msm[4];
          int row1;
          int col1;
          int row2;
          int col2;
          if (!wb_utils::string_to_int(row1_str, row1))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter row value");
          if (!wb_utils::string_to_int(col1_str, col1))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter col value");
          if (!wb_utils::string_to_int(row2_str, row2))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter row value");
          if (!wb_utils::string_to_int(col2_str, col2))
            errors.add("Operator_transform_image_create::run", "", "invalid line parameter col value");
          if (!errors.has_error()) {
            image->draw_rectangle_filled(row1, col1, row2, col2, foreground);
          }
        }
      }
    }
  }
  if (!errors.has_error()) {
    if (output_data_store->data_format == WB_data_format::Data_format::JPEG) {
      output_data_store->write_image_jpeg(image, errors);
    } else if (output_data_store->data_format == WB_data_format::Data_format::BINARY) {
      output_data_store->write_image(image, errors);
    } else {
      errors.add("Operator_transform_image_create::run", "", "invalid data format '"
          + WB_data_format::to_string(output_data_store->data_format) + "'");
    }
  }
}