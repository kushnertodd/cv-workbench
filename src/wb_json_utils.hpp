//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_JSON_UTILS_HPP_
#define CV_WORKBENCH_SRC_WB_JSON_UTILS_HPP_

#include <string>
#include <json-c/json.h>
#include "errors.hpp"

using namespace std;

bool error_check_type(string module, string key, json_object *jobj, enum json_type expected_type, Errors &errors);
json_object *get_json_object(string module, json_object *jobj, string key,
                             enum json_type expected_type, Errors &errors, bool optional = false);
bool json_parse_step_item_type_check(string item, json_type type_expected, json_type type_found, Errors &errors);

#endif //CV_WORKBENCH_SRC_WB_JSON_UTILS_HPP_
