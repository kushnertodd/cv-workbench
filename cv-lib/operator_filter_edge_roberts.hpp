#ifndef CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_ROBERTS_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_ROBERTS_HPP_

#include "operator.hpp"
#include "wb_defs.hpp"

class Operator_filter_edge_roberts : public Operator {
public:
    ~Operator_filter_edge_roberts() override;
    void run(std::list<Data_source_descriptor *> &input_data_sources,
             std::list<Data_source_descriptor *> &output_data_stores, String_map &operator_parameters,
             std::list<WB_log_entry> &log_entries, Errors &errors) override;
};

#endif // CV_WORKBENCH_SRC_OPERATOR_FILTER_EDGE_ROBERTS_HPP_
