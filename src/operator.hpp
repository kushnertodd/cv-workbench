//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_OPERATOR_H_
#define CV_WORKBENCH_SRC_OPERATOR_H_

#include <map>
#include "data_source_descriptor.hpp"

class Operator {
 public:
  Operator();
  virtual ~Operator();
  virtual void run(list<Data_source_descriptor *> &input_data_sources,
                   list<Data_source_descriptor *> &output_data_stores,
                   map<string, string> &operator_parameters,
                   Errors &errors) = 0;
};

#endif //CV_WORKBENCH_SRC_OPERATOR_H_