#include <json-c/json.h>
#include <iostream>
#include <list>
#include <cstdio>
#include "file_utils.hpp"

using namespace std;

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

class Errors {
 public:
  int error_ct = 0;
  list<string> error_list;
  void add(string error) {
    error_ct++;
    error_list.push_back(error);
  }
  void merge(Errors &errors) {
    error_ct += errors.error_ct;
    error_list.insert(a.end(), errors.error_list.begin(), errors.error_list.end());
  }
  string toString() {
    ostringstream os;
    for (string error : error_list) {
      os << error << endl;
    }
    return os.str();
  }
};

char *indent_str(int indent) {
  string buf = "";
  for (int i = 0; i < indent; i++)
    buf += " ";
  return buf;
}

class Json_key_string_value_pair {
 public:
  string key;
  string value;
  Json_key_string_value_pair(string m_key, string m_value):
  key(m_key),
  value(m_value){}
};
class Json_key_int_value_pair {
 public:
  string key;
  int value;
  Json_key_int_value_pair(string m_key, int m_value):
      key(m_key),
      value(m_value){}
};

class Json_berkeley_db {
 public:
  string database;
  int id;
  Json_berkeley_db() {}
  static Json_berkeley_db *create_json_berkeley_db(string key, string value, Errors errors) {
    int id;
    Errors local_errors;
    if (!string_to_int(value, &id)) {
      ostringstream os;
      os << "Json_berkeley_db: cannot convert id '" << value << "' to int";
      local_errors.add(os.str());
    }
    if (local_errors.error_ct > 0) {
      errors.merge(local_errors);
      return null;
    } else {
      Json_berkeley_db *jbd = new Json_berkeley_db();
      jbd->key = key;
      jbd->id = id;
      return jbd;
    }
  }
};

class Json_file_descriptor {
 public:
  string directory;
  string filename;
  Json_file_descriptor() {}
  Json_file_descriptor(string m_directory, string m_filename) :
      directory(m_directory),
      filename(m_filename) {
  }
};
class Json_internet_url {
 public:
  string url;
  int rows;
  int columns;
  Errors local_errors;
  Json_internet_url() {}
  static Json_internet_url *create_json_internet_url(string key, string value, Errors errors) {
    Errors local_errors;
    int rows;
    if (!string_to_int(value, &rows)) {
      ostringstream os;
      os << "Json_internet_url: cannot convert rows '" << value << "' to int";
      local_errors.add(os.str());
    }
    int columns;
    if (!string_to_int(value, &columns)) {
      ostringstream os;
      os << "Json_internet_url: cannot convert columns '" << value << "' to int";
      local_errors.add(os.str());
    }
    if (local_errors.error_ct > 0) {
      errors.merge(local_errors);
      return null;
    } else {
      Json_internet_url *jiu = new Json_internet_url();
      jiu->key = key;
      jiu->rows = rows;
      jiu->columns = columns;
      return jiu;
    }
  }
};

class Json_data_descriptor {
 public:
  Json_berkeley_db *db;
  Json_file_descriptor *file;
  Json_internet_url *internet;
  ~Json_data_descriptor() {
    if (db != null) delete db;
    if (file != null) delete file;
    if (internet != null) delete internet;
  }
  Json_data_descriptor() {
    db = null;
    file = null;
    internet = null;
  }
};

class Json_template_parameter {
 public:
  Json_key_value_pair *name;
  Json_key_value_pair *required;
  Json_key_value_pair *data_type;
  Json_key_value_pair *default_value;
  list<string> valid_values;
  ~Json_template_parameter() {
    if (name != null) delete name;
    if (required != null) delete file;
    if (data_type != null) delete internet;
    if (default_value != null) delete internet;
  }
  Json_template_parameter() {
    name = null;
    required = null;
    data_type = null;
    default_value = null;
  }
};

class Json_template {
 public:
  int  id;
  string domain;
  string class_value;
  string instance_value;
  Json_data_descriptor *input_data;
  Json_data_descriptor *output_data;
  list<Json_template_parameter *> parameters;
  void Json_template_parse(string json) {

  }
};

