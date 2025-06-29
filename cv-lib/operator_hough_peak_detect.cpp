#include "operator_hough_peak_detect.hpp"
#include <iostream>
#include "operator_utils.hpp"

extern bool debug;

/**
 * @brief
 */
Operator_hough_peak_detect::~Operator_hough_peak_detect() = default;
/**
 * @brief
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param log_entries
 * @param errors
 */
void Operator_hough_peak_detect::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                     std::vector<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                     Errors &errors) {
    if (debug) {
        std::cout << "Operator_hough_peak_detect::run parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.size() != 1)
        errors.add("Operator_hough_peak_detect::run", "", "one input data source required");
    else if (output_data_stores.empty())
        errors.add("Operator_hough_peak_detect::run", "", "output data source required");

    double threshold = 0.0;
    Operator_utils::get_real_parameter("Operator_hough_peak_detect::run", operator_parameters, "threshold", threshold,
                                       errors);
    double rho_suppress = 0.0;
    Operator_utils::get_real_parameter("Operator_hough_peak_detect::run", operator_parameters, "rho_suppress",
                                       rho_suppress, errors);
    int theta_suppress = 0;
    Operator_utils::get_int_parameter("Operator_hough_peak_detect::run", operator_parameters, "theta_suppress",
                                      theta_suppress, errors);
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources[0];
        std::unique_ptr<Hough> hough(input_data_source->read_operator_hough("Operator_hough_peak_detect::run", errors));
        if (!errors.has_error()) {
            hough->find_peaks(threshold, rho_suppress, theta_suppress);
            if (!errors.has_error())
                for (Data_source_descriptor *hough_output_data_store: output_data_stores)
                    hough_output_data_store->write_operator_hough_peaks(hough.get(), "Operator_hough_peak_detect::run",
                                                                  errors);
            if (!errors.has_error())
                hough->log(log_entries);
        }
    }
}
