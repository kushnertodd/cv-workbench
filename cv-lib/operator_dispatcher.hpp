#ifndef CV_WORKBENCH_SRC_PRODUCE_OPERATOR_HPP_
#define CV_WORKBENCH_SRC_PRODUCE_OPERATOR_HPP_

#include <iostream>
#include "operator.hpp"

class Operator_dispatcher : public Operator {
public:
    ~Operator_dispatcher() override;
    static Operator *create_operator(const std::string &operator_name);
};

#endif // CV_WORKBENCH_SRC_PRODUCE_OPERATOR_HPP_
