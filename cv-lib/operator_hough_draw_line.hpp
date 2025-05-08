#ifndef SRC__OPERATOR_HOUGH_DRAW_LINE_HPP_
#define SRC__OPERATOR_HOUGH_DRAW_LINE_HPP_

#include "operator.hpp"
#include "wb_defs.hpp"

class Operator_hough_draw_line : public Operator {
public:
    void run(std::list<Data_source_descriptor *> &input_data_sources,
             std::list<Data_source_descriptor *> &output_data_stores, String_map &operator_parameters,
             std::list<WB_log_entry> &log_entries, Errors &errors) override;
};

#endif // SRC__OPERATOR_HOUGH_DRAW_LINE_HPP_
