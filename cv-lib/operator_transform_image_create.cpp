//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <regex>
#include "operator_transform_image_create.hpp"
#include "operator_utils.hpp"

extern bool debug;

/**
   create new image from an existing image

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

  bool input_data_sources_missing = input_data_sources.empty();
  if (output_data_stores.empty())
    errors.add("Operator_transform_image_create::run", "", "output data source required");
  else {
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
      background = 0.0;
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
    Image *image = nullptr;
    Data_source_descriptor *input_data_source;
    if (input_data_sources_missing && (!saw_rows || !saw_cols))
      errors.add("Operator_transform_image_create::run",
                 "",
                 "'rows' and 'cols' parameters required if no input data source");
    if (!errors.has_error()) {
      if (input_data_sources_missing)
        image = new Image(rows, cols, 1, Image_depth::CV_32S, background);
      else {
        input_data_source = input_data_sources.front();
        image = input_data_source->read_operator_image("Operator_transform_image_create::run", errors);
        if (image != nullptr && !errors.has_error())
          image->check_grayscale("Operator_transform_image_create::run", errors);
      }
    }
    if (!errors.has_error() && saw_point) {
      std::vector<std::string> points = wb_utils::tokenize(param_point_str, "|");
      if (points.empty())
        errors.add("Operator_transform_image_create::run", "", "invalid point parameter value");
      if (!errors.has_error()) {
        std::regex point_pat("\\(([0-9]+),([0-9]+)\\)");
        for (const std::string &point_str: points) {
          std::smatch msm;
          if (!std::regex_match(point_str, msm, point_pat) || msm.size() != 3)
            errors.add("Operator_transform_image_create::run", "", "invalid point parameter value");
          else {
            std::string row_str = msm[1];
            std::string col_str = msm[2];
            int row;
            int col;
            if (!wb_utils::string_to_int(row_str, row))
              errors.add("Operator_transform_image_create::run", "", "invalid point parameter row value");
            if (!wb_utils::string_to_int(col_str, col))
              errors.add("Operator_transform_image_create::run", "", "invalid point parameter col value");
            if (!errors.has_error() && image != nullptr) {
              image->set(row, col, foreground);
            }
          }
        }
      }
    }
    if (!errors.has_error() && saw_line) {
      std::vector<std::string> lines = wb_utils::tokenize(param_line_str, "|");
      if (lines.empty())
        errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
      if (!errors.has_error()) {
        std::regex line_pat(R"(\(([0-9]+),([0-9]+)\):\(([0-9]+),([0-9]+)\))");
        for (const std::string &line_str: lines) {
          std::smatch msm;
          if (!std::regex_match(line_str, msm, line_pat))
            errors.add("Operator_transform_image_create::run",
                       "",
                       "invalid line parameter value");
          else if (msm.size() != 5)
            errors.add("Operator_transform_image_create::run",
                       "",
                       "invalid line parameter value");
          else {
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
            if (!errors.has_error() && image != nullptr) {
              image->draw_line_segment(row1, col1, row2, col2, foreground);
            }
          }
        }
      }
    }
    if (!errors.has_error() && saw_rectangle) {
      std::vector<std::string> rect_lines = wb_utils::tokenize(param_rectangle_str, "|");
      if (rect_lines.empty())
        errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
      if (!errors.has_error()) {
        std::regex line_pat(R"(\(([0-9]+),([0-9]+)\):\(([0-9]+),([0-9]+)\))");
        for (const std::string &rect_line_str: rect_lines) {
          std::smatch msm;
          if (!std::regex_match(rect_line_str, msm, line_pat))
            errors.add("Operator_transform_image_create::run",
                       "",
                       "invalid line parameter value");
          else if (msm.size() != 5)
            errors.add("Operator_transform_image_create::run",
                       "",
                       "invalid line parameter value");
          else {
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
            if (!errors.has_error() && image != nullptr) {
              image->draw_rectangle(row1, col1, row2, col2, foreground);
            }
          }
        }
      }
    }
    if (!errors.has_error() && saw_rectangle_filled) {
      std::vector<std::string> rect_lines = wb_utils::tokenize(param_rectangle_filled_str, "|");
      if (rect_lines.empty())
        errors.add("Operator_transform_image_create::run", "", "invalid line parameter value");
      if (!errors.has_error()) {
        std::regex line_pat(R"(\(([0-9]+),([0-9]+)\):\(([0-9]+),([0-9]+)\))");
        for (const std::string &rect_line_str: rect_lines) {
          std::smatch msm;
          if (!std::regex_match(rect_line_str, msm, line_pat))
            errors.add("Operator_transform_image_create::run",
                       "",
                       "invalid line parameter value");
          else if (msm.size() != 5)
            errors.add("Operator_transform_image_create::run",
                       "",
                       "invalid line parameter value");
          else {
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
            if (!errors.has_error() && image != nullptr)
              image->draw_rectangle_filled(row1,
                                           col1,
                                           row2,
                                           col2,
                                           foreground);
          }
        }
      }
    }
    if (!errors.has_error())
      for (Data_source_descriptor *output_data_store: output_data_stores)
        output_data_store->write_operator_image(image, "Operator_hough_image_create::run", errors);
  }
}