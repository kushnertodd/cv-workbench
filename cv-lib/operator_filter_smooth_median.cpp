#include "operator_filter_smooth_median.hpp"

/**
 * @brief
 */
Operator_filter_smooth_median::~Operator_filter_smooth_median() = default;
/**
 * @brief
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param log_entries
 * @param errors
 */
void Operator_filter_smooth_median::run(std::vector<Data_source_descriptor *> &input_data_sources,
                                        std::vector<Data_source_descriptor *> &output_data_stores,
                                        String_map &operator_parameters, std::vector<WB_log_entry> &log_entries,
                                        Errors &errors) {
    errors.add("", "", "Operator filter_smooth_median not yet implemented");
}
