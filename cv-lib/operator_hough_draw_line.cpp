#include "operator_hough_draw_line.hpp"
#include <iostream>
#include "hough.hpp"
#include "operator_utils.hpp"
#include "wb_window.hpp"

extern bool debug;

/**
 * theta_inc: hough accumulator theta increment (no. thetas = 180/theta_inc)
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_hough_draw_line::run(std::list<Data_source_descriptor *> &input_data_sources,
                                   std::list<Data_source_descriptor *> &output_data_stores,
                                   String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                   Errors &errors) {
    if (debug)
        std::cout << "Operator_hough_draw_line::run parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    if (input_data_sources.size() != 2)
        errors.add("Operator_hough_draw_line::run", "", "two input data sources required");
    else if (output_data_stores.size() != 1)
        errors.add("Operator_hough_draw_line::run", "", "one output data source required");
    Data_source_descriptor *input_data_source = nullptr;
    Data_source_descriptor *input_image_source = nullptr;
    Data_source_descriptor *output_image_store = nullptr;
    if (!errors.has_error()) {
        input_data_source = input_data_sources.front();
        input_data_sources.pop_front();
        input_image_source = input_data_sources.front();
        output_image_store = output_data_stores.front();
    }
    double pixel_value = 255.0;
    int out_component = 1;
    if (!errors.has_error()) {
        if (Operator_utils::has_parameter(operator_parameters, "pixel-value"))
            Operator_utils::get_real_parameter("Operator_hough_draw_line::run", operator_parameters, "pixel-value",
                                               pixel_value, errors);
        if (Operator_utils::has_parameter(operator_parameters, "out-component"))
            Operator_utils::get_int_parameter("Operator_hough_draw_line::run", operator_parameters, "out-component",
                                              out_component, errors);
    }
    Data *input_data_ptr = nullptr;
    if (!errors.has_error())
        input_data_ptr = input_data_source->read_operator_data("Operator_transform_image_create::run", errors);
    std::unique_ptr<Data> input_data(input_data_ptr);
    Image *input_image_ptr = nullptr;
    if (!errors.has_error())
        input_image_ptr = input_image_source->read_operator_image("Operator_hough_draw_line::run", errors);
    std::unique_ptr<Image> input_image(input_image_ptr);
    if (!errors.has_error())
        input_image->check_grayscale("Operator_hough_draw_line::run", errors);
    WB_window *window_ptr = nullptr;
    if (!errors.has_error()) {
        int ncols = input_image->get_ncols();
        int nrows = input_image->get_nrows();
        double x_min = input_image->to_x(0);
        double y_max = input_image->to_y(0);
        double x_max = input_image->to_x(ncols - 1);
        double y_min = input_image->to_y(nrows - 1);
        window_ptr = new WB_window(x_min, y_min, x_max, y_max);
    }
    std::unique_ptr<WB_window> window(window_ptr);
    if (!errors.has_error())
        for (std::string line: input_data->lines) {
            std::vector<std::string> params = wb_utils::tokenize(line, " ");
            if (params.size() != 2)
                errors.add("Operator_hough_draw_line::run", "", "invalid draw command: '" + line + "'");
            double rho{};
            int theta{};
            if (!errors.has_error())
                if (!wb_utils::string_to_double(params[0], rho))
                    errors.add("Operator_hough_draw_line::run", "", "invalid point parameter rho value");
            if (!errors.has_error())
                if (!wb_utils::string_to_int(params[1], theta))
                    errors.add("Operator_hough_draw_line::run", "", "invalid point parameter theta value");
            if (!errors.has_error()) {
                Polar_line polar_line(rho, theta);
                Line_segment line_segment;
                if (!window->clip_window(polar_line, line_segment))
                    // errors.add("Operator_hough_draw_line::run", "",
                    //            "failed clipping polar line (" + polar_line.to_string() + ") against window " +
                    //                    window->to_string());
                    std::cout << "Operator_hough_draw_line::run: failed clipping polar line (" +
                                         polar_line.to_string() + ") against window " + window->to_string()
                              << std::endl;
                else {
                    Image_line_segment image_line_segment;
                    input_image->to_image_line_segment(image_line_segment, line_segment);
                    input_image->draw_line_segment(image_line_segment, pixel_value);
                }
            }
        }
    if (!errors.has_error())
        if (input_image_source->data_format == WB_data_format::Data_format::JPEG) {
            output_image_store->write_image_jpeg(input_image.get(), errors);
        } else if (input_image_source->data_format == WB_data_format::Data_format::BINARY) {
            output_image_store->write_image(input_image.get(), errors);
        } else {
            errors.add("Operator_hough_draw_line::run", "",
                       "invalid data format '" + WB_data_format::to_string(output_image_store->data_format) + "'");
        }
}
