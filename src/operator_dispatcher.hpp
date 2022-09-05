//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_PRODUCE_OPERATOR_HPP_
#define CV_WORKBENCH_SRC_PRODUCE_OPERATOR_HPP_

#include <iostream>
#include "operator.hpp"

//
/**
 * Maps text operator string to operator instance
 */
class Operator_dispatcher : public Operator {
 public:
  static Operator *create_operator(const std::string &operator_name);
};

#endif //CV_WORKBENCH_SRC_PRODUCE_OPERATOR_HPP_
