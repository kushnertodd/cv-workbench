// gcc json-parse00.c -ljson-c -o json-parse00

#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

struct valid_values {
  char* values[10];
};

struct parameters {
  char name[100];
  char data_type[100];
  char default_value[100];
  struct valid_values values[10];
} parameter_set;

struct template_ {
  char id[100];
  char domain[100];
  char class[100];
  struct parameters params[10];
} template_struct;

int
main(void)
{
  json_object *root =
    json_object_from_file("test.json");
  if (!root)
    return 1;

  json_object *id_name =
    json_object_object_get(root, "id");
  strcpy(template.id,
         (char *) json_object_to_json_string(id_name));
  printf("id: %s\n",
         json_object_to_json_string_ext(
           id_name,
           JSON_C_TO_STRING_PRETTY));

  json_object *domain_name =
    json_object_object_get(root,
                           "domain");
  strcpy(template.domain,
         json_object_to_json_string(domain_name));
  printf("domain: %s\n",
         json_object_to_json_string_ext(
           id_name,
           JSON_C_TO_STRING_PRETTY));

  json_object *class_name =
    json_object_object_get(root, "class");
  strcpy(template.class,
         json_object_to_json_string(class_name));
  printf("class: %s\n",
         json_object_to_json_string_ext(
           class_name,
           JSON_C_TO_STRING_PRETTY));


  json_object *parameters =
    json_object_object_get(root,
                           "parameters");
  printf("parameters: %s\n",
         json_object_to_json_string_ext(
           parameters,
           JSON_C_TO_STRING_PRETTY));

  json_object *param_1 =
    json_object_array_get_idx(parameters, 0);

  json_object *name =
    json_object_object_get(param_1, "name");
  strcpy(parameter_set.name,
         json_object_to_json_string(name));
  printf("parameters[0].name: %s\n",
         json_object_to_json_string_ext(
           name,
           JSON_C_TO_STRING_PRETTY));

  json_object *data_type =
    json_object_object_get(param_1, "data-type");
  strcpy(parameter_set.data_type,
         json_object_to_json_string(data_type));
  printf("parameters[0].data_type: %s\n",
         json_object_to_json_string_ext(
           data_type,
           JSON_C_TO_STRING_PRETTY));

  json_object *default_value =
    json_object_object_get(param_1, "default");
  strcpy(parameter_set.default_value,
         json_object_to_json_string(default_value));
  printf("parameters[0].default_value: %s\n",
         json_object_to_json_string_ext(
           default_value,
           JSON_C_TO_STRING_PRETTY));

  json_object *valid_values =
    json_object_object_get(param_1, "valid-values");
  int nvalues =
    json_object_array_length(valid_values);
  printf("parameters[0].valid-values: %s\n",
         json_object_to_json_string_ext(
           valid_values,
           JSON_C_TO_STRING_PRETTY));
  for (int i = 0; i < nvalues; i++) {
    json_object *next_value =
      json_object_array_get_idx(valid_values, 0);
  }
  template.params[0] = parameter_set;

  json_object_put(root);
  return 0;
}
