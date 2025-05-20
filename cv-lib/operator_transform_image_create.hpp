#ifndef CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_IMAGE_CREATE_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_IMAGE_CREATE_HPP_

#include "operator.hpp"

class Operator_transform_image_create : public Operator {
public:
    ~Operator_transform_image_create() override;
    void run(std::list<Data_source_descriptor *> &input_data_sources,
             std::list<Data_source_descriptor *> &output_data_stores, String_map &operator_parameters,
             std::list<WB_log_entry> &log_entries, Errors &errors) override;
};

#endif // CV_WORKBENCH_SRC_OPERATOR_TRANSFORM_IMAGE_CREATE_HPP_
