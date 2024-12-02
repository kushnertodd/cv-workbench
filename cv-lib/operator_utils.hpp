//
// Created by kushn on 6/21/2022.
//

#ifndef CV_WORKBENCH_SRC_OPERATOR_UTILS_HPP_
#define CV_WORKBENCH_SRC_OPERATOR_UTILS_HPP_

#include <string>
#include "data_source_descriptor.hpp"
#include "errors.hpp"
#include "wb_defs.hpp"

//

class Operator_utils {
 public:
  static bool get_int_parameter(const std::string &module,
                                String_map &parameters,
                                const std::string &parameter,
                                int &int_value,
                                Errors &errors,
                                bool optional = false);
  static std::string get_parameter(String_map &parameters, const std::string &parameter);
  static bool get_real_parameter(const std::string &module,
                                 String_map &parameters,
                                 const std::string &parameter,
                                 double &real_value,
                                 Errors &errors,
                                 bool optional = false);
  static bool get_string_parameter(const std::string &module,
                                   String_map &parameters,
                                   const std::string &parameter,
                                   std::string &string_value,
                                   Errors &errors,
                                   bool optional = false);
  static bool has_parameter(String_map &parameters, const std::string &parameter);
  static std::string parameters_to_string(String_map &parameters);
//  static void write_operator_image(Data_source_descriptor *output_data_store,
//                                   Image *output,
};

#endif //CV_WORKBENCH_SRC_OPERATOR_UTILS_HPP_
