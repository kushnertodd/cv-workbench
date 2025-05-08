#ifndef CV_WORKBENCH_SRC_OPERATOR_H_
#define CV_WORKBENCH_SRC_OPERATOR_H_

#include "data_source_descriptor.hpp"
#include "wb_defs.hpp"
#include "wb_log.hpp"

class Operator {
public:
    virtual ~Operator();
    virtual void run(std::list<Data_source_descriptor *> &input_data_sources,
                     std::list<Data_source_descriptor *> &output_data_stores, String_map &operator_parameters,
                     std::list<WB_log_entry> &log_entries, Errors &errors) = 0;
};

#endif // CV_WORKBENCH_SRC_OPERATOR_H_
