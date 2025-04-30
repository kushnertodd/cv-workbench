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
    if (input_data_sources.empty())
        errors.add("Operator_hough_image_create::run", "", "input data source required");
    else if (input_data_sources.size() > 1)
        errors.add("Operator_hough_image_create::run", "", "too many input data sources");
    else if (output_data_stores.empty())
        errors.add("Operator_hough_image_create::run", "", "output data source required");
    int rho_inc = 0;
    int theta_inc = 0;
    int threshold = 0;
    int ulc_row = 0;
    int ulc_col = 0;
    int lrc_row = 0;
    int lrc_col = 0;
    bool saw_rho_inc = false;
    bool saw_theta_inc = false;
    bool saw_threshold = false;
    bool saw_lrc_row = false;
    bool saw_lrc_col = false;
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
                                          threshold, errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "ulc-row")) {
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "ulc-row", ulc_row,
                                          errors);
    } else
        ulc_row = 0;
    if (Operator_utils::has_parameter(operator_parameters, "ulc-col")) {
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "ulc-col", ulc_col,
                                          errors);
    } else
        ulc_col = 0;
    if (Operator_utils::has_parameter(operator_parameters, "lrc-row")) {
        saw_lrc_row = true;
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "lrc-row", lrc_row,
                                          errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "lrc-col")) {
        saw_lrc_col = true;
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "lrc_col", lrc_col,
                                          errors);
    }
    if (!saw_theta_inc) {
        errors.add("Operator_hough_image_create::run", "", "missing 'theta_inc' parameter");
    }
    if (!saw_threshold) {
        errors.add("Operator_hough_image_create::run", "", "missing 'threshold' parameter");
    }
    Data_source_descriptor *input_data_source = input_data_sources.front();
    Image *input_ptr = nullptr;
    Hough *hough_ptr = nullptr;
    if (!errors.has_error())
        input_ptr = input_data_source->read_operator_image("Operator_hough_image_create::run", errors);
    std::unique_ptr<Image> input(input_ptr);
    if (!errors.has_error() && input_ptr != nullptr)
        input->check_grayscale("Operator_hough_image_create::run", errors);
    if (!errors.has_error() && input_ptr != nullptr) {
        if (!saw_lrc_col)
            lrc_col = input->get_ncols() - 1;
        if (!saw_lrc_row)
            lrc_row = input->get_nrows() - 1;
        hough_ptr = Hough::create_image(input.get(), rho_inc, theta_inc, threshold);
    }
    std::unique_ptr<Hough> output(hough_ptr);
    if (!errors.has_error() && hough_ptr != nullptr)
        for (Data_source_descriptor *hough_output_data_store: output_data_stores)
            hough_output_data_store->write_operator_hough(hough, "Operator_hough_image_create::run", errors);
    // if (!errors.has_error() && hough_ptr != nullptr)
    //     hough_ptr->log(log_entries);
}
