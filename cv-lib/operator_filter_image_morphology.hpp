#ifndef CV_WORKBENCH_SRC_OPERATOR_FILTER_IMAGE_MORPHOLOGY_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_FILTER_IMAGE_MORPHOLOGY_HPP_

#include "operator.hpp"
#include "wb_defs.hpp"

class Operator_filter_image_morphology : public Operator {
public:
    ~Operator_filter_image_morphology() override;
    void run(std::vector<Data_source_descriptor *> &input_data_sources,
             std::vector<Data_source_descriptor *> &output_data_stores, String_map &operator_parameters,
             std::vector<WB_log_entry> &log_entries, Errors &errors) override;
};

#endif // CV_WORKBENCH_SRC_OPERATOR_FILTER_IMAGE_MORPHOLOGY_HPP_
