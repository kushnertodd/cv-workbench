//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "morphology.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "operator_filter_image_morphology.hpp"

//

extern bool debug;

Operator_filter_image_morphology::~Operator_filter_image_morphology() = default;

/**
 * there are seven morphological operations. each use a structuring element as a mask.The types of masks are:
 * - rectangle
 * - cross
 * - ellipse
 * there operations are:
 * - erode     output the minimum pixel under the mask
 * - dilate    output the maximum pixel under the mask
 * - open      erode followed by dilate
 * - close     dilate followed by erode
 * - gradient  subtract the eroded image from the dilated image
 * - top-hat   subtract the input image and the opened image
 * - black-hat  subtract the closed image from the input image
 * references:
 * https://docs.opencv.org/4.x/d9/d61/tutorial_py_morphological_ops.html
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_filter_image_morphology::run(std::list<Data_source_descriptor *> &input_data_sources,
                                           std::list<Data_source_descriptor *> &output_data_stores,
                                           String_map &operator_parameters,
                                           std::list<WB_log_entry> &log_entries,
                                           Errors &errors) {

  if (debug) {
    std::cout << "Operator_filter_image_morphology::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_filter_image_morphology::run", "", "missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_filter_image_morphology::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_filter_image_morphology::run", "", "missing output data source");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_filter_image_morphology::run", "", "too many output data sources");
  else {
    WB_morphology_types::Structuring_element_type structuring_element_type;
    int height;
    int width;
    int thickness;
    std::string operator_str;
    if (!Operator_utils::has_parameter(operator_parameters, "structuring-element"))
      errors.add("Operator_filter_image_morphology::run", "", "missing 'structuring-element' parameter");
    else {
      std::string structuring_element_type_str =
          Operator_utils::get_parameter(operator_parameters, "structuring-element");
      structuring_element_type =
          WB_morphology_types::from_structuring_element_type_string(structuring_element_type_str);
      if (structuring_element_type == WB_morphology_types::Structuring_element_type::UNDEFINED)
        errors.add("Operator_filter_image_morphology::run", "", "invalid 'structuring-element' parameter");
      else if (structuring_element_type == WB_morphology_types::Structuring_element_type::CROSS)
        Operator_utils::get_int_parameter("Operator_histogram_image_create::run",
                                          operator_parameters, "thickness", thickness, errors);
    }
    if (!Operator_utils::has_parameter(operator_parameters, "operation"))
      errors.add("Operator_filter_image_morphology::run", "", "missing 'operation' parameter");
    else
      operator_str = Operator_utils::get_parameter(operator_parameters, "operation");
    Operator_utils::get_int_parameter("Operator_histogram_image_create::run",
                                      operator_parameters, "height", height, errors);
    Operator_utils::get_int_parameter("Operator_histogram_image_create::run",
                                      operator_parameters, "width", width, errors);
    if (!errors.has_error()) {
      Data_source_descriptor *input_data_source = input_data_sources.front();
      Image *input = nullptr;
      if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
        input = input_data_source->read_image_jpeg(errors);
      else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
        input = input_data_source->read_image(errors);
      else
        errors.add("Operator_filter_image_morphology::run", "", "invalid data format: " +
            WB_data_format::to_string(input_data_source->data_format));
      if (!errors.has_error() && input != nullptr)
        input->check_grayscale(errors);
      if (!errors.has_error() && input != nullptr) {
        if (operator_str == "erode") {
          std::unique_ptr<Image>
              erode_image(Morphology::erode(input, structuring_element_type, height, width, thickness, errors));
          if (!errors.has_error())
            Operator_utils::write_operator_image(output_data_stores.front(), erode_image.get(), errors);
          if (!errors.has_error()) erode_image->log(log_entries);
        } else if (operator_str == "dilate") {
          std::unique_ptr<Image>
              dilate_image(Morphology::dilate(input, structuring_element_type, height, width, thickness, errors));
          if (!errors.has_error())
            Operator_utils::write_operator_image(output_data_stores.front(), dilate_image.get(), errors);
          if (!errors.has_error()) dilate_image->log(log_entries);
        } else if (operator_str == "open") {
          std::unique_ptr<Image>
              open_image(Morphology::open(input, structuring_element_type, height, width, thickness, errors));
          if (!errors.has_error())
            Operator_utils::write_operator_image(output_data_stores.front(), open_image.get(), errors);
          if (!errors.has_error()) open_image->log(log_entries);
        } else if (operator_str == "close") {
          std::unique_ptr<Image>
              close_image(Morphology::close(input, structuring_element_type, height, width, thickness, errors));
          if (!errors.has_error())
            Operator_utils::write_operator_image(output_data_stores.front(), close_image.get(), errors);
          if (!errors.has_error()) close_image->log(log_entries);
        } else if (operator_str == "gradient") {
          std::unique_ptr<Image>
              gradient_image(Morphology::gradient(input, structuring_element_type, height, width, thickness, errors));
          if (!errors.has_error())
            Operator_utils::write_operator_image(output_data_stores.front(), gradient_image.get(), errors);
          if (!errors.has_error()) gradient_image->log(log_entries);
        } else if (operator_str == "top-hat") {
          std::unique_ptr<Image>
              top_hat_image(Morphology::top_hat(input, structuring_element_type, height, width, thickness, errors));
          if (!errors.has_error())
            Operator_utils::write_operator_image(output_data_stores.front(), top_hat_image.get(), errors);
          if (!errors.has_error()) top_hat_image->log(log_entries);
        } else if (operator_str == "black-hat") {
          std::unique_ptr<Image>
              black_hat_image(Morphology::black_hat(input, structuring_element_type, height, width, thickness, errors));
          if (!errors.has_error())
            Operator_utils::write_operator_image(output_data_stores.front(), black_hat_image.get(), errors);
          if (!errors.has_error()) black_hat_image->log(log_entries);
        } else
          errors.add("Operator_filter_image_morphology::run", "", "invalid 'operation' parameter: "+operator_str);
        delete input;
      }
    }
  }
}