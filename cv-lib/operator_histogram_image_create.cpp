#include "operator_histogram_image_create.hpp"
#include <iostream>
#include "berkeley_db_data_source_descriptor.hpp"
#include "operator_utils.hpp"

extern bool debug;

/**
 * theta_inc: histogram accumulator theta increment (no. thetas = 180/theta_inc)
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_histogram_image_create::run(std::list<Data_source_descriptor *> &input_data_sources,
                                          std::list<Data_source_descriptor *> &output_data_stores,
                                          String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                          Errors &errors) {
    if (debug) {
        std::cout << "Operator_histogram_image_create::run parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.empty())
        errors.add("Operator_histogram_image_create::run", "", "input data source required");
    else if (input_data_sources.size() > 1)
        errors.add("Operator_histogram_image_create::run", "", "too many input data sources");
    else if (output_data_stores.empty())
        errors.add("Operator_histogram_image_create::run", "", "output data source required");
    else if (output_data_stores.size() > 2)
        errors.add("Operator_histogram_image_create::run", "", "too many output data sources");
    int nbins;
    Operator_utils::get_int_parameter("Operator_histogram_image_create::run", operator_parameters, "nbins", nbins,
                                      errors);
    double lower_value;
    bool saw_lower_value = false;
    if (Operator_utils::has_parameter(operator_parameters, "lower-value")) {
        saw_lower_value = true;
        Operator_utils::get_real_parameter("Operator_histogram_image_create::run", operator_parameters, "lower-value",
                                           lower_value, errors);
    }
    double upper_value;
    bool saw_upper_value = false;
    if (Operator_utils::has_parameter(operator_parameters, "upper-value")) {
        saw_upper_value = true;
        Operator_utils::get_real_parameter("Operator_histogram_image_create::run", operator_parameters, "upper-value",
                                           upper_value, errors);
    }
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources.front();
        Image *input = input_data_source->read_operator_image("Operator_histogram_image_create::run", errors);
        if (!errors.has_error() && input != nullptr)
            input->check_grayscale("Operator_histogram_image_create::run", errors);
        if (!errors.has_error()) {
            Histogram *histogram =
                    Histogram::create_image(input, nbins, lower_value, upper_value, saw_lower_value, saw_upper_value);
            for (Data_source_descriptor *histogram_output_data_store: output_data_stores) {
                histogram_output_data_store->write_operator_histogram(histogram, "Operator_histogram_image_create::run",
                                                                      errors);
            }
            if (!errors.has_error() && histogram != nullptr)
                histogram->log(log_entries);
            delete histogram;
        }
    }
}
