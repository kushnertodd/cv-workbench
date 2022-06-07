// A simple and complete json parser
// https://linuxprograms.wordpress.com/2010/08/19/json_parser_json-c/

/*

This parser makes use of all the functions which reads the value of a json object. This parser is complete in all respects. You can make use of the functions to create parser for your various requirements

*/

#include <json-c/json.h>
//#include <stdio.h>
#include <iostream>
//#include "file_utils_C.h"
#include "file_utils.hpp"
using namespace std;

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
  int i;
  json_object *jvalue;

  for (i = 0; i < arraylen; i++) {
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

/*Parsing the json object*/
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

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "usage: %s json-template-filename" << argv[0] << endl;
    exit(0);
  }
  char *filename = argv[1];
  string string_val = file_utils::read_file(filename);
  cout << "JSON string: " << string_val << endl;
  json_object *jobj = json_tokener_parse(string_val.c_str());
  if (jobj == NULL)
    printf("json_tokener_parse() failed\n");
  else
    json_parse(jobj);
}
