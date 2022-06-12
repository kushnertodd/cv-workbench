//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_json_utils.hpp"

using namespace std;

extern bool debug;

bool error_check_type(string module, string key, json_object *jobj, enum json_type expected_type, Errors &errors) {
  enum json_type actual_type = json_object_get_type(jobj);
  if (debug)
    cout << "error_check_type: key '" << key << "' expected type '"
         << json_type_to_name(expected_type) << "' actual type '" <<
         json_type_to_name(actual_type) << "'" << endl;
  if (expected_type != actual_type) {
    ostringstream os;
    os << module << ": invalid '" << key << "' type, expected " << json_type_to_name(expected_type)
       << " not " << json_type_to_name(actual_type) << ".";
    errors.add(os.str());
    return false;
  }
  return true;
}

json_object *get_json_object(string module, json_object *jobj, string key,
                             enum json_type expected_type, Errors &errors, bool optional) {
 if (debug)
  cout << "get_json_object: key '" << key << "' expected type '"
       << json_type_to_name(expected_type)
       //<< "' key.c_str() '"       << key.c_str()
       << "'" << endl;
  json_object *jobj_from_key = json_object_object_get(jobj, key.c_str());
  if (jobj_from_key == nullptr) {
    if (!optional) {
      string message = module + ": '" + key + "' key missing";
      errors.add(message);
      if (debug)
        cout << message << endl;
    }
  } else {
    if (!error_check_type(module, key, jobj_from_key, expected_type, errors)) {
      return nullptr;
    }
  }
  return jobj_from_key;
}

bool json_parse_step_item_type_check(string item, json_type type_expected, json_type type_found, Errors &errors) {
  ostringstream os;
  if (type_expected != type_found) {
    os << "step "
       //<< i
       << ": expected " << item << " as " << json_type_to_name(type_expected)
       << ", found to be " << json_type_to_name(type_found);
    errors.add(os.str());
    return false;
  }
  return true;
}
