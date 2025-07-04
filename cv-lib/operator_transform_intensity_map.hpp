#ifndef CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_INTENSITY_MAP_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_INTENSITY_MAP_HPP_

#include "operator.hpp"

class Operator_transform_intensity_map : public Operator {
public:
    ~Operator_transform_intensity_map() override;
    void run(std::vector<Data_source_descriptor *> &input_data_sources,
             std::vector<Data_source_descriptor *> &output_data_stores, String_map &operator_parameters,
             std::vector<WB_log_entry> &log_entries, Errors &errors) override;
};

#endif // CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_INTENSITY_MAP_HPP_
