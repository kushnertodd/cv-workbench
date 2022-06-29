//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_UTILS_HPP_
#define CV_WORKBENCH_SRC_WB_UTILS_HPP_

#include <map>
#include <string>
#include <json-c/json.h>
#include "data_source_descriptor.hpp"
#include "wb_defs.hpp"

using namespace std;

class Workbench_utils {
 public:
  static char ascii_to_char(int n);
  static string char_to_string(char c);
  static string data_type_enum_to_string(cv_enums::CV_data_type type);
  static string file_format_to_string(cv_enums::CV_image_file_format type);
  static bool hex_string_to_int(string text, unsigned long long &value);
  static string image_depth_enum_to_string(cv_enums::CV_image_depth depth);
  static string indent(int n);
  static string int_to_hex_string(unsigned long long i, int width = -1);
  static string int_to_string(int i, int width = -1);
  static bool is_numeric(string number);
  static void json_parse(json_object *jobj);
  static void json_parse_array(json_object *jobj, char *key);
  static void json_print_value(json_object *jobj);
  static string real_to_string(double i, int width = -1);
  static string repository_type_enum_to_string(cv_enums::CV_repository_type type);
  static bool string_to_bool(string str, bool &bvalue);
  static cv_enums::CV_data_type string_to_data_type_enum(string type);
  static cv_enums::CV_image_file_format string_to_file_format_enum(string type);
  static cv_enums::CV_image_depth string_to_image_depth_enum(string depth);
  static bool string_to_int(string str, int &value);
  cv_enums::CV_repository_type string_to_repository_type_enum(string type);
  static bool string_to_real(string text, double &value);

};

#endif //CV_WORKBENCH_SRC_WB_UTILS_HPP_
