//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "morphology.hpp"
#include "operator_utils.hpp"
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
  if (input_data_sources.empty())
    errors.add("Operator_filter_image_morphology::run", "", "input data source required");
  if (input_data_sources.size() > 1)
    errors.add("Operator_filter_image_morphology::run", "", "too many input data sources");
  if (output_data_stores.empty())
    errors.add("Operator_filter_image_morphology::run", "", "output data source required");
  int height;
  Operator_utils::get_int_parameter("Operator_filter_image_morphology::run",
                                    operator_parameters, "height", height, errors);
  int width;
  Operator_utils::get_int_parameter("Operator_filter_image_morphology::run",
                                    operator_parameters, "width", width, errors);
  std::string structuring_element_type_str;
  bool structuring_element_type_found =
      Operator_utils::get_string_parameter("Operator_filter_image_morphology::run",
                                           operator_parameters,
                                           "structuring-element",
                                           structuring_element_type_str, errors);
  WB_morphology_types::Structuring_element_type structuring_element_type;
  int thickness;
  if (structuring_element_type_found && !errors.has_error()) {
    structuring_element_type =
        WB_morphology_types::from_structuring_element_type_string(structuring_element_type_str);
    if (structuring_element_type == WB_morphology_types::Structuring_element_type::UNDEFINED)
      errors.add("Operator_filter_image_morphology::run", "",
                 "unknown structuring-element: " + structuring_element_type_str);
    else if (structuring_element_type == WB_morphology_types::Structuring_element_type::CROSS)
      Operator_utils::get_int_parameter("Operator_filter_image_morphology::run",
                                        operator_parameters, "thickness", thickness, errors);
  }
  std::string operation_str;
  bool operation_found = Operator_utils::get_string_parameter("Operator_filter_image_morphology::run",
                                                              operator_parameters,
                                                              "operation",
                                                              operation_str, errors);
  Image *input_ptr;
  if (operation_found && !errors.has_error()) {
    Data_source_descriptor *input_data_source = input_data_sources.front();
    input_ptr = input_data_source->read_operator_image("Operator_filter_image_morphology::run", errors);
    std::unique_ptr<Image> input(input_ptr);
    if (!errors.has_error() && input_ptr != nullptr)
      input->check_grayscale("Operator_filter_image_morphology::run", errors);
    if (!errors.has_error() && input_ptr != nullptr) {
      if (operation_str == "erode") {
        std::unique_ptr<Image>
            erode_image(Morphology::erode(input.get(), structuring_element_type,
                                          height, width, thickness, errors));
        if (!errors.has_error())
          for (Data_source_descriptor *output_data_store: output_data_stores)
            output_data_store->write_operator_image(erode_image.get(),
                                                    "Operator_filter_image_morphology::run", errors);
        if (!errors.has_error()) erode_image->log(log_entries);
      } else if (operation_str == "dilate") {
        std::unique_ptr<Image>
            dilate_image(Morphology::dilate(input.get(), structuring_element_type,
                                            height, width, thickness, errors));
        if (!errors.has_error())
          for (Data_source_descriptor *output_data_store: output_data_stores)
            output_data_store->write_operator_image(dilate_image.get(),
                                                    "Operator_filter_image_morphology::run",
                                                    errors);
        if (!errors.has_error()) dilate_image->log(log_entries);
      } else if (operation_str == "open") {
        std::unique_ptr<Image>
            open_image(Morphology::open(input.get(), structuring_element_type,
                                        height, width, thickness, errors));
        if (!errors.has_error())
          for (Data_source_descriptor *output_data_store: output_data_stores)
            output_data_store->write_operator_image(open_image.get(),
                                                    "Operator_filter_image_morphology::run", errors);
        if (!errors.has_error()) open_image->log(log_entries);
      } else if (operation_str == "close") {
        std::unique_ptr<Image>
            close_image(Morphology::close(input.get(), structuring_element_type,
                                          height, width, thickness, errors));
        if (!errors.has_error())
          for (Data_source_descriptor *output_data_store: output_data_stores)
            output_data_store->write_operator_image(close_image.get(),
                                                    "Operator_filter_image_morphology::run", errors);
        if (!errors.has_error()) close_image->log(log_entries);
      } else if (operation_str == "gradient") {
        std::unique_ptr<Image>
            gradient_image(Morphology::gradient(input.get(), structuring_element_type,
                                                height, width, thickness, errors));
        if (!errors.has_error())
          for (Data_source_descriptor *output_data_store: output_data_stores)
            output_data_store->write_operator_image(gradient_image.get(),
                                                    "Operator_filter_image_morphology::run",
                                                    errors);
        if (!errors.has_error()) gradient_image->log(log_entries);
      } else if (operation_str == "top-hat") {
        std::unique_ptr<Image>
            top_hat_image(Morphology::top_hat(input.get(), structuring_element_type,
                                              height, width, thickness, errors));
        if (!errors.has_error())
          for (Data_source_descriptor *output_data_store: output_data_stores)
            output_data_store->write_operator_image(top_hat_image.get(),
                                                    "Operator_filter_image_morphology::run",
                                                    errors);
        if (!errors.has_error()) top_hat_image->log(log_entries);
      } else if (operation_str == "black-hat") {
        std::unique_ptr<Image>
            black_hat_image
            (Morphology::black_hat(input.get(), structuring_element_type,
                                   height, width, thickness, errors));
        if (!errors.has_error())
          for (Data_source_descriptor *output_data_store: output_data_stores)
            output_data_store->write_operator_image(black_hat_image.get(),
                                                    "Operator_filter_image_morphology::run",
                                                    errors);
        if (!errors.has_error()) black_hat_image->log(log_entries);
      } else
        errors.add("Operator_filter_image_morphology::run", "",
                   "unknown operation " + operation_str);
    }
  }
}
