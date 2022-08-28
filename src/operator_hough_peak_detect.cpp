//
// Created by kushn on 7/23/2022.
//

#include <iostream>
#include <memory>
#include "operator_utils.hpp"
#include "operator_hough_peak_detect.hpp"

extern bool debug;

Operator_hough_peak_detect::~Operator_hough_peak_detect() = default;
void Operator_hough_peak_detect::run(std::list<Data_source_descriptor *> &input_data_sources,
                                     std::list<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters,
                                     std::list<WB_log_entry> &log_entries,
                                     Errors &errors) {
  if (debug) {
    std::cout << "Operator_hough_peak_detect::run parameters: "
              << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
  }
  if (input_data_sources.empty())
    errors.add("Operator_hough_peak_detect::run", "", "input data source required");
  else if (input_data_sources.size() > 1)
    errors.add("Operator_hough_peak_detect::run", "", "too many input data sources");
  else if (output_data_stores.empty())
    errors.add("Operator_hough_peak_detect::run", "", "output data source required");
  int npeaks = 0;
  Operator_utils::get_int_parameter("Operator_hough_peak_detect::run",
                                    operator_parameters, "npeaks", npeaks, errors);
  Data_source_descriptor *input_data_source = input_data_sources.front();
  Hough *hough_ptr;
  if (!errors.has_error()) {
    hough_ptr = input_data_source->read_hough(errors);
    std::unique_ptr<Hough> hough(hough_ptr);
    if (!errors.has_error() && hough_ptr != nullptr)
      Histogram::find_hough_peaks(hough_ptr, npeaks);
    for (Data_source_descriptor *hough_output_data_store: output_data_stores)
      hough_output_data_store->write_operator_hough_peaks(hough.get(),
                                                          "Operator_histOperator_hough_peak_detectogram_hough_create::run",
                                                          errors);
  }
}

