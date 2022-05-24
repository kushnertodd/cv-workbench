// gcc json00.c -ljson-c -o json00 

#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main(void)
{
     json_object *root = json_object_from_file("sample.json");
     json_object_object_foreach(root, key, val) 
         printf("%s  -> %s\n", key, json_object_get_string(val));
    
    json_object_put(root);
printf("The json object to string: JSON_C_TO_STRING_PLAIN \n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PLAIN));
printf("The json object to string: JSON_C_TO_STRING_SPACED \n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_SPACED));
printf("The json object to string: JSON_C_TO_STRING_PRETTY \n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
printf("The json object to string: JSON_C_TO_STRING_PRETTY_TAB \n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY_TAB));
printf("The json object to string: JSON_C_TO_STRING_NOZERO \n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_NOZERO));
printf("The json object to string: JSON_C_TO_STRING_NOSLASHESCAPE \n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_NOSLASHESCAPE));

    return 0;
 }
