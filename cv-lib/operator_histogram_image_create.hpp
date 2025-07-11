#ifndef SRC__OPERATOR_HISTOGRAM_IMAGE_CREATE_HPP_
#define SRC__OPERATOR_HISTOGRAM_IMAGE_CREATE_HPP_

#include "operator.hpp"
#include "wb_defs.hpp"

class Operator_histogram_image_create : public Operator {
public:
    ~Operator_histogram_image_create() override;
    void run(std::vector<Data_source_descriptor *> &input_data_sources,
             std::vector<Data_source_descriptor *> &output_data_stores, String_map &operator_parameters,
             std::vector<WB_log_entry> &log_entries, Errors &errors) override;
};

#endif // SRC__OPERATOR_HISTOGRAM_IMAGE_CREATE_HPP_
