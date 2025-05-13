#include "operator_hough_image_create.hpp"
#include <iostream>
#include "hough.hpp"
#include "operator_utils.hpp"

extern bool debug;

/**
 * theta_inc: hough accumulator theta increment (no. thetas = 180/theta_inc)
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_hough_image_create::run(std::list<Data_source_descriptor *> &input_data_sources,
                                      std::list<Data_source_descriptor *> &output_data_stores,
                                      String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                      Errors &errors) {
    if (debug) {
        std::cout << "Operator_hough_image_create::run parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.size() != 1)
        errors.add("Operator_hough_image_create::run", "", "one input data source required");
    else if (output_data_stores.empty())
        errors.add("Operator_hough_image_create::run", "", "output data source required");
    int rho_inc = 0;
    int theta_inc = 0;
    int pixel_threshold = 0;
    bool saw_rho_inc = false;
    bool saw_theta_inc = false;
    bool saw_threshold = false;
    if (Operator_utils::has_parameter(operator_parameters, "rho-inc")) {
        saw_rho_inc = true;
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "rho-inc", rho_inc,
                                          errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "theta-inc")) {
        saw_theta_inc = true;
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "theta-inc",
                                          theta_inc, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "pixel-threshold")) {
        saw_threshold = true;
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "pixel-threshold",
                                          pixel_threshold, errors);
    }
    if (!saw_rho_inc) {
        rho_inc = 1;
        // errors.add("Operator_hough_image_create::run", "", "missing 'rho-inc' parameter");
    }
    if (!saw_theta_inc) {
        theta_inc = 3;
        // errors.add("Operator_hough_image_create::run", "", "missing 'theta-inc' parameter");
    }
    if (!saw_threshold) {
        pixel_threshold = 0;
        // errors.add("Operator_hough_image_create::run", "", "missing 'threshold' parameter");
    }
    Data_source_descriptor *input_data_source = input_data_sources.front();
    if (!errors.has_error()) {
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_hough_image_create::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_hough_image_create::run", errors);
        if (!errors.has_error()) {
            std::unique_ptr<Hough> hough = std::unique_ptr<Hough>(
                    new Hough(input_image->to_x(0), input_image->to_x(input_image->get_ncols()), input_image->to_y(0),
                              input_image->to_y(input_image->get_ncols()), rho_inc, theta_inc, pixel_threshold));
            hough->initialize(input_image.get(), pixel_threshold);
            if (!errors.has_error())
                for (Data_source_descriptor *hough_output_data_store: output_data_stores)
                    hough_output_data_store->write_operator_hough(hough.get(), "Operator_hough_image_create::run",
                                                                  errors);
            if (!errors.has_error())
                hough->log(log_entries);
        }
    }
}
