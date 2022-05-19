#include <json-c/json.h>
#include <stdio.h>
#include <string.h>

char* indent_str(int indent) {
  char buf[] = "                                ";
  char* ret = malloc(strlen(buf) + 1);
  strcpy(ret, buf);
  ret[indent] = '\0';
  return ret;
}

/*printing the value corresponding to boolean, double, integer and strings*/
void print_json_value(int indent, json_object *jobj) {
  enum json_type type;
  printf("%stype: ", indent_str(indent), type);
  type = json_object_get_type(jobj); /*Getting the type of the json object*/
  switch (type) {
    case json_type_boolean:
      printf("%sjson_type_boolean\n", indent_str(indent));
      printf("%s          value: %s\n", indent_str(indent), json_object_get_boolean(jobj) ? "true" : "false");
      break;
    case json_type_double:
      printf("json_type_double\n");
      printf("%s          value: %lf\n", indent_str(indent), json_object_get_double(jobj));
      break;
    case json_type_int:
      printf("json_type_int\n");
      printf("%s          value: %d\n", indent_str(indent), json_object_get_int(jobj));
      break;
    case json_type_string:
      printf("json_type_string\n");
      printf("%s          value: %s\n", indent_str(indent), json_object_get_string(jobj));
      break;
  }

}

void json_parse_array(int indent, json_object *jobj, char *key) {
  void json_parse(int indent, json_object *jobj); /*Forward Declaration*/
  enum json_type type;

  json_object *jarray = jobj; /*Simply get the array*/
  if (key) {
    jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
  }

  int arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
  printf("\n%s          Array Length: %d\n", indent_str(indent), arraylen);
  int i;
  json_object *jvalue;

  for (i = 0; i < arraylen; i++) {
    jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
    type = json_object_get_type(jvalue);
    if (type == json_type_array) {
      json_parse_array(indent+4, jvalue, NULL);
    } else if (type != json_type_object) {
      printf("%svalue[%d]: ", indent_str(indent), i);
      print_json_value(indent, jvalue);
    } else {
      json_parse(indent, jvalue);
    }
  }
}

/*Parsing the json object*/
void json_parse(int indent, json_object *jobj) {
  enum json_type type;
  json_object_object_foreach(jobj, key, val)
  { /*Passing through every array element*/
    printf("%stype: ", indent_str(indent), type);
    type = json_object_get_type(val);
    switch (type) {
      case json_type_boolean:
      case json_type_double:
      case json_type_int:
      case json_type_string:
        printf("%skey '%-20s'  ", indent_str(indent), key);
        print_json_value(indent, val);
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

int main() {
  char *string = 
/*
"{\"sitename\" : \"joys of programming\", "
                 "\"categories\" : [ \"c\" , [\"c++\" , \"c\" ], \"java\", "
                 "\"PHP\" ],\"author-details\": { \"admin\": false, "
                 "\"name\" : \"Joys of Programming\", \"Number of Posts\" : 10 } }";
*/
"{                                         "
"  \"sitename\": \"joys of programming\",  "
"  \"categories\": [                       "
"    \"c\",                                "
"    [                                     "
"      \"c++\",                            "
"      \"c\"                               "
"    ],                                    "
"    \"java\",                             "
"    \"PHP\"                               "
"  ],                                      "
"  \"author-details\": {                   "
"    \"admin\": false,                     "
"    \"name\": \"Joys of Programming\",    "
"    \"Number of Posts\": 10               "
"  }                                       "
"}                                         ";
  printf("JSON string: %s\n", string);
  json_object *jobj = json_tokener_parse(string);
  json_parse(0, jobj);
}
