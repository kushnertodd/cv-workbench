#include "operator_histogram_image_create.hpp"
#include <iostream>
#include "berkeley_db_data_source_descriptor.hpp"
#include "operator_utils.hpp"

extern bool debug;

/**
 * @brief
 */
Operator_histogram_image_create::~Operator_histogram_image_create() = default;
/**
 * theta_inc: histogram accumulator theta increment (no. thetas = 180/theta_inc)
 *
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
void Operator_histogram_image_create::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                          std::vector<Data_source_descriptor *> &output_data_stores,
                                          String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                          Errors &errors) {
    if (debug) {
        std::cout << "Operator_histogram_image_create::run parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.size() != 1)
        errors.add("Operator_histogram_image_create::run", "", "one input data source required");
    if (output_data_stores.empty())
        errors.add("Operator_histogram_image_create::run", "", "output data source required");

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
        Data_source_descriptor *input_data_source = input_data_sources[0];
        Image *input_image = input_data_source->read_operator_image("Operator_histogram_image_create::run", errors);
        if (!errors.has_error() && input_image != nullptr)
            input_image->check_grayscale("Operator_histogram_image_create::run", errors);
        if (!errors.has_error()) {
            std::unique_ptr<Histogram> histogram(Histogram::create_image(
                    input_image, nbins, lower_value, saw_lower_value, upper_value, saw_upper_value));
            for (Data_source_descriptor *histogram_output_data_store: output_data_stores) {
                histogram_output_data_store->write_operator_histogram(histogram.get(),
                                                                      "Operator_histogram_image_create::run", errors);
            }
            if (!errors.has_error())
                histogram->log(log_entries);
        }
    }
}
