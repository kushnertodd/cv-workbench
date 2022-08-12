//
// Created by kushn on 6/14/2022.
//

#include <iostream>
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
  double rows;
  double cols;
  double background;
  double foreground;
  std::string point_str;
  std::string line_str;
  std::string rectangle_str;
  bool saw_rows = false;
  bool saw_cols = false;
  bool saw_background = false;
  bool saw_foreground = false;
  bool saw_point = false;
  bool saw_line = false;
  bool saw_rectangle = false;
  if (Operator_utils::has_parameter(operator_parameters, "rows")) {
    saw_rows = true;
    Operator_utils::get_real_parameter("Operator_transform_image_create::run",
                                       operator_parameters, "rows", rows, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "cols")) {
    saw_cols = true;
    Operator_utils::get_real_parameter("Operator_transform_image_create::run",
                                       operator_parameters, "cols", cols, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "background")) {
    saw_background = true;
    Operator_utils::get_real_parameter("Operator_transform_image_create::run",
                                       operator_parameters, "background", background, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "foreground")) {
    saw_foreground = true;
    Operator_utils::get_real_parameter("Operator_transform_image_create::run",
                                       operator_parameters, "foreground", foreground, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "point")) {
    saw_point = true;
    point_str = Operator_utils::get_parameter(operator_parameters, "point");
  }
  if (Operator_utils::has_parameter(operator_parameters, "line")) {
    saw_line = true;
    line_str = Operator_utils::get_parameter(operator_parameters, "line");
  }
  if (Operator_utils::has_parameter(operator_parameters, "rectangle")) {
    saw_rectangle = true;
    rectangle_str = Operator_utils::get_parameter(operator_parameters, "rectangle");
  }
  if (input_data_sources_missing && (!saw_rows || !saw_cols))
    errors.add("Operator_transform_image_create::run",
               "",
               "'rows' and 'cols' parameters required if no input data source");
  Image *input;
  Data_source_descriptor *input_data_source;
  Data_source_descriptor *output_data_store;
  if (!errors.has_error()) {
    input_data_source = input_data_sources.front();
    output_data_store = output_data_stores.front();
    input = input_data_source->read_image(errors);
    if (input != nullptr)
      input->check_grayscale(errors);
  }
  if (!errors.has_error()) {
    Image *output_image;// =        Image::scale_image(input, lower_in, upper_in, lower_out, upper_out, WB_image_depth::Image_depth::CV_8U);
    if (output_data_store->data_format == WB_data_format::Data_format::JPEG) {
      output_data_store->write_image_jpeg(output_image, errors);
    } else if (output_data_store->data_format == WB_data_format::Data_format::BINARY) {
      output_data_store->write_image(output_image, errors);
    } else {
      errors.add("Operator_transform_image_create::run", "", "invalid data format '"
          + WB_data_format::to_string(output_data_store->data_format) + "'");
    }
  }
}