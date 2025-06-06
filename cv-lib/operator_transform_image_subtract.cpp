#include "operator_transform_image_subtract.hpp"
#include <iostream>
#include <regex>
#include "operator_utils.hpp"

extern bool debug;

/**
 * @brief
 */
Operator_transform_image_subtract::~Operator_transform_image_subtract() = default;
/**
   subtract new image from an existing image

 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_transform_image_subtract::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                            std::vector<Data_source_descriptor *> &output_data_stores,
                                            String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                            Errors &errors) {
    if (debug) {
        std::cout << "Operator_transform_image_subtract::run:parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.size() != 2)
        errors.add("Operator_transform_image_subtract::run", "", "two input data sources required");
    else if (output_data_stores.empty())
        errors.add("Operator_transform_image_subtract::run", "", "output data source required");

    else {
        Image *input_image1_ptr = nullptr;
        Image *input_image2_ptr = nullptr;
        bool read_image1 = false;
        bool read_image2 = false;
        for (Data_source_descriptor *input_data_source: input_data_sources) {
            if (input_data_source->get_id() == 1) {
                read_image1 = true;
                input_image1_ptr =
                        input_data_source->read_operator_image("Operator_transform_image_subtract::run", errors);
            } else if (input_data_source->get_id() == 2) {
                read_image2 = true;
                input_image2_ptr =
                        input_data_source->read_operator_image("Operator_transform_image_subtract::run", errors);
            }
        }
        if (!read_image1)
            errors.add("Operator_transform_image_subtract::run", "", "missing input image id 1");
        if (!read_image2)
            errors.add("Operator_transform_image_subtract::run", "", "missing input image id 2");
        if (input_image1_ptr != nullptr)
            input_image1_ptr->check_grayscale("Operator_transform_image_subtract::run image 1", errors);
        if (input_image2_ptr != nullptr)
            input_image2_ptr->check_grayscale("Operator_transform_image_subtract::run image 2", errors);
        if (!errors.has_error()) {
            std::unique_ptr<Image> output_image(Image::subtract(input_image1_ptr, input_image2_ptr, errors));
            if (!errors.has_error()) {
                Data_source_descriptor *output_data_store = output_data_stores[0];
                output_data_store->write_operator_image(output_image.get(), "Operator_transform_image_subtract::run",
                                                        errors);
                if (!errors.has_error())
                    output_image->log(log_entries);
            }
        }
        delete input_image1_ptr;
        delete input_image2_ptr;
    }
}
