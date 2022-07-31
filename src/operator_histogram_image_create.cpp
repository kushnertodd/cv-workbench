//
// Created by kushn on 7/13/2022.
//

#include <iostream>
#include "berkeley_db_data_source_descriptor.hpp"
#include "histogram.hpp"
#include "operator_utils.hpp"
#include "wb_defs.hpp"
#include "operator_histogram_image_create.hpp"

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
                                          String_map &operator_parameters,
                                          std::list<WB_log_entry> &log_entries,
                                          Errors &errors) {
  if (debug) {
    std::cout << "Operator_histogram_image_create::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_histogram_image_create::run", "", "missing input data source");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_histogram_image_create::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_histogram_image_create::run", "", "missing output data source");
  else if (output_data_stores.size() > 2)
    errors.add("Operator_histogram_image_create::run", "", "too many output data sources");
  int nbins;
  double lower_value;
  double upper_value;
  bool saw_nbins = false;
  bool saw_lower_value = false;
  bool saw_upper_value = false;
  if (Operator_utils::has_parameter(operator_parameters, "nbins")) {
    saw_nbins = true;
    Operator_utils::get_int_parameter("Operator_histogram_image_create::run",
                                      operator_parameters, "nbins", nbins, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "lower_value")) {
    saw_lower_value = true;
    Operator_utils::get_real_parameter("Operator_histogram_image_create::run",
                                       operator_parameters, "lower_value", lower_value, errors);
  }
  if (Operator_utils::has_parameter(operator_parameters, "upper_value")) {
    saw_upper_value = true;
    Operator_utils::get_real_parameter("Operator_histogram_image_create::run",
                                       operator_parameters, "upper_value", upper_value, errors);
  }
  if (!saw_nbins) {
    errors.add("Operator_histogram_image_create::run", "", "missing 'nbins' parameter");
  }
  /*
   * optional for now
  if (!saw_lower_value) {
    errors.add("Operator_histogram_image_create::run", "", "missing 'lower_value' parameter");
  }
  if (!saw_upper_value) {
    errors.add("Operator_histogram_image_create::run", "", "missing 'upper_value' parameter");
  }
   */
  if (errors.error_ct == 0) {
    Data_source_descriptor *input_data_source = input_data_sources.front();
    Image *input = nullptr;
    if (input_data_source->data_format == WB_data_format::Data_format::JPEG)
      input = input_data_source->read_image_jpeg(errors);
    else if (input_data_source->data_format == WB_data_format::Data_format::BINARY)
      input = input_data_source->read_image(errors);
    else
      errors.add("Operator_histogram_image_create::run", "", "invalid data format: " +
          WB_data_format::to_string(input_data_source->data_format));
    if (errors.error_ct == 0 && input != nullptr)
      input->check_grayscale(errors);
    if (errors.error_ct == 0) {
      Histogram *histogram = Histogram::create_image(input, nbins, lower_value, upper_value,
                                                     saw_lower_value, saw_upper_value);
      for (Data_source_descriptor *histogram_output_data_store: output_data_stores) {
        if (histogram_output_data_store->data_format == WB_data_format::Data_format::BINARY) {
          histogram_output_data_store->write_histogram(histogram, errors);
        } else if (histogram_output_data_store->data_format == WB_data_format::Data_format::TEXT) {
          histogram_output_data_store->write_histogram_text(histogram, errors);
        } else {
          errors.add("Operator_histogram_image_create::run", "", "invalid data format "
              + WB_data_format::to_string(histogram_output_data_store->data_format));
        }
      }
      if (!errors.has_error() && histogram != nullptr) {
        histogram->log(log_entries);
      }
      delete histogram;
    }
  }
}
