//
// Created by kushn on 6/21/2022.
//

#ifndef CV_WORKBENCH_SRC_OPERATOR_UTILS_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_UTILS_HPP_

#include <string>
#include "errors.hpp"
#include "wb_defs.hpp"

//

class Operator_utils {
 public:
  static bool get_int_parameter(std::string module,
                                String_map &parameters,
                                std::string parameter,
                                int &int_value,
                                Errors &errors);
  static bool get_real_parameter(std::string module,
                                 String_map &parameters,
                                 std::string parameter,
                                 double &real_value,
                                 Errors &errors);
  static std::string get_parameter(String_map &parameters, std::string parameter);
  static bool has_parameter(String_map &parameters, std::string parameter);
  static std::string parameters_to_string(String_map &parameters);
};

#endif //CV_WORKBENCH_SRC_OPERATOR_UTILS_HPP_
