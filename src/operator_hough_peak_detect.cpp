//
// Created by kushn on 7/23/2022.
//

#include <iostream>
#include <memory>
#include "operator_utils.hpp"
#include "operator_hough_peak_detect.hpp"

Operator_hough_peak_detect::~Operator_hough_peak_detect() = default;
/**
 * Run hough peak detect operator
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param log_entries
 * @param errors
 */
void Operator_hough_peak_detect::run(std::list<Data_source_descriptor *> &input_data_sources,
                                     std::list<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters,
                                     std::list<WB_log_entry> &log_entries,
                                     Errors &errors) {
  if (input_data_sources.empty())
    errors.add("Operator_hough_peak_detect::run", "", "input data source required");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_hough_peak_detect::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_hough_peak_detect::run", "", "output data source required");
  int rho_size = 1;
  Operator_utils::get_int_parameter("Operator_hough_peak_detect::run",
                                    operator_parameters, "rho_size", rho_size, errors, true);
  int theta_size = 1;
  Operator_utils::get_int_parameter("Operator_hough_peak_detect::run",
                                    operator_parameters, "rho_size", theta_size, errors, true);
  int threshold_count;
  bool saw_threshold_count =
      Operator_utils::get_int_parameter("Operator_hough_peak_detect::run",
                                        operator_parameters, "threshold_count", threshold_count, errors, true);
  int threshold_difference;
  bool saw_threshold_difference =
      Operator_utils::get_int_parameter("Operator_hough_peak_detect::run",
                                        operator_parameters,
                                        "threshold_difference",
                                        threshold_difference,
                                        errors,
                                        true);
  double threshold_percentage;
  bool saw_threshold_percentage =
      Operator_utils::get_real_parameter("Operator_hough_peak_detect::run",
                                         operator_parameters,
                                         "threshold_difference",
                                         threshold_percentage,
                                         errors,
                                         true);

  Hough *hough_ptr;
  if (!errors.has_error()) {
    Data_source_descriptor *input_data_source = input_data_sources.front();
    std::unique_ptr<Hough> hough(input_data_source->read_hough(errors));
    if (!errors.has_error())
      hough->find_peaks(rho_size, theta_size);
    for (Data_source_descriptor *hough_output_data_store: output_data_stores)
      if (!errors.has_error())
        hough_output_data_store->write_operator_hough_peaks(hough.get(),
                                                            "Operator_histOperator_hough_peak_detectogram_hough_create::run",
                                                            errors);
  }
}

