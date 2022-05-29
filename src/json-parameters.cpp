// gcc json-parse00.c -ljson-c -o json-parse00

#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <json-c/json.h>

class Errors {
 public:
  int error_count = 0;
  std::list<std::string> errors;
  bool debug = false;
  bool check_field(json_object *field, std::string name) {
    if (field == NULL) {
      add_error("missing required field: " + name);
      return false;
    }
    return true;
  }

  void add_error(std::string error) {
    error_count++;
    errors.push_back(error);
  }

  void print_errors(std::string indent) {
    for (std::list<std::string>::iterator it = errors.begin(); it != errors.end(); it++)
      std::cout << indent << *it << std::endl;
  }
};

class Request_parameters {
 public:
  std::list<std::string> comments;
  std::string name;
  std::string data_type;
  std::string default_value;
  std::list<std::string> valid_values;
  Errors errors;

  void parse_parameters(json_object *parameters_json) {
    if (errors.debug)
      std::cout << "   parameter element: "
                << json_object_to_json_string_ext(parameters_json, JSON_C_TO_STRING_PRETTY) << std::endl;

    // parse "name"
    json_object *name_json = json_object_object_get(parameters_json, "name");
    if (errors.check_field(name_json, "parameters: name")) {
      name = json_object_to_json_string(name_json);
      if (errors.debug)
        std::cout << "name: " << json_object_to_json_string_ext(name_json, JSON_C_TO_STRING_PRETTY) << std::endl;
    }

    // parse "data-type"
    json_object *data_type_json = json_object_object_get(parameters_json, "data-type");
    if (errors.check_field(data_type_json, "parameters: data_type")) {
      data_type = json_object_to_json_string(data_type_json);
      if (errors.debug)
        std::cout << "data_type: " << json_object_to_json_string_ext(data_type_json, JSON_C_TO_STRING_PRETTY)
                  << std::endl;
    }

    // parse "default"
    json_object *default_value_json = json_object_object_get(parameters_json, "default");
    if (errors.check_field(default_value_json, "parameters: default_value")) {
      default_value = json_object_to_json_string(default_value_json);
      if (errors.debug)
        std::cout << "default_value: " << json_object_to_json_string_ext(default_value_json, JSON_C_TO_STRING_PRETTY)
                  << std::endl;
    }

    // parse "valid-values"
    json_object *valid_values_json = json_object_object_get(parameters_json, "valid-values");
    if (errors.check_field(valid_values_json, "parameters: valid_values")) {
      int nvalues = json_object_array_length(valid_values_json);
      if (errors.debug)
        std::cout << "valid_values: " << json_object_to_json_string_ext(valid_values_json, JSON_C_TO_STRING_PRETTY)
                  << std::endl;
      for (int i = 0; i < nvalues; i++) {
        json_object *next_value_json = json_object_array_get_idx(valid_values_json, i);
        valid_values.push_back(json_object_to_json_string(next_value_json));
      }
    }
  }

  std::string toString() {
    std::ostringstream os;
    std::string indent = "      ";
    os << "    {" << std::endl;
    os << indent << "\"name\": " << name << std::endl;
    os << indent << "\"data-type\"\": " << data_type << std::endl;
    os << indent << "\"default\": " << default_value << std::endl;
    os << indent << "\"valid-values\": [" << std::endl;
    std::list<std::string>::iterator it = valid_values.begin();
    while (it != valid_values.end()) {
      std::string valid_value = *it;
      it++;
      if (it == valid_values.end())
        os << indent << "  " << valid_value << std::endl;
      else
        os << indent << "  " << valid_value << ", " << std::endl;
    }
    os << indent << "]" << std::endl;
    os << "    }" << std::endl;
    return os.str();
  }
};

class Operator_request {
 public:
  std::string id_name;
  std::string domain_name;
  std::string class_name;
  std::string instance_name;
  std::list<Request_parameters *> parameters_list;
  Errors errors;

  void parse_request(json_object *root) {

    // parse "id"
    json_object *id_json = json_object_object_get(root, "id");
    if (errors.check_field(id_json, "request: id")) {
      id_name = json_object_to_json_string(id_json);
      if (errors.debug)
        std::cout << "id: " << json_object_to_json_string_ext(id_json, JSON_C_TO_STRING_PRETTY) << std::endl;
    }

    // parse "domain"
    json_object *domain_json = json_object_object_get(root, "domain");
    if (errors.check_field(domain_json, "request: domain")) {
      domain_name = json_object_to_json_string(domain_json);
      if (errors.debug)
        std::cout << "domain: " << json_object_to_json_string_ext(domain_json, JSON_C_TO_STRING_PRETTY) << std::endl;
    }

    // parse "class"
    json_object *class_json = json_object_object_get(root, "class");
    if (errors.check_field(class_json, "request: class")) {
      class_name = json_object_to_json_string(class_json);
      if (errors.debug)
        std::cout << "class: " << json_object_to_json_string_ext(class_json, JSON_C_TO_STRING_PRETTY) << std::endl;
    }

    // parse "instance"
    json_object *instance_json = json_object_object_get(root, "instance");
    if (errors.check_field(instance_json, "request: instance")) {
      instance_name = json_object_to_json_string(instance_json);
      if (errors.debug)
        std::cout << "instance: " << json_object_to_json_string_ext(instance_json, JSON_C_TO_STRING_PRETTY) << std::endl;
    }

    // parse "parameters"
    json_object *parameters_json = json_object_object_get(root, "parameters");
    if (errors.check_field(parameters_json, "request: parameters")) {

      int nparams = json_object_array_length(parameters_json);
      for (int i = 0; i < nparams; i++) {
        json_object *parameter_elem = json_object_array_get_idx(parameters_json, i);

        Request_parameters *parameters = new Request_parameters();
        if (errors.debug)
          std::cout << "parameters: " << json_object_to_json_string_ext(parameter_elem, JSON_C_TO_STRING_PRETTY)
                    << std::endl;

        parameters->parse_parameters(parameter_elem);
        parameters_list.push_back(parameters);

      }
      if (errors.error_count)
        errors.print_errors("");
      for (std::list<Request_parameters *>::iterator it = parameters_list.begin(); it != parameters_list.end(); it++) {
        Request_parameters *parameters = *it;
        if (parameters->errors.error_count)
          parameters->errors.print_errors("    ");
      }
    }
  }
  std::string toString() {
    std::ostringstream os;
    std::string indent = "  ";
    os << "{" << std::endl;
    os << indent << "\"id\": " << id_name << std::endl;
    os << indent << "\"domain\": " << domain_name << std::endl;
    os << indent << "\"class\": " << class_name << std::endl;
    os << indent << "\"instance\": " << instance_name << std::endl;
    os << indent << "\"parameters\": [" << std::endl;

    for (std::list<Request_parameters *>::iterator it = parameters_list.begin(); it != parameters_list.end(); it++) {
      Request_parameters *parameters = *it;
      os << parameters->toString();
    }

    os << "  ]" << std::endl << "}" << std::endl;
    return os.str();
  }
};

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "usage: " << argv[0] << " instance-template.json" << std::endl;
    exit(0);
  }
  //json_object *root = json_object_from_file("operator_request.json");
  std::string instance_template_file = argv[1];
  json_object *root = json_object_from_file(instance_template_file.c_str());
  if (!root) {
    std::cout << "instance template file '" << instance_template_file << "' not valid" << std::endl;
    return 1;
  }
  Operator_request *request = new Operator_request();
  request->parse_request(root);
  std::cout << std::endl << std::endl << "request:" << std::endl << std::endl << request->toString() << std::endl;
  json_object_put(root);
  return 0;
}
