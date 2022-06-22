//
// Created by kushn on 6/21/2022.
//

#ifndef CV_WORKBENCH_SRC_OPERATOR_UTILS_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_UTILS_HPP_

#include <string>
#include "errors.hpp"
#include "wb_defs.hpp"

using namespace std;

class Operator_utils {
 public:
  static bool get_int_parameter(string module,
                                String_map &parameters,
                                string parameter,
                                int &int_value,
                                Errors &errors);
  static bool get_real_parameter(string module,
                                 String_map &parameters,
                                 string parameter,
                                 double &real_value,
                                 Errors &errors);
  static string get_parameter(String_map &parameters, string parameter);
  static bool has_parameter(String_map &parameters, string parameter);
  static string parameters_to_string(String_map &parameters);
};

#endif //CV_WORKBENCH_SRC_OPERATOR_UTILS_HPP_
