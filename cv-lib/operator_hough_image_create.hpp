#ifndef SRC__OPERATOR_HOUGH_IMAGE_CREATE_HPP_
#define SRC__OPERATOR_HOUGH_IMAGE_CREATE_HPP_

#include "operator.hpp"
#include "polar_trig.hpp"
#include "wb_defs.hpp"

const int default_min_theta = 0;
const int default_max_theta = theta_max;

class Operator_hough_image_create : public Operator {
public:
    ~Operator_hough_image_create() override;
    void run(std::vector<Data_source_descriptor *> &input_data_sources,
             std::vector<Data_source_descriptor *> &output_data_stores, String_map &operator_parameters,
             std::vector<WB_log_entry> &log_entries, Errors &errors) override;
};

#endif // SRC__OPERATOR_HOUGH_IMAGE_CREATE_HPP_
