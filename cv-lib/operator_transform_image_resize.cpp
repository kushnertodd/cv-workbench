//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include "image_depth.hpp"
#include "operator_utils.hpp"
#include "wb_data_format.hpp"
#include "wb_defs.hpp"
#include "operator_transform_image_resize.hpp"

extern bool debug;

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
    if (input_data_sources.empty())
        errors.add("Operator_transform_image_resize::run", "", "input data source required");
    else if (input_data_sources.size() > 1)
        errors.add("Operator_transform_image_resize::run", "", "too many input data sources");
    else if (output_data_stores.empty())
        errors.add("Operator_transform_image_resize::run", "", "output data source required");
    else if (output_data_stores.size() > 1)
        errors.add("Operator_transform_image_resize::run", "", "too many output data sources");
    int area_nrows;
    int area_ncols;

    bool saw_area_nrows = false;
    bool saw_area_ncols = false;
    if (Operator_utils::has_parameter(operator_parameters, "area-nrows")) {
        saw_area_nrows = true;
        Operator_utils::get_int_parameter("Operator_transform_image_resize::run", operator_parameters, "area-nrows",
                                          area_nrows, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "area-ncols")) {
        saw_area_ncols = true;
        Operator_utils::get_int_parameter("Operator_transform_image_resize::run", operator_parameters, "area-ncols",
                                          area_ncols, errors);
    }
    if (!saw_area_nrows) {
        errors.add("Operator_transform_image_resize::run", "", "missing 'area-nrows' parameter");
    }
    if (!saw_area_ncols) {
        errors.add("Operator_transform_image_resize::run", "", "missing 'area-ncols' parameter");
    }

    if (!Operator_utils::has_parameter(operator_parameters, "resize-type"))
        errors.add("Operator_filter_image_morphology::run", "", "resize-type parameter required");
    WB_resize_types::Resize_type resize_type;
    if (!errors.has_error()) {
        std::string resize_type_str = Operator_utils::get_parameter(operator_parameters, "resize-type");
        resize_type = WB_resize_types::from_string(resize_type_str);
        if (resize_type == WB_resize_types::Resize_type::UNDEFINED)
            errors.add("Operator_filter_image_morphology::run", "", "invalid 'resize-type' parameter");
    }

    Image *input;
    Data_source_descriptor *input_data_source;
    Data_source_descriptor *output_data_store;
    if (!errors.has_error()) {
        input_data_source = input_data_sources.front();
        output_data_store = output_data_stores.front();
        input = input_data_source->read_image(errors);
        if (input != nullptr) {
            input->check_grayscale("Operator_transform_image_resize::run", errors);
        }
    }
    if (!errors.has_error()) {
        Image *output_image = Image::resize(input, area_nrows, area_ncols, WB_resize_types::Resize_type::MAX);
        output_data_store->write_image(output_image, errors);
    }
}
