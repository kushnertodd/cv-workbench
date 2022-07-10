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

//

class Workbench_utils {
 public:
  static char ascii_to_char(int n);
  static std::string char_to_string(char c);
  static std::string data_type_enum_to_string(cv_enums::CV_data_type type);
  static void error_exit(std::string message);
  static std::string file_format_to_string(cv_enums::CV_image_file_format type);
  static bool hex_string_to_int(std::string text, unsigned long long &value);
  static std::string image_depth_enum_to_string(cv_enums::CV_image_depth depth);
  static std::string indent(int n);
  static std::string int_to_hex_string(unsigned long long i, int width = -1);
  static std::string int_to_string(int i, int width = -1);
  static bool is_numeric(std::string number);
  static void json_parse(json_object *jobj);
  static void json_parse_array(json_object *jobj, char *key);
  static void json_print_value(json_object *jobj);
  static std::string real_to_string(double i, int width = -1);
  static std::string repository_type_enum_to_string(cv_enums::CV_repository_type type);
  static bool string_to_bool(std::string str, bool &bvalue);
  static cv_enums::CV_data_type string_to_data_type_enum(std::string type);
  static cv_enums::CV_image_file_format string_to_file_format_enum(std::string type);
  static cv_enums::CV_image_depth string_to_image_depth_enum(std::string depth);
  static bool string_to_int(std::string str, int &value);
  static cv_enums::CV_repository_type string_to_repository_type_enum(std::string type);
  static bool string_to_real(std::string text, double &value);
  static bool write_double(FILE *fp, double value, std::string message, Errors &errors);
  static bool write_double_buffer(FILE *fp, double *buf, double count, std::string message, Errors &errors);
  static bool write_float(FILE *fp, float value, std::string message, Errors &errors);
  static bool write_float_buffer(FILE *fp, float *buf, float count, std::string message, Errors &errors);
  static  bool write_int(FILE *fp, int value, std::string message, Errors &errors);
  static bool write_int_buffer(FILE *fp, int *buf, int count, std::string message, Errors &errors);

};

#endif //CV_WORKBENCH_SRC_WB_UTILS_HPP_