//printing the value corresponding to boolean, double, integer and strings
void json_print_value(int indent, json_object *jobj, Errors &errors) {
  enum json_type type;
  printf("%stype: ", indent_str(indent).c_str(), type);
  type = json_object_get_type(jobj); //Getting the type of the json object
  switch (type) {
    case json_type_boolean:
      printf("%sjson_type_boolean\n", indent_str(indent).c_str());
      printf("%s          value: %s\n", indent_str(indent).c_str(), json_object_get_boolean(jobj) ? "true" : "false");
      break;
    case json_type_double:
      printf("json_type_double\n");
      printf("%s          value: %lf\n", indent_str(indent).c_str(), json_object_get_double(jobj));
      break;
    case json_type_int:
      printf("json_type_int\n");
      printf("%s          value: %d\n", indent_str(indent).c_str(), json_object_get_int(jobj));
      break;
    case json_type_string:
      printf("json_type_string\n");
      printf("%s          value: %s\n", indent_str(indent).c_str(), json_object_get_string(jobj));
      break;
  }

}

void json_parse_array(int indent, json_object *jobj, char *key, Errors &errors) {
  void json_parse(int indent, json_object *jobj, Errors &errors); //Forward Declaration
  enum json_type type;

  json_object *jarray = jobj; //Simply get the array
  if (key) {
    jarray = json_object_object_get(jobj, key); //Getting the array if it is a key value pair
  }

  int arraylen = json_object_array_length(jarray); //Getting the length of the array
  printf("\n%s          Array Length: %d\n", indent_str(indent).c_str(), arraylen);
  int i;
  json_object *jvalue;

  for (i = 0; i < arraylen; i++) {
    jvalue = json_object_array_get_idx(jarray, i); //Getting the array element at position i
    type = json_object_get_type(jvalue);
    if (type == json_type_array) {
      json_parse_array(indent + 4, jvalue, NULL, errors);
    } else if (type != json_type_object) {
      printf("%svalue[%d]: ", indent_str(indent).c_str(), i);
      json_print_value(indent, jvalue);
    } else {
      json_parse(indent, jvalue, errors);
    }
  }
}

// Parsing the json object
void json_parse(int indent, json_object *jobj, Errors &errors) {
  enum json_type type;
  Json_template *json_template = new Json_template();
  json_object_object_foreach(jobj, key, val) {
    type = json_object_get_type(val);
      if (key == "id") {
        if (type == json_type_int)
         Json_key_int_value_pair *create_json_key_int_value_pair(string key, string value, Errors errors) {

        } else if (key == "domain") {
      } else if (key == "class") {
      } else if (key == "instance") {
      } else if (key == "input-data") {
      } else if (key == "output-data") {
      } else if (key == "parameters") {
      } else {      ostringstream os;
        os << "json_parse: unrecognized tag  '"<< key;
        errors.add(os.str());
      }
    }
    /*
    switch (type) {
      case json_type_boolean:
      case json_type_double:
      case json_type_int:
      case json_type_string:
        printf("%skey '%-20s'  ", indent_str(indent).c_str(), key);
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
        printf("%skey '%-20s'  ", indent_str(indent).c_str(), key);
        printf("%sjson_type_object\n", indent_str(indent).c_str());
        jobj = json_object_object_get(jobj, key);
        json_parse(indent, jobj, errors);
        break;
      case json_type_array:
        printf("%skey '%-20s'  ", indent_str(indent).c_str(), key);
        printf("%stype: json_type_array, ", indent_str(indent).c_str());
        json_parse_array(indent, jobj, key);
        break;
    }
     */
  }
}

int main(int argc, char **argv) {
  Errors errors;
  if (argc < 2) {
    printf("usage: %s json-template-filename\n", argv[0]);
    exit(0);
  }
  char *filename = argv[1];
  string string_val = file_utils::read_file(filename);
  //printf("JSON string: %s\n", string_val.c_str());
  json_object *jobj = json_tokener_parse(string_val.c_str());
  if (jobj == NULL)
    cout << "json_tokener_parse() failed:" << endl << errors;
  else
    json_parse(0, jobj, errors);
  //free(string);
}
