//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_UTILS_HPP_
#define CV_WORKBENCH_SRC_WB_UTILS_HPP_

#include <map>
#include <string>
#include <json-c/json.h>
#include "data_source_descriptor.hpp"
#include "wb_enums.hpp"

using namespace std;

char ascii_to_char(int n);
string char_to_string(char c);
string data_type_enum_to_string(Cv_data_type_enum type);
string file_format_to_string(Cv_image_file_format_enum type);
bool hex_string_to_int(string text, unsigned long long &value);
string image_depth_enum_to_string(Cv_image_depth_enum depth);
string indent(int n);
string int_to_hex_string(unsigned long long i, int width = -1);
string int_to_string(int i, int width = -1);
bool is_numeric(string number);
void json_parse_array(json_object *jobj, char *key);
void json_parse(json_object *jobj);
void json_print_value(json_object *jobj);
string real_to_string(double i, int width = -1);
string repository_type_enum_to_string(Cv_repository_type_enum type);
bool string_to_bool(string str, bool &bvalue);
Cv_data_type_enum string_to_data_type_enum(string type);
Cv_image_file_format_enum string_to_file_format_enum(string type);
Cv_image_depth_enum string_to_image_depth_enum(string depth);
bool string_to_int(string str, int &value);
bool string_to_real(string text, double &value);
bool string_to_real(string arg, double &value);

void operator_filter_edge_sobel(Data_source_descriptor *input_data_source,
                                Data_source_descriptor *output_data_store,
                                map<string, string> operator_parameters,
                                Errors &errors);
#endif //CV_WORKBENCH_SRC_WB_UTILS_HPP_
