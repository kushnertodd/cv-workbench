//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <regex>
#include "operator_transform_image_combine.hpp"
#include "operator_utils.hpp"

extern bool debug;

/**
   combine new image from an existing image

 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_transform_image_combine::run(std::list<Data_source_descriptor *> &input_data_sources,
                                           std::list<Data_source_descriptor *> &output_data_stores,
                                           String_map &operator_parameters,
                                           std::list<WB_log_entry> &log_entries,
                                           Errors &errors) {

  if (debug) {
    std::cout << "Operator_transform_image_combine::run:parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_transform_image_combine::run", "", "two input data sources required");
  if (input_data_sources.size() > 2)
    errors.add("Operator_transform_image_combine::run", "", "too many input data sources");
  if (output_data_stores.empty())
    errors.add("Operator_transform_image_combine::run", "", "output data source required");
  else {
    double scale1 = 1.0;
    if (Operator_utils::has_parameter(operator_parameters, "scale-1"))
      Operator_utils::get_real_parameter("Operator_transform_image_combine::run",
                                         operator_parameters, "scale-1", scale1, errors, true);
    double scale2 = 1.0;
    if (Operator_utils::has_parameter(operator_parameters, "scale-2"))
      Operator_utils::get_real_parameter("Operator_transform_image_combine::run",
                                         operator_parameters, "scale-2", scale2, errors, true);
    double offset = 0.0;
    if (Operator_utils::has_parameter(operator_parameters, "offset"))
      Operator_utils::get_real_parameter("Operator_transform_image_combine::run",
                                         operator_parameters, "offset", offset, errors, true);
    Image *image1_ptr = nullptr;
    Image *image2_ptr = nullptr;
    bool read_image1 = false;
    bool read_image2 = false;
    for (Data_source_descriptor *input_data_source: input_data_sources) {
      if (input_data_source->id == 1) {
        read_image1 = true;
        image1_ptr = input_data_source->read_operator_image("Operator_transform_image_combine::run", errors);
      } else if (input_data_source->id == 2) {
        read_image2 = true;
        image2_ptr = input_data_source->read_operator_image("Operator_transform_image_combine::run", errors);
      }
    }
    if (!read_image1)
      errors.add("Operator_transform_image_combine::run", "", "missing input image id 1");
    if (!read_image2)
      errors.add("Operator_transform_image_combine::run", "", "missing input image id 2");
    std::unique_ptr<Image> image1(image1_ptr);
    if (!errors.has_error() && image1_ptr != nullptr)
      image1->check_grayscale("Operator_transform_image_combine::run image 1", errors);
    std::unique_ptr<Image> image2(image2_ptr);
    if (!errors.has_error() && image2_ptr != nullptr)
      image2->check_grayscale("Operator_transform_image_combine::run image 2", errors);
    Image *output_ptr = nullptr;
    if (!errors.has_error() && image1 != nullptr && image2 != nullptr)
      output_ptr = Image::combine(image1.get(), image2.get(), scale1, scale2, offset, errors);
    std::unique_ptr<Image> output(output_ptr);
    if (!errors.has_error() && output_ptr != nullptr)
      for (Data_source_descriptor *output_data_store: output_data_stores)
        output_data_store->write_operator_image(output.get(), "Operator_transform_image_combine::run", errors);
    Data_source_descriptor *output_data_store = output_data_stores.front();
    output_data_store->write_operator_image(output.get(),
                                            "Operator_transform_image_combine::run", errors);
    if (!errors.has_error() && output_ptr != nullptr)
      output->log(log_entries);
  }
}