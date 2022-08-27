//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <memory>
#include "operator_transform_intensity_map.hpp"
#include "operator_utils.hpp"
#include "wb_data_format.hpp"
#include "wb_image_depth.hpp"
#include "wb_defs.hpp"

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
void Operator_transform_intensity_map::run(std::list<Data_source_descriptor *> &input_data_sources,
                                           std::list<Data_source_descriptor *> &output_data_stores,
                                           String_map &operator_parameters,
                                           std::list<WB_log_entry> &log_entries,
                                           Errors &errors) {

  if (input_data_sources.empty())
    errors.add("Operator_transform_intensity_map::run", "", "input data source required");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_transform_intensity_map::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_transform_intensity_map::run", "", "output data source required");
  std::string depth_str;
  bool saw_depth = Operator_utils::get_string_parameter("Operator_transform_intensity_map::run",
                                                        operator_parameters,
                                                        "depth",
                                                        depth_str, errors);

  WB_image_depth::Image_depth depth;
  if (!errors.has_error()) {
    depth = WB_image_depth::from_string(depth_str);
    if (depth == WB_image_depth::Image_depth::UNDEFINED) {
      errors.add("Operator_transform_intensity_map::run", "", "undefined depth value");
    }
  }
  double lower_in;
  Operator_utils::get_real_parameter("Operator_transform_intensity_map::run",
                                     operator_parameters, "lower_in", lower_in, errors);
  double upper_in;
  Operator_utils::get_real_parameter("Operator_transform_intensity_map::run",
                                     operator_parameters, "upper_in", upper_in, errors);
  double lower_out;
  Operator_utils::get_real_parameter("Operator_transform_intensity_map::run",
                                     operator_parameters, "lower_out", lower_out, errors);
  double upper_out;
  Operator_utils::get_real_parameter("Operator_transform_intensity_map::run",
                                     operator_parameters, "upper_out", upper_out, errors);
  Data_source_descriptor *input_data_source = input_data_sources.front();
  Image *input_ptr = nullptr;
  if (!errors.has_error())
    input_ptr = input_data_source->read_image(errors);
  std::unique_ptr<Image> input(input_ptr);
  if (!errors.has_error() && input_ptr != nullptr)
    input->check_grayscale("Operator_transform_intensity_map::run", errors);
  if (!errors.has_error() && input_ptr != nullptr) {
    if (!saw_depth) {
      depth = input->get_depth();
    }
    Image *output_image_ptr = nullptr;
    if (!errors.has_error())
      for (Data_source_descriptor *output_data_store: output_data_stores) {
        if (output_data_store->data_format == WB_data_format::Data_format::JPEG) {
          output_image_ptr =
              Image::scale_image(input.get(),
                                 lower_in,
                                 upper_in,
                                 lower_out,
                                 upper_out,
                                 WB_image_depth::Image_depth::CV_8U);
          std::unique_ptr<Image> output_image(output_image_ptr);
          output_data_store->write_image_jpeg(output_image.get(), errors);
          if (!errors.has_error() && output_image_ptr != nullptr)
            output_image->log(log_entries);
        } else if (output_data_store->data_format == WB_data_format::Data_format::BINARY) {
          output_image_ptr =
              Image::scale_image(input.get(), lower_in, upper_in, lower_out, upper_out, depth);
          std::unique_ptr<Image> output_image(output_image_ptr);
          output_data_store->write_image(output_image.get(), errors);
          if (!errors.has_error() && output_image_ptr != nullptr)
            output_image->log(log_entries);
        }
      }
  }
}