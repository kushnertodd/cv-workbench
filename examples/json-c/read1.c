#include <json-c/json.h>
#include <stdio.h>
void json_parse(json_object *jobj) {
  enum json_type type;
  json_object_object_foreach(jobj, key, val) {
    type = json_object_get_type(val);
    switch (type) {
      case json_type_boolean:
        printf("type: json_type_boolean, ");
        printf("value: %s\n", json_object_get_boolean(val) ? "true" : "false");
        break;
    }
  }
}
int main() {
  char *string = "{ \"admin\" : true,  \"reviewer\" :  false,  \"author\" :  true}";
  printf("JSON string: %s\n", string);
  json_object *jobj = json_tokener_parse(string);
  json_parse(jobj);
}
