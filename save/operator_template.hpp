//
// Created by kushn on 5/21/2022.
//

#ifndef CV_WORKBENCH_CONFIG_OPERATOR_TEMPLATE_H_
#define CV_WORKBENCH_CONFIG_OPERATOR_TEMPLATE_H_

/*
JSON string: {
  "1-D by 2": {
    "id": 1,
    "domain": "filters",
    "class": "edge detection",
    "parameters": [
      {
        "__comment1": [
          " 0 = [-1, 1] (horiz)",
          "90 = [1, -1] (vert)"
        ],
        "name": "orientation",
        "data-type": "int",
        "default": 0,
        "valid-values": [
          0,
          90
        ]
      }
    ]
  }
}

 */
class json_key_value_pair {
 public:
  string key;
  string value;
};

class json_template_parameter {
 public:
  json_key_value_pair name;
  json_key_value_pair data_type;
  json_key_value_pair default;
  list<string> valid_values;
};

class json_template {
 public:
  json_key_value_pair id;
  json_key_value_pair domain;
  json_key_value_pair class;
  list<json_template_parameter> parameters;
  void json_template_parse(std::string json) {

  }
};

struct parameters_string {
  char* name;
  char* data_type;
  char* default_value;
  char* valid_values[];
};

struct json_string {
  char* id;
  char* domain;
  char* class;
  struct parameters_string parameters;
};

class operator_template {

};

#endif //CV_WORKBENCH_CONFIG_OPERATOR_TEMPLATE_H_
