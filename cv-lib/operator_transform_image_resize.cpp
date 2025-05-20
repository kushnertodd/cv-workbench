#include "operator_transform_image_resize.hpp"
#include <iostream>
#include "image_depth.hpp"
#include "operator_utils.hpp"
#include "wb_data_format.hpp"
#include "wb_defs.hpp"

extern bool debug;

/**
 * @brief
 */
Operator_transform_image_resize::~Operator_transform_image_resize() = default;
/**
 * create new image from an existing image
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_transform_image_resize::run(std::list<Data_source_descriptor *> &input_data_sources,
                                          std::list<Data_source_descriptor *> &output_data_stores,
                                          String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                          Errors &errors) {
    if (debug) {
        std::cout << "Operator_transform_image_resize::run:parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.size() != 1)
        errors.add("Operator_transform_image_resize::run", "", "one input data source required");
    else if (output_data_stores.empty())
        errors.add("Operator_transform_image_resize::run", "", "at least one output data source required");

    int area_ncols;
    int area_nrows;

    bool saw_area_ncols = false;
    bool saw_area_nrows = false;
    if (Operator_utils::has_parameter(operator_parameters, "area-ncols")) {
        saw_area_ncols = true;
        Operator_utils::get_int_parameter("Operator_transform_image_resize::run", operator_parameters, "area-ncols",
                                          area_ncols, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "area-nrows")) {
        saw_area_nrows = true;
        Operator_utils::get_int_parameter("Operator_transform_image_resize::run", operator_parameters, "area-nrows",
                                          area_nrows, errors);
    }
    if (!saw_area_ncols) {
        errors.add("Operator_transform_image_resize::run", "", "missing 'area-ncols' parameter");
    }
    if (!saw_area_nrows) {
        errors.add("Operator_transform_image_resize::run", "", "missing 'area-nrows' parameter");
    }

    if (!Operator_utils::has_parameter(operator_parameters, "resize-type"))
        errors.add("Operator_transform_image_resize::run", "", "resize-type parameter required");
    WB_resize_types::Resize_type resize_type;
    if (!errors.has_error()) {
        std::string resize_type_str = Operator_utils::get_parameter(operator_parameters, "resize-type");
        resize_type = WB_resize_types::from_string(resize_type_str);
        if (resize_type == WB_resize_types::Resize_type::UNDEFINED)
            errors.add("Operator_transform_image_resize::run", "", "invalid 'resize-type' parameter");
    }

    if (!errors.has_error()) {
        std::unique_ptr<Image> input_image(input_data_sources.front()->read_image(errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_transform_image_resize::run", errors);
        if (!errors.has_error()) {
            std::unique_ptr<Image> output_image(
                    Image::resize(input_image.get(), area_ncols, area_nrows, WB_resize_types::Resize_type::MAX));
            output_data_stores.front()->write_image(output_image.get(), errors);
        }
    }
}
