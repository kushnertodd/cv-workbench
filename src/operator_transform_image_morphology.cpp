//
// Created by kushn on 7/23/2022.
//

#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "operator_utils.hpp"
#include "morphology.hpp"
#include "wb_defs.hpp"
#include "operator_transform_image_morphology.hpp"

// 2022-08-17 not used right now
Operator_transform_image_morphology::~Operator_transform_image_morphology() = default;
void Operator_transform_image_morphology::run(std::list<Data_source_descriptor *> &input_data_sources,
                                              std::list<Data_source_descriptor *> &output_data_stores,
                                              String_map &operator_parameters,
                                              std::list<WB_log_entry> &log_entries,
                                              Errors &errors) {
  if (input_data_sources.empty())
    errors.add("Operator_transform_image_morphology::run", "", "input data source required");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_transform_image_morphology::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_transform_image_morphology::run", "", "output data source required");
  else if (output_data_stores.size() > 1)
    errors.add("Operator_transform_image_morphology::run", "", "too many output data sources");
  else {
    int height;
    int width;
    int thickness;
    std::string param_height_str;
    std::string param_width_str;
    std::string param_thickness_str;

    if (Operator_utils::has_parameter(operator_parameters, "height")) {
      Operator_utils::get_int_parameter("Operator_transform_image_morphology::run",
                                        operator_parameters, "height", height, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "width")) {
      Operator_utils::get_int_parameter("Operator_transform_image_morphology::run",
                                        operator_parameters, "width", width, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "thickness")) {
      Operator_utils::get_int_parameter("Operator_transform_image_morphology::run",
                                        operator_parameters, "thickness", thickness, errors);
    }
    std::string
        param_structuring_element_str = Operator_utils::get_parameter(operator_parameters, "structuring-element");
    WB_morphology_types::Structuring_element_type structuring_element =
        WB_morphology_types::from_structuring_element_type_string(param_structuring_element_str);
    if (structuring_element == WB_morphology_types::Structuring_element_type::UNDEFINED)
      errors.add("Operator_transform_image_morphology::run", "", "invalid 'structuring-element' parameter");
    if (!Operator_utils::has_parameter(operator_parameters, "operation")) {
      errors.add("Operator_transform_image_morphology::run", "", "missing 'operation' parameter");
    } else {
      std::string param_operation_str = Operator_utils::get_parameter(operator_parameters, "operation");
      if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources.front();
        Data_source_descriptor *output_data_store = output_data_stores.front();
        Image *input = nullptr;
        Image *output = nullptr;
        if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
          input = input_data_source->read_image_jpeg(errors);
        else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
          input = input_data_source->read_image(errors);
        else
          errors.add("Operator_transform_image_morphology::run", "", "invalid data format: " +
              WB_data_format::to_string(input_data_source->data_format));
        if (!errors.has_error() && input != nullptr)
          input->check_grayscale(errors);
        if (!errors.has_error() && input != nullptr) {
          if (param_operation_str == "erode") {
            output = Morphology::erode(input, structuring_element,
                                       height, width, thickness, errors);
          } else if (param_operation_str == "dilate") {
            output = Morphology::dilate(input, structuring_element,
                                        height, width, thickness, errors);
          } else if (param_operation_str == "open") {
            output = Morphology::open(input, structuring_element,
                                      height, width, thickness, errors);
          } else if (param_operation_str == "close") {
            output = Morphology::close(input, structuring_element,
                                       height, width, thickness, errors);
          } else if (param_operation_str == "top-hat") {
            output = Morphology::top_hat(input, structuring_element,
                                         height, width, thickness, errors);
          } else if (param_operation_str == "black-hat") {
            output = Morphology::black_hat(input, structuring_element,
                                           height, width, thickness, errors);
          } else
            errors.add("Operator_transform_image_morphology::run", "", "invalid 'operation' parameter");
        }
        if (!errors.has_error() && output != nullptr) {
          output_data_store->write_image(output, errors);
        }
        if (!errors.has_error() && output != nullptr) {
          output->log(log_entries);
        }
        delete output;
        delete input;
      }
    }
  }
}
