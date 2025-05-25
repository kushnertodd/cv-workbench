#include "operator_transform_intensity_convert.hpp"
#include <iostream>
#include "image_depth.hpp"
#include "operator_utils.hpp"
#include "wb_data_format.hpp"
#include "wb_defs.hpp"

extern bool debug;

/**
 * @brief
 */
Operator_transform_intensity_convert::~Operator_transform_intensity_convert() = default;
/**
   convert pixel values from an existing image
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_transform_intensity_convert::run(std::list<Data_source_descriptor *> &input_data_sources,
                                               std::list<Data_source_descriptor *> &output_data_stores,
                                               String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                               Errors &errors) {
    if (debug) {
        std::cout << "Operator_transform_intensity_convert::run:parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.size() != 1)
        errors.add("Operator_transform_intensity_convert::run", "", "one input data source required");
    else if (output_data_stores.empty())
        errors.add("Operator_transform_intensity_convert::run", "", "at least one output data source required");

    bool saw_function = false;
    WB_convert_types::Convert_type convert_type;
    if (Operator_utils::has_parameter(operator_parameters, "function")) {
        saw_function = true;
        std::string convert_type_str = Operator_utils::get_parameter(operator_parameters, "function");
        convert_type = WB_convert_types::from_string(convert_type_str);
        if (convert_type == WB_convert_types::Convert_type::UNDEFINED)
            errors.add("Operator_transform_intensity_convert::run", "", "invalid 'function' parameter");
    }
    if (!saw_function)
        errors.add("Operator_transform_intensity_convert::run", "", "missing 'function' parameter");
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources.front();
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_transform_intensity_convert::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_transform_intensity_convert::run", errors);
        if (!errors.has_error()) {
            std::unique_ptr<Image> output_image(Image::convert(input_image.get(), convert_type, errors));
            output_data_stores.front()->write_image(output_image.get(), errors);
        }
    }
}
