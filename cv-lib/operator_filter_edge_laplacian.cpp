#include "operator_filter_edge_laplacian.hpp"

/**
 * @brief
 *
 */
Operator_filter_edge_laplacian::~Operator_filter_edge_laplacian() = default;
/**
 * @brief
 * @param input_data_sources
 * @param output_data_stores
 * @param operator_parameters
 * @param log_entries
 * @param errors
 */
void Operator_filter_edge_laplacian::run(std::list<Data_source_descriptor *> &input_data_sources,
                                         std::list<Data_source_descriptor *> &output_data_stores,
                                         String_map &operator_parameters, std::list<WB_log_entry> &log_entries,
                                         Errors &errors) {
    errors.add("", "", "Operator filter_edge_laplacian not yet implemented");
}
