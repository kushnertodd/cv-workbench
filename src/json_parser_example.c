// A simple and complete json parser
// https://linuxprograms.wordpress.com/2010/08/19/json_parser_json-c/

/*

This parser makes use of all the functions which reads the value of a json object. This parser is complete in all respects. You can make use of the functions to create parser for your various requirements

*/

#include <json-c/json.h>
#include <stdio.h>
#include "file_utils_C.h"

/*printing the value corresponding to boolean, double, integer and strings*/
void json_print_value(json_object *jobj){
  enum json_type type;
  type = json_object_get_type(jobj); /*Getting the type of the json object*/
  printf("type: %d '%s'\n",type, json_type_to_name(type));
  switch (type) {
    case json_type_null: printf("json_type_null\n");
    case json_type_boolean: printf("json_type_boolean\n");
      printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
      break;
    case json_type_double: printf("json_type_double\n");
      printf("          value: %lf\n", json_object_get_double(jobj));
      break;
    case json_type_int: printf("json_type_int\n");
      printf("          value: %d\n", json_object_get_int(jobj));
      break;
    case json_type_string: printf("json_type_string\n");
      printf("          value: %s\n", json_object_get_string(jobj));
      break;
  }

}

void json_parse_array( json_object *jobj, char *key) {
  void json_parse(json_object * jobj); /*Forward Declaration*/
  enum json_type type;

  json_object *jarray = jobj; /*Simply get the array*/
  if(key) {
    jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
  }

  int arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
  printf("Array Length: %d\n",arraylen);
  int i;
  json_object * jvalue;

  for (i=0; i< arraylen; i++){
    jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
    type = json_object_get_type(jvalue);
    if (type == json_type_array) {
      json_parse_array(jvalue, NULL);
    }
    else if (type != json_type_object) {
      printf("value[%d]: ",i);
      json_print_value(jvalue);
    }
    else {
      json_parse(jvalue);
    }
  }
}

/*Parsing the json object*/
void json_parse(json_object * jobj) {
  enum json_type type;
  json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
    type = json_object_get_type(val);
    printf("\nkey: '%s' type: %d '%s'\n",key, type, json_type_to_name(type));
    switch (type) {
      case json_type_boolean:
      case json_type_double:
      case json_type_int:
      case json_type_string: json_print_value(val);
        break;
      case json_type_object: printf("json_type_object\n");
        jobj = json_object_object_get(jobj, key);
        json_parse(jobj);
        break;
      case json_type_array: printf("type: json_type_array, ");
        json_parse_array(jobj, key);
        break;
    }
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("usage: %s filename\n", argv[0]);
    exit(0);
  }
  char *filename = argv[1];
  long bufsize;
  char* string = read_file(filename, &bufsize);
  printf("JSON string: %s\n", string);
  json_object *jobj = json_tokener_parse(string);
  if (jobj == NULL)
    printf("json_tokener_parse() failed\n");
  else
    json_parse(jobj);
  free(string);
}
