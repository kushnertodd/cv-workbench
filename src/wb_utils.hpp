//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_UTILS_HPP_
#define CV_WORKBENCH_SRC_WB_UTILS_HPP_

#include <string>
#include <json-c/json.h>

using namespace std;

string indent(int n);
bool string_to_int(string str, int &value);
bool string_to_bool(string str, bool &bvalue);
void print_json_value(json_object *jobj);

#endif //CV_WORKBENCH_SRC_WB_UTILS_HPP_
