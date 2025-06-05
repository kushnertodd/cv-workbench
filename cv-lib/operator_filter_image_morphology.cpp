#include "operator_filter_image_morphology.hpp"
#include <iostream>
#include <memory>
#include "kernel.hpp"
#include "morphology.hpp"
#include "operator_utils.hpp"

extern bool debug;

/**
 * @brief
 */
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
void Operator_filter_image_morphology::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                           std::vector<Data_source_descriptor *> &output_data_stores,
                                           String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                           Errors &errors) {

    if (input_data_sources.size() != 1)
        errors.add("Operator_filter_image_morphology::run", "", "one input data source required");
    if (output_data_stores.empty())
        errors.add("Operator_filter_image_morphology::run", "", "output data source required");
    int height{};
    Operator_utils::get_int_parameter("Operator_filter_image_morphology::run", operator_parameters, "height", height,
                                      errors);
    int width{};
    Operator_utils::get_int_parameter("Operator_filter_image_morphology::run", operator_parameters, "width", width,
                                      errors);
    if (!Operator_utils::has_parameter(operator_parameters, "structuring-element"))
        errors.add("Operator_filter_image_morphology::run", "", "structuring-element parameter required");
    WB_morphology_types::Structuring_element_type structuring_element_type;
    int thickness{};
    std::string structuring_element_type_str =
            Operator_utils::get_parameter(operator_parameters, "structuring-element");
    structuring_element_type = WB_morphology_types::from_structuring_element_type_string(structuring_element_type_str);
    if (structuring_element_type == WB_morphology_types::Structuring_element_type::UNDEFINED)
        errors.add("Operator_filter_image_morphology::run", "", "invalid 'structuring-element' parameter");
    else if (structuring_element_type == WB_morphology_types::Structuring_element_type::CROSS)
        Operator_utils::get_int_parameter("Operator_filter_image_morphology::run", operator_parameters, "thickness",
                                          thickness, errors);
    std::string operator_str;
    if (!Operator_utils::has_parameter(operator_parameters, "operation"))
        errors.add("Operator_filter_image_morphology::run", "", "operation parameter required");
    else
        operator_str = Operator_utils::get_parameter(operator_parameters, "operation");
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources.front();
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_filter_image_morphology::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_filter_image_morphology::run", errors);
        if (!errors.has_error()) {
            if (operator_str == "erode") {
                std::unique_ptr<Image> erode_image(Morphology::erode(input_image.get(), structuring_element_type,
                                                                     height, width, thickness, errors));
                if (!errors.has_error())
                    output_data_stores.front()->write_operator_image(erode_image.get(),
                                                                     "Operator_filter_image_morphology::run", errors);
                if (!errors.has_error())
                    erode_image->log(log_entries);
            } else if (operator_str == "dilate") {
                std::unique_ptr<Image> dilate_image(Morphology::dilate(input_image.get(), structuring_element_type,
                                                                       height, width, thickness, errors));
                if (!errors.has_error())
                    output_data_stores.front()->write_operator_image(dilate_image.get(),
                                                                     "Operator_filter_image_morphology::run", errors);
                if (!errors.has_error())
                    dilate_image->log(log_entries);
            } else if (operator_str == "open") {
                std::unique_ptr<Image> open_image(Morphology::open(input_image.get(), structuring_element_type, height,
                                                                   width, thickness, errors));
                if (!errors.has_error())
                    output_data_stores.front()->write_operator_image(open_image.get(),
                                                                     "Operator_filter_image_morphology::run", errors);
                if (!errors.has_error())
                    open_image->log(log_entries);
            } else if (operator_str == "close") {
                std::unique_ptr<Image> close_image(Morphology::close(input_image.get(), structuring_element_type,
                                                                     height, width, thickness, errors));
                if (!errors.has_error())
                    output_data_stores.front()->write_operator_image(close_image.get(),
                                                                     "Operator_filter_image_morphology::run", errors);
                if (!errors.has_error())
                    close_image->log(log_entries);
            } else if (operator_str == "gradient") {
                std::unique_ptr<Image> gradient_image(Morphology::gradient(input_image.get(), structuring_element_type,
                                                                           height, width, thickness, errors));
                if (!errors.has_error())
                    output_data_stores.front()->write_operator_image(gradient_image.get(),
                                                                     "Operator_filter_image_morphology::run", errors);
                if (!errors.has_error())
                    gradient_image->log(log_entries);
            } else if (operator_str == "top-hat") {
                std::unique_ptr<Image> top_hat_image(Morphology::top_hat(input_image.get(), structuring_element_type,
                                                                         height, width, thickness, errors));
                if (!errors.has_error())
                    output_data_stores.front()->write_operator_image(top_hat_image.get(),
                                                                     "Operator_filter_image_morphology::run", errors);
                if (!errors.has_error())
                    top_hat_image->log(log_entries);
            } else if (operator_str == "black-hat") {
                std::unique_ptr<Image> black_hat_image(Morphology::black_hat(
                        input_image.get(), structuring_element_type, height, width, thickness, errors));
                if (!errors.has_error())
                    output_data_stores.front()->write_operator_image(black_hat_image.get(),
                                                                     "Operator_filter_image_morphology::run", errors);
                if (!errors.has_error())
                    black_hat_image->log(log_entries);
            } else
                errors.add("Operator_filter_image_morphology::run", "",
                           "invalid 'operation' parameter: " + operator_str);
        }
    }
}
