#include "operator_histogram_peak_detect.hpp"

/**
 * @brief
 */
Operator_histogram_peak_detect::~Operator_histogram_peak_detect() = default;
/**
 * @brief
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param log_entries
 * @param errors
 */
void Operator_histogram_peak_detect::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                         std::vector<Data_source_descriptor *> &output_data_stores,
                                         String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                         Errors &errors) {
    errors.add("", "", "Operator histogram_peak_detect not yet implemented");
}
