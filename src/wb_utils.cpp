//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_utils.hpp"

using namespace std;

string indent(int n) {
  string s;
  for (int i = 0; i < n; i++) {
    s += " ";
  }
  return s;
}

bool string_to_int(string str, int &value) {
  stringstream s;
  s << str;
  if (s >> value)
    return true;
  else
    return false;
}

bool string_to_bool(string str, bool &bvalue) {
  if (str == "true") {
    bvalue = true;
    return true;
  } else if (str == "false") {
    bvalue = false;
    return true;
  } else {
    return false;
  }
}

/*printing the value corresponding to boolean, double, integer and strings*/
void print_json_value(json_object *jobj) {
  enum json_type type;
  type = json_object_get_type(jobj); /*Getting the type of the json object*/
  //printf("type: %d '%s'\n",type, json_type_to_name(type));
  cout << "type: " << type << "'" << json_type_to_name(type) << "'" << endl;
  switch (type) {
    //case json_type_null: printf("json_type_null\n");
    case json_type_null:
      cout << "json_type_null" << endl;
      //case json_type_boolean: printf("json_type_boolean\n");
    case json_type_boolean:
      cout << "json_type_boolean" << endl;
      //printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
      cout << "value: " << (json_object_get_boolean(jobj) ? "true" : "false") << endl;
      break;
      //case json_type_double: printf("json_type_double\n");
    case json_type_double:
      cout << "json_type_double" << endl;
      //printf("          value: %lf\n", json_object_get_double(jobj));
      cout << "          value: " << json_object_get_double(jobj) << endl;
      break;
      //case json_type_int: printf("json_type_int\n");
    case json_type_int:
      cout << "json_type_int" << endl;
      //printf("          value: %d\n", json_object_get_int(jobj));
      cout << "          value: " << json_object_get_int(jobj) << endl;
      break;
      //case json_type_string: printf("json_type_string\n");
    case json_type_string:
      cout << "json_type_string" << endl;
      //printf("          value: %s\n", json_object_get_string(jobj));
      cout << "          value: " << json_object_get_string(jobj) << endl;
      break;
    case json_type_object:
    case json_type_array:
      break;
  }
}

void json_parse_array(json_object *jobj, char *key) {
  void json_parse(json_object *jobj); /*Forward Declaration*/
  enum json_type type;

  json_object *jarray = jobj; /*Simply get the array*/
  if (key) {
    jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
  }

  int arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
  //printf("Array Length: %d\n",arraylen);
  cout << "Array Length: " << arraylen << endl;
  json_object *jvalue;

  for (int i = 0; i < arraylen; i++) {
    jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
    type = json_object_get_type(jvalue);
    if (type == json_type_array) {
      json_parse_array(jvalue, NULL);
    } else if (type != json_type_object) {
      //printf("value[%d]: ",i);
      cout << "value[" << i << "]: " << endl;
      print_json_value(jvalue);
    } else {
      json_parse(jvalue);
    }
  }
}

/**
 * Parsing the json object
 * @param jobj json-c parsed json
 */
void json_parse(json_object *jobj) {
  enum json_type type;
  json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
    type = json_object_get_type(val);
    //printf("\nkey: '%s' type: %d '%s'\n",key, type, json_type_to_name(type));
    cout << endl << "key: '" << key << "' type: " << type << " '" << json_type_to_name(type) << "'" << endl;
    switch (type) {
      case json_type_boolean:
      case json_type_double:
      case json_type_int:
      case json_type_string:
      case json_type_null:
        print_json_value(val);
        break;
        //case json_type_object: printf("json_type_object\n");
      case json_type_object:
        cout << "json_type_object" << endl;
        jobj = json_object_object_get(jobj, key);
        json_parse(jobj);
        break;
        //case json_type_array: printf("type: json_type_array, ");
      case json_type_array:
        cout << "type: json_type_array, ";
        json_parse_array(jobj, key);
        break;
    }
  }

}

