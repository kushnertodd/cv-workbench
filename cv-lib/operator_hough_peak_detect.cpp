#include "operator_hough_peak_detect.hpp"
#include <iostream>
#include "operator_utils.hpp"

extern bool debug;

Operator_hough_peak_detect::~Operator_hough_peak_detect() = default;
void Operator_hough_peak_detect::run(std::list<Data_source_descriptor *> &input_data_sources,
                                     std::list<Data_source_descriptor *> &output_data_stores,
                                     String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                     Errors &errors) {
    if (debug) {
        std::cout << "Operator_hough_peak_detect::run parameters: "
                  << Operator_utils::parameters_to_string(operator_parameters) << std::endl;
    }
    if (input_data_sources.size() != 1)
        errors.add("Operator_hough_peak_detect::run", "", "one input data source required");
    else if (output_data_stores.empty())
        errors.add("Operator_hough_peak_detect::run", "", "output data source required");

    int npeaks = 0;
    Operator_utils::get_int_parameter("Operator_hough_peak_detect::run", operator_parameters, "npeaks", npeaks, errors);
    if (!errors.has_error()) {
        Data_source_descriptor *input_data_source = input_data_sources.front();
        std::unique_ptr<Hough> hough(input_data_source->read_hough(errors));
        if (!errors.has_error()) {
            Histogram::find_hough_peaks(hough.get(), npeaks);
            if (!errors.has_error())
                for (Data_source_descriptor *hough_output_data_store: output_data_stores) {
                    if (hough_output_data_store->data_format == WB_data_format::Data_format::BINARY) {
                        hough_output_data_store->write_hough_peaks(hough.get(), errors);
                    } else if (hough_output_data_store->data_format == WB_data_format::Data_format::TEXT) {
                        hough_output_data_store->write_hough_peaks_text(hough.get(), errors);
                    } else {
                        errors.add("Operator_hough_peak_detect::run", "",
                                   "invalid data format " +
                                           WB_data_format::to_string(hough_output_data_store->data_format));
                    }
                    if (errors.has_error())
                        break;
                }
        }
    }
}
