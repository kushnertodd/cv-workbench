#include "operator_hough_image_create.hpp"
#include <iostream>
#include "hough.hpp"
#include "operator_utils.hpp"

extern bool debug;

/**
 * @brief
 */
Operator_hough_image_create::~Operator_hough_image_create() = default;
/**
 * @brief
 * @param theta
 * @return theta in range -360..359
 */
bool Operator_hough_image_create::is_valid_min_nax_theta(int theta) {
    return (theta >= -theta_max_2pi && theta < theta_max_2pi);
}
/**
 * @brief
 * @param theta
 * @return theta in range 0..359
 */
bool Operator_hough_image_create::is_valid_theta_2pi(int theta) { return (theta >= 0 && theta < theta_max_2pi); }
/**
 * @brief
 * @param map min_max_theta in range -360..359 to 0..359
 * @return
 */
int Operator_hough_image_create::min_max_theta_to_theta_2pi(int min_max_theta) {
    assert(is_valid_min_nax_theta(min_max_theta));
    return (min_max_theta + theta_max_2pi) % theta_max_2pi;
}
/**
 * @brief
 * @param theta in range 0..359
 * @return theta in range 0..177
 */
int Operator_hough_image_create::theta_2pi_to_theta(int theta_2pi) {
    assert(is_valid_theta_2pi(theta_2pi));
    return theta_2pi > theta_pi ? theta_2pi - theta_pi : theta_2pi;
}
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
    int rho_inc = 1;
    if (Operator_utils::has_parameter(operator_parameters, "rho-inc"))
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "rho-inc", rho_inc,
                                          errors);
    int theta_inc = 3;
    if (Operator_utils::has_parameter(operator_parameters, "theta-inc"))
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "theta-inc",
                                          theta_inc, errors);
    int pixel_threshold = 0;
    if (Operator_utils::has_parameter(operator_parameters, "pixel-threshold"))
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "pixel-threshold",
                                          pixel_threshold, errors);
    int min_theta_input = default_min_theta;
    if (Operator_utils::has_parameter(operator_parameters, "min-theta"))
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "min-theta",
                                          min_theta_input, errors);
    if (!is_valid_theta_2pi(min_theta_input))
        errors.add("Operator_hough_image_create::run", "", "min-theta must be in range -360..359");
    int max_theta_input = default_max_theta;
    if (Operator_utils::has_parameter(operator_parameters, "max-theta"))
        Operator_utils::get_int_parameter("Operator_hough_image_create::run", operator_parameters, "max-theta",
                                          max_theta_input, errors);
    if (!is_valid_theta_2pi(max_theta_input))
        errors.add("Operator_hough_image_create::run", "", "max-theta must be in range -360..359");
    std::string accumulate_str = "unit";
    bool have_accumulate = Operator_utils::get_string_parameter("Operator_hough_image_create::run", operator_parameters,
                                                                "accumulate", accumulate_str, errors);
    if (have_accumulate && !wb_utils::string_in_list(accumulate_str, {"unit", "value"}))
        errors.add("Operator_hough_image_create::run", "", "accumulatation not unit or value");
    int min_col;
    int min_row;
    int max_col;
    int max_row;
    bool saw_min_col = false;
    bool saw_min_row = false;
    bool saw_max_col = false;
    bool saw_max_row = false;
    if (Operator_utils::has_parameter(operator_parameters, "min-col")) {
        saw_min_col = true;
        Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "min-col", min_col,
                                          errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "min-row")) {
        saw_min_row = true;
        Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "min-row", min_row,
                                          errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "max-col")) {
        saw_max_col = true;
        Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "max-col", max_col,
                                          errors);
    }
    if (Operator_utils::has_parameter(operator_parameters, "max-row")) {
        saw_max_row = true;
        Operator_utils::get_int_parameter("Operator_transform_image_create::run", operator_parameters, "max-row", max_row,
                                          errors);
    }
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources[0];
        std::unique_ptr<Image> input_image(
                input_data_source->read_operator_image("Operator_hough_image_create::run", errors));
        if (!errors.has_error())
            input_image->check_grayscale("Operator_hough_image_create::run", errors);
        if (!errors.has_error()) {
            bool unit = accumulate_str == "unit";
            int min_theta_2pi = min_max_theta_to_theta_2pi(min_theta_input);
            int max_theta_2pi = min_max_theta_to_theta_2pi(max_theta_input);
            int min_theta = theta_2pi_to_theta(min_theta_2pi);
            int max_theta = theta_2pi_to_theta(max_theta_2pi);
            std::unique_ptr<Hough> hough =
                    std::unique_ptr<Hough>(new Hough(input_image->to_x(0), input_image->to_x(input_image->get_ncols()),
                                                     input_image->to_y(input_image->get_nrows()), input_image->to_y(0),
                                                     rho_inc, theta_inc, pixel_threshold, unit, min_theta, max_theta));
            hough->initialize(input_image.get(), pixel_threshold, unit, min_col, saw_min_col, min_row, saw_min_row,
                              max_col, saw_max_col, max_row, saw_max_row, errors);
            if (!errors.has_error())
                for (Data_source_descriptor *hough_output_data_store: output_data_stores)
                    hough_output_data_store->write_operator_hough(hough.get(), "Operator_hough_image_create::run",
                                                                  errors);
            if (!errors.has_error())
                hough->log(log_entries);
        }
    }
}
