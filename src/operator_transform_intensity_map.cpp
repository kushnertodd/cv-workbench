//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include "operator_transform_intensity_map.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

//

extern bool debug;

Operator_transform_intensity_map::Operator_transform_intensity_map() {}

/**
   create new image from an existing image
   parameters:
     depth_enum depth
       depth of output image
       optional: defaults to input image depth
         cv_enums::CV_8U   unsigned byte
         cv_enums::CV_32S  int
         cv_enums::CV_32F  float
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
void Operator_transform_intensity_map::run(std::list<Data_source_descriptor *> &input_data_sources,
                                           std::list<Data_source_descriptor *> &output_data_stores,
                                           String_map &operator_parameters,
                                           Errors &errors) {

  if (debug) {
    std::cout << "Operator_transform_intensity_map::run:parameters: "
         << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.size() == 0)
    errors.add("Operator_transform_intensity_map::run:transform-intensity-map: missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_transform_intensity_map::run:transform-intensity-map: too many input data sources");
  if (output_data_stores.size() == 0)
    errors.add("Operator_transform_intensity_map::run:transform-intensity-map: missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_transform_intensity_map::run:transform-intensity-map: too many output data sources");
  cv_enums::CV_image_depth depth;
  double lower_in;
  double upper_in;
  double lower_out;
  double upper_out;
  bool saw_depth = false;
  bool saw_lower_in = false;
  bool saw_upper_in = false;
  bool saw_lower_out = false;
  bool saw_upper_out = false;
  if (Operator_utils::has_parameter(operator_parameters, "depth")) {
    saw_depth = true;
    std::string depth_str = Operator_utils::get_parameter(operator_parameters, "depth");
    depth = Workbench_utils::string_to_image_depth_enum(depth_str);
    if (depth == cv_enums::UNDEFINED_IMAGE_DEPTH) {
      errors.add("Operator_transform_intensity_map::run: undefined depth value");
    }
  }
  if (Operator_utils::has_parameter(operator_parameters, "lower_in")) {
    saw_lower_in = true;
    Operator_utils::get_real_parameter("Operator_transform_intensity_map::run",
                                       operator_parameters, "lower_in", lower_in, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "upper_in")) {
    saw_upper_in = true;
    Operator_utils::get_real_parameter("Operator_transform_intensity_map::run",
                                       operator_parameters, "upper_in", upper_in, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "lower_out")) {
    saw_lower_out = true;
    Operator_utils::get_real_parameter("Operator_transform_intensity_map::run",
                                       operator_parameters, "lower_out", lower_out, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "upper_out")) {
    saw_upper_out = true;
    Operator_utils::get_real_parameter("Operator_transform_intensity_map::run",
                                       operator_parameters, "upper_out", upper_out, errors);
  }
  bool no_parameters = false;
  if (!saw_lower_in && !saw_upper_in && !saw_lower_out && !saw_upper_out) {
    no_parameters = true;
  } else {
    if (!saw_lower_in) {
      errors.add("Operator_transform_intensity_map::run: missing 'lower_in' parameters");
    }
    if (!saw_upper_in) {
      errors.add("Operator_transform_intensity_map::run: missing 'upper_in' parameters");
    }
    if (!saw_lower_out) {
      errors.add("Operator_transform_intensity_map::run: missing 'lower_out' parameters");
    }
    if (!saw_upper_out) {
      errors.add("Operator_transform_intensity_map::run: missing 'upper_out' parameters");
    }
  }
  Image *input;
  Data_source_descriptor *input_data_source;
  Data_source_descriptor *output_data_store;
  if (errors.error_ct == 0) {
    input_data_source = input_data_sources.front();
    output_data_store = output_data_stores.front();
    input = input_data_source->read_image(errors);
  }
  if (errors.error_ct == 0) {
    int rows = input->get_rows();
    int cols = input->get_cols();
    if (!saw_depth) {
      depth = input->get_depth();
    }
    Image *output = Image::clone_image(input, depth);
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        if (no_parameters) {
          output->set(row, col, input->get(row, col));
        } else {
          output->set(row, col, input->get_scaled(row, col, lower_in, upper_in, lower_out, upper_out));
        }
      }
    }
    output_data_store->write_image(output, errors);
  }
}