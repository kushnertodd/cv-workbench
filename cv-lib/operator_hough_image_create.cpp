#include "operator_hough_image_create.hpp"
#include <iostream>
#include "hough.hpp"
#include "operator_utils.hpp"
#include "sub_image.hpp"

extern bool debug;

/**
 * @brief
 */
Operator_hough_image_create::~Operator_hough_image_create() = default;
/**
 * theta_inc: hough accumulator theta increment (no. thetas = 180/theta_inc)
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_hough_image_create::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                      std::vector<Data_source_descriptor *> &output_data_stores,
                                      String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                      Errors &errors) {
    if (debug) {
        std::cout << "Operator_hough_image_create::run parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.size() != 1)
        errors.add("Operator_hough_image_create::run", "", "one input data source required");
    else if (output_data_stores.empty())
        errors.add("Operator_hough_image_create::run", "", "output data source required");
    int theta_inc = 3;
    if (Operator_utils::has_parameter(operator_parameters, "theta-inc"))
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "theta-inc",
                                          theta_inc, errors);
    int pixel_threshold = 0;
    if (Operator_utils::has_parameter(operator_parameters, "pixel-threshold"))
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "pixel-threshold",
                                          pixel_threshold, errors);
    int min_theta = default_min_theta;
    if (Operator_utils::has_parameter(operator_parameters, "min-theta"))
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "min-theta",
                                          min_theta, errors);
    if (!Polar_trig::is_min_max_theta_valid(min_theta))
        errors.add("Operator_hough_image_create::run", "", "min-theta must be in range -180..179");
    int max_theta = default_max_theta;
    if (Operator_utils::has_parameter(operator_parameters, "max-theta"))
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "max-theta",
                                          max_theta, errors);
    if (!Polar_trig::is_min_max_theta_valid(max_theta))
        errors.add("Operator_hough_image_create::run", "", "max-theta must be in range -180..179");
    if (min_theta > max_theta)
        errors.add("Operator_hough_image_create::run", "", "min-theta must be at most max-theta");
    std::string accumulate_str = "unit";
    bool have_accumulate = Operator_utils::get_string_parameter("Operator_hough_image_create::run", operator_parameters,
                                                                "accumulate", accumulate_str, errors);
    if (have_accumulate && !wb_utils::string_in_list(accumulate_str, {"unit", "value"}))
        errors.add("Operator_hough_image_create::run", "", "accumulatation not unit or value");
    int nrhos{};
    bool saw_nrhos = false;
    if (Operator_utils::has_parameter(operator_parameters, "nrhos")) {
        saw_nrhos = true;
        Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "nrhos", nrhos,
                                          errors);
    }
    double rho_inc{};
    bool saw_rho_inc = false;
    if (Operator_utils::has_parameter(operator_parameters, "rho-inc")) {
        saw_rho_inc = true;
        Operator_utils::get_real_parameter("Operator_transform_image_create::run", operator_parameters, "rho-inc",
                                           rho_inc, errors);
    }
    int min_col;
    bool saw_min_col = false;
    if (Operator_utils::has_parameter(operator_parameters, "min-col")) {
        saw_min_col = true;
        Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "min-col",
                                          min_col, errors);
    }
    int min_row;
    bool saw_min_row = false;
    if (Operator_utils::has_parameter(operator_parameters, "min-row")) {
        saw_min_row = true;
        Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "min-row",
                                          min_row, errors);
    }
    int max_col;
    bool saw_max_col = false;
    if (Operator_utils::has_parameter(operator_parameters, "max-col")) {
        saw_max_col = true;
        Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "max-col",
                                          max_col, errors);
    }
    int max_row;
    bool saw_max_row = false;
    if (Operator_utils::has_parameter(operator_parameters, "max-row")) {
        saw_max_row = true;
        Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "max-row",
                                          max_row, errors);
    }
    if ((!saw_nrhos && !saw_rho_inc) || (saw_nrhos && saw_rho_inc))
        errors.add("Operator_hough_image_create::run", "", "one of nrhos and row-inc must be specified");
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources[0];
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_hough_image_create::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_hough_image_create::run", errors);
        if (!errors.has_error()) {
            bool unit = accumulate_str == "unit";
            if (!saw_min_col)
                min_col = 0;
            if (!saw_min_row)
                min_row = 0;
            if (!saw_max_col)
                max_col = input_image->get_ncols() - 1;
            if (!saw_max_row)
                max_row = input_image->get_nrows() - 1;
            std::unique_ptr<Sub_image> input_sub_image =
                    std::make_unique<Sub_image>(input_image.get(), min_col, min_row, max_col, max_row);
            std::unique_ptr<Hough> hough = std::make_unique<Hough>(
                    input_sub_image.get(), input_sub_image->get_min_x(), input_sub_image->get_max_x(),
                    input_sub_image->get_min_y(), input_sub_image->get_max_y(), saw_nrhos, nrhos, saw_rho_inc, rho_inc,
                    theta_inc, pixel_threshold, unit, min_theta, max_theta);
            hough->initialize_rhos();
            hough->initialize_accumulator();
            hough->initialize(pixel_threshold, unit, min_col, min_row, max_col, max_row, errors);
            if (!errors.has_error())
                for (Data_source_descriptor *hough_output_data_store: output_data_stores)
                    hough_output_data_store->write_operator_hough(hough.get(), "Operator_hough_image_create::run",
                                                                  errors);
            if (!errors.has_error())
                hough->log(log_entries);
        }
    }
}
