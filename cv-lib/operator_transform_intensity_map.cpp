#include "operator_transform_intensity_map.hpp"
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
void Operator_transform_intensity_map::run(std::list<Data_source_descriptor *> &input_data_sources,
                                           std::list<Data_source_descriptor *> &output_data_stores,
                                           String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                           Errors &errors) {
    if (debug) {
        std::cout << "Operator_transform_intensity_map::run:parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.empty())
        errors.add("Operator_transform_intensity_map::run", "", "input data source required");
    else if (input_data_sources.size() > 1)
        errors.add("Operator_transform_intensity_map::run", "", "too many input data sources");
    else if (output_data_stores.empty())
        errors.add("Operator_transform_intensity_map::run", "", "output data source required");
    else if (output_data_stores.size() > 1)
        errors.add("Operator_transform_intensity_map::run", "", "too many output data sources");
    Image_depth depth;
    double lower_in;
    double upper_in;
    double lower_out;
    double upper_out;
    double standard_deviations;
    bool saw_depth = false;
    bool saw_lower_in = false;
    bool saw_upper_in = false;
    bool saw_lower_out = false;
    bool saw_upper_out = false;
    bool saw_standard_deviations = false;
    if (Operator_utils::has_parameter(operator_parameters, "depth")) {
        saw_depth = true;
        std::string depth_str = Operator_utils::get_parameter(operator_parameters, "depth");
        depth = WB_image_depth::from_string(depth_str);
        if (depth == Image_depth::UNDEFINED) {
            errors.add("Operator_transform_intensity_map::run", "", "undefined depth value");
        }
    }
    if (Operator_utils::has_parameter(operator_parameters, "standard-deviations")) {
        saw_standard_deviations = true;
        Operator_utils::get_real_parameter("Operator_transform_intensity_map::run", operator_parameters,
                                           "standard-deviations", standard_deviations, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "lower-in")) {
        saw_lower_in = true;
        Operator_utils::get_real_parameter("Operator_transform_intensity_map::run", operator_parameters, "lower-in",
                                           lower_in, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "upper-in")) {
        saw_upper_in = true;
        Operator_utils::get_real_parameter("Operator_transform_intensity_map::run", operator_parameters, "upper-in",
                                           upper_in, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "lower-out")) {
        saw_lower_out = true;
        Operator_utils::get_real_parameter("Operator_transform_intensity_map::run", operator_parameters, "lower-out",
                                           lower_out, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "upper-out")) {
        saw_upper_out = true;
        Operator_utils::get_real_parameter("Operator_transform_intensity_map::run", operator_parameters, "upper-out",
                                           upper_out, errors);
    }
    Image *input;
    Data_source_descriptor *input_data_source;
    Data_source_descriptor *output_data_store;
    if (!errors.has_error()) {
        input_data_source = input_data_sources.front();
        output_data_store = output_data_stores.front();
        input = input_data_source->read_image(errors);
        if (input != nullptr) {
            input->check_grayscale("Operator_transform_intensity_map::run", errors);
        }
        if (!saw_lower_out) {
            lower_out = 0;
        }
        if (!saw_upper_out) {
            upper_out = 255;
        }
    }
    if (!errors.has_error()) {
        if (!saw_depth) {
            depth = input->get_depth();
        }
        Variance_stats stats;
        input->get_stats(stats);
        if (saw_standard_deviations) {
            lower_in = std::max(stats.get_mean() - standard_deviations * stats.get_standard_deviation(),
                                stats.get_min_value());
            upper_in = std::min(stats.get_mean() + standard_deviations * stats.get_standard_deviation(),
                                stats.get_max_value());
        } else {
            if (!saw_lower_in) {
                lower_in = stats.get_min_value();
            }
            if (!saw_upper_in) {
                upper_in = stats.get_max_value();
            }
        }
        Image *output_image;
        if (output_data_store->data_format == WB_data_format::Data_format::JPEG) {
            output_image = Image::scale_image(input, lower_in, upper_in, lower_out, upper_out, Image_depth::CV_8U);
            output_data_store->write_image_jpeg(output_image, errors);
        } else if (output_data_store->data_format == WB_data_format::Data_format::BINARY) {
            output_image = Image::scale_image(input, lower_in, upper_in, lower_out, upper_out, depth);
            output_data_store->write_image(output_image, errors);
        } else {
            errors.add("Operator_transform_intensity_map::run", "",
                       "invalid data format '" + WB_data_format::to_string(output_data_store->data_format) + "'");
        }
        if (!errors.has_error() && output_image != nullptr)
            output_image->log(log_entries);
    }
}
