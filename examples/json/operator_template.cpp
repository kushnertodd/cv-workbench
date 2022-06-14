//
// Created by kushn on 5/21/2022.
//

#include "operator_template.hpp"

//Parsing the json object
void json_parse(int indent, json_object *jobj) {
  enum json_type type;
  json_object_object_foreach(jobj, key, val)
  { //Passing through every array element
    printf("%stype: ", indent_str(indent), type);
    type = json_object_get_type(val);
    switch (type) {
      case json_type_boolean:
      case json_type_double:
      case json_type_int:
      case json_type_string:
        printf("%skey '%-20s'  ", indent_str(indent), key);
        json_print_value(indent, val);
        if (!strcmp(key, "id")) {
        } else if (!strcmp(key, "domain")) {
        } else if (!strcmp(key, "class")) {
        } else if (!strcmp(key, "parameters")) {
        } else if (!strcmp(key, "name")) {
        } else if (!strcmp(key, "data_type")) {
        } else if (!strcmp(key, "default")) {
        } else if (!strcmp(key, "valid_values")) {
        } else
          printf("what is this key? '%s'\n", key);
        break;
      case json_type_object:
        printf("%skey '%-20s'  ", indent_str(indent), key);
        printf("%sjson_type_object\n", indent_str(indent));
        jobj = json_object_object_get(jobj, key);
        json_parse(indent, jobj);
        break;
      case json_type_array:
        printf("%skey '%-20s'  ", indent_str(indent), key);
        printf("%stype: json_type_array, ", indent_str(indent));
        json_parse_array(indent, jobj, key);
        break;
    }
  }
}
