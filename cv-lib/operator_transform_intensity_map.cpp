#include "operator_transform_intensity_map.hpp"
#include <iostream>
#include "image_depth.hpp"
#include "operator_utils.hpp"
#include "wb_data_format.hpp"
#include "wb_defs.hpp"

extern bool debug;

/**
 * @brief
 */
Operator_transform_intensity_map::~Operator_transform_intensity_map() = default;
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
void Operator_transform_intensity_map::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                           std::vector<Data_source_descriptor *> &output_data_stores,
                                           String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                           Errors &errors) {
    if (debug) {
        std::cout << "Operator_transform_intensity_map::run:parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.size() != 1)
        errors.add("Operator_transform_intensity_map::run", "", "one input data source required");
    else if (output_data_stores.empty())
        errors.add("Operator_transform_intensity_map::run", "", "at least one output data source required");

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
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources[0];
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_transform_intensity_map::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_transform_intensity_map::run", errors);
        if (!errors.has_error()) {
            if (!saw_lower_out)
                lower_out = 0;
            if (!saw_upper_out)
                upper_out = 255;
            if (!saw_depth)
                depth = input_image->get_depth();
            Variance_stats stats;
            input_image->get_stats(stats);
            if (saw_standard_deviations) {
                lower_in = std::max(stats.get_mean() - standard_deviations * stats.get_standard_deviation(),
                                    stats.get_min_value());
                upper_in = std::min(stats.get_mean() + standard_deviations * stats.get_standard_deviation(),
                                    stats.get_max_value());
            } else {
                if (!saw_lower_in)
                    lower_in = stats.get_min_value();
                if (!saw_upper_in)
                    upper_in = stats.get_max_value();
            }
            Data_source_descriptor *output_data_store = output_data_stores[0];
            if (output_data_store->data_format == WB_data_format::Data_format::JPEG) {
                std::unique_ptr<Image> output_image(Image::scale_image(input_image.get(), lower_in, upper_in, lower_out,
                                                                       upper_out, Image_depth::CV_8U));
                output_data_store->write_image_jpeg(output_image.get(), errors);
                if (!errors.has_error())
                    output_image->log(log_entries);
            } else if (output_data_store->data_format == WB_data_format::Data_format::BINARY) {
                std::unique_ptr<Image> output_image(
                        Image::scale_image(input_image.get(), lower_in, upper_in, lower_out, upper_out, depth));
                output_data_store->write_image(output_image.get(), errors);
                if (!errors.has_error())
                    output_image->log(log_entries);
            } else {
                errors.add("Operator_transform_intensity_map::run", "",
                           "invalid data format '" + WB_data_format::to_string(output_data_store->data_format) + "'");
            }
        }
    }
}
