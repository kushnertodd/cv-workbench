//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_UTILS_HPP_
#define CV_WORKBENCH_SRC_WB_UTILS_HPP_

#include <string>
#include <json-c/json.h>
#include "wb_enums.hpp"

using namespace std;

string indent(int n);
bool string_to_int(string str, int &value);
bool string_to_bool(string str, bool &bvalue);
void print_json_value(json_object *jobj);
void json_parse_array(json_object *jobj, char *key);
void json_parse(json_object *jobj);
string repository_name_to_string(Repository_type_enum type);
string data_type_to_string(Cv_data_type_enum type);
string image_format_to_string(Cv_image_file_format_enum type);
#endif //CV_WORKBENCH_SRC_WB_UTILS_HPP_
