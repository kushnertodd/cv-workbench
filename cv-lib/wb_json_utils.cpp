#include "wb_json_utils.hpp"
#include <iostream>
#include <sstream>

extern bool debug;
/**
 * @brief
 * @param module
 * @param key
 * @param jobj
 * @param
 * @param errors
 * @return
 */
bool error_check_type(const std::string &module, const std::string &key, json_object *jobj,
                      enum json_type expected_type, Errors &errors) {
    enum json_type actual_type = json_object_get_type(jobj);
    if (debug)
        std::cout << "error_check_type: key '" << key << "' expected type '" << json_type_to_name(expected_type)
                  << "' actual type '" << json_type_to_name(actual_type) << "'" << std::endl;
    if (expected_type != actual_type) {
        std::ostringstream os;
        os << module << ": invalid '" << key << "' type, expected " << json_type_to_name(expected_type) << " not "
           << json_type_to_name(actual_type) << ".";
        errors.add("error_check_type", "", os.str());
        return false;
    }
    return true;
}
/**
 * @brief
 * @param module
 * @param jobj
 * @param key
 * @param
 * @param errors
 * @param optional
 * @return
 */
json_object *get_json_object(const std::string &module, json_object *jobj, const std::string &key,
                             enum json_type expected_type, Errors &errors, bool optional) {
    if (debug)
        std::cout << "get_json_object: key '" << key << "' expected type '"
                  << json_type_to_name(expected_type)
                  //<< "' key.c_str() '"       << key.c_str()
                  << "'" << std::endl;
    json_object *jobj_from_key = json_object_object_get(jobj, key.c_str());
    if (jobj_from_key == nullptr) {
        if (!optional) {
            std::string message = module + ": '" + key + "' key missing";
            errors.add("get_json_object", "", message);
            if (debug)
                std::cout << message << std::endl;
        }
    } else {
        if (!error_check_type(module, key, jobj_from_key, expected_type, errors)) {
            return nullptr;
        }
    }
    return jobj_from_key;
}
/**
 * @brief
 * @param item
 * @param type_expected
 * @param type_found
 * @param errors
 * @return
 */
bool json_parse_step_item_type_check(const std::string &item, json_type type_expected, json_type type_found,
                                     Errors &errors) {
    std::ostringstream os;
    if (type_expected != type_found) {
        os << "step "
           //<< i
           << ": expected " << item << " as " << json_type_to_name(type_expected) << ", found to be "
           << json_type_to_name(type_found);
        errors.add("json_parse_step_item_type_check", "", os.str());
        return false;
    }
    return true;
}
