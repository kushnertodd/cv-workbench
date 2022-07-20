//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_UTILS_HPP_
#define CV_WORKBENCH_SRC_WB_UTILS_HPP_

#include <map>
#include <string>
#include <json-c/json.h>
#include "errors.hpp"
#include "wb_defs.hpp"

namespace wb_utils {

char ascii_to_char(int n);
std::string char_to_string(char c);
std::string data_type_enum_to_string(cv_enums::CV_data_type type);
float double_to_float(double value);
void error_exit(const std::string &message);
std::string data_format_to_string(cv_enums::CV_data_format type);
bool hex_string_to_int(const std::string &text, unsigned long long &value);
std::string image_depth_enum_to_string(cv_enums::CV_image_depth depth);
std::string indent(int n);
float int_to_float(int value);
std::string int_to_hex_string(unsigned long long i, int width = -1);
std::string int_to_string(int i, int width = -1);
bool is_numeric(std::string number);
void json_parse(json_object *jobj);
void json_parse_array(json_object *jobj, char *key);
void json_print_value(json_object *jobj);
std::string real_to_string(double i, int width = -1);
std::string repository_type_enum_to_string(cv_enums::CV_repository_type type);
int round_double_to_int(double value);
int round_float_to_int(float value);
void string_find(std::string text, std::string& prefix, std::string& suffix, std::string pat, bool &found, bool &at_beginning, bool &at_end);
bool string_to_bool(const std::string &str, bool &bvalue);
cv_enums::CV_data_type string_to_data_type_enum(const std::string &type);
cv_enums::CV_data_format string_to_data_format_enum(const std::string &type);
cv_enums::CV_image_depth string_to_image_depth_enum(const std::string &depth);
bool string_to_int(const std::string &str, int &value);
cv_enums::CV_repository_type string_to_repository_type_enum(const std::string &type);
bool string_to_double(const std::string &text, double &value);
bool write_double(FILE *fp, double value, const std::string &message, Errors &errors);
bool write_double_buffer(FILE *fp, double *buf, int count, const std::string &message, Errors &errors);
bool write_float(FILE *fp, float value, const std::string &message, Errors &errors);
bool write_float_buffer(FILE *fp, float *buf, int count, const std::string &message, Errors &errors);
bool write_int(FILE *fp, int value, const std::string &message, Errors &errors);
bool write_int_buffer(FILE *fp, int *buf, int count, const std::string &message, Errors &errors);

}

#endif //CV_WORKBENCH_SRC_WB_UTILS_HPP_
