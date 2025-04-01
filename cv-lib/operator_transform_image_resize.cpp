//
// Created by kushn on 6/14/2022.
//

#include "operator_transform_image_resize.hpp"
#include <iostream>
#include "image_depth.hpp"
#include "operator_utils.hpp"
#include "wb_data_format.hpp"
#include "wb_defs.hpp"

extern bool debug;

/**
   create new image from an existing image
   parameters:
     depth_enum depth
       depth of output image
       optional: defaults to input image depth
         Image_depth::CV_8U   unsigned byte
         Image_depth::CV_32S  int
         Image_depth::CV_32F  float
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
    int area_rows;
    int area_cols;

    bool saw_area_rows = false;
    bool saw_area_cols = false;
    if (Operator_utils::has_parameter(operator_parameters, "area-rows")) {
        saw_area_rows = true;
        Operator_utils::get_int_parameter("Operator_transform_image_resize::run", operator_parameters, "area-rows",
                                          area_rows, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "area-cols")) {
        saw_area_cols = true;
        Operator_utils::get_int_parameter("Operator_transform_image_resize::run", operator_parameters, "area-cols",
                                          area_cols, errors);
    }
    if (!saw_area_rows) {
        errors.add("Operator_transform_image_resize::run", "", "missing 'area-rows' parameter");
    }
    if (!saw_area_cols) {
        errors.add("Operator_transform_image_resize::run", "", "missing 'area-cols' parameter");
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
        Image *output_image = Image::resize(input, area_rows, area_cols, Resize_type::MAX);
        output_data_store->write_image(output_image, errors);
    }
}
