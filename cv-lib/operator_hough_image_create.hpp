#ifndef SRC__OPERATOR_HOUGH_IMAGE_CREATE_HPP_
#define SRC__OPERATOR_HOUGH_IMAGE_CREATE_HPP_

#include "operator.hpp"
#include "wb_defs.hpp"

class Operator_hough_image_create : public Operator {
public:
    ~Operator_hough_image_create() override;
    void run(std::list<Data_source_descriptor *> &input_data_sources,
             std::list<Data_source_descriptor *> &output_data_stores, String_map &operator_parameters,
             std::list<WB_log_entry> &log_entries, Errors &errors) override;
};

#endif // SRC__OPERATOR_HOUGH_IMAGE_CREATE_HPP_
