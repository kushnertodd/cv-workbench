//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "experiment_step.hpp"
#include "berkeley_db_data_source_descriptor.hpp"
#include "experiment_step_data_source_descriptor.hpp"
#include "filesystem_data_source_descriptor.hpp"
#include "internet_data_source_descriptor.hpp"
#include "operator.hpp"
#include "operator_producer.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

static Data_source_descriptor *json_parse_data_descriptor(json_object *json_data_descriptor, Errors &errors) {
  Data_source_descriptor *data_source_descriptor = nullptr;
  // parse: ' { "id": ... `
  int id;
  json_object *json_id =
      get_json_object("json_parse_data_descriptor", json_data_descriptor, "id",
                      json_type_int, errors);
  if (json_id != nullptr) {
    id = json_object_get_int(json_id);
  }
  Cv_data_type_enum data_type;
  json_object *json_type =
      get_json_object("json_parse_data_descriptor", json_data_descriptor, "type",
                      json_type_string, errors);
  if (json_type != nullptr) {
    string data_type_str = json_object_get_string(json_type);
    if (debug)
      cout << "json_parse_data_descriptor: type '" << data_type_str << "'" << endl;
    data_type = Workbench_utils::string_to_data_type_enum(data_type_str);
  }
  json_object *json_repository =
      get_json_object("json_parse_data_descriptor", json_data_descriptor, "repository",
                      json_type_string, errors);
  if (json_repository != nullptr) {
    string repository = json_object_get_string(json_repository);
    if (repository == "berkeley_db") {
      data_source_descriptor =
          Berkeley_db_data_source_descriptor::json_parse(
              json_data_descriptor, id, data_type, errors);
    } else if (repository == "filesystem") {
      data_source_descriptor =
          Filesystem_data_source_descriptor::json_parse(
              json_data_descriptor, id, data_type, errors);
    } else if (repository == "internet") {
      data_source_descriptor =
          Internet_data_source_descriptor::json_parse(
              json_data_descriptor, id, data_type, errors);
    } else if (repository == "step-output") {
      data_source_descriptor =
          Experiment_step_data_source_descriptor::json_parse(
              json_data_descriptor, id, data_type, errors);
    } else {
      errors.add("invalid data repository type: " + repository);
    }
  }
  return data_source_descriptor;
}

Experiment_step::~Experiment_step() {
  for (Data_source_descriptor *descriptor: input_data_sources) {
    if (descriptor != nullptr)
      delete descriptor;
  }
  for (Data_source_descriptor *descriptor: output_data_stores) {
    if (descriptor != nullptr)
      delete descriptor;
  }
}
Experiment_step::Experiment_step() {}
Experiment_step::Experiment_step(int m_id, string m_operator_name) : id(m_id), operator_name(m_operator_name) {}
/**
 * Parse experiment json
 * @param jobj  json-c parsed json
 * @param errors experiment parse errors
 */
Experiment_step *Experiment_step::json_parse(json_object *json_step, Errors &errors) {
  // parse: ' { "id": ... `
  json_object *json_id = get_json_object("Experiment_step::json_parse", json_step, "id", json_type_int, errors);
  json_object *json_operator = get_json_object("Experiment_step::json_parse", json_step, "operator",
                                               json_type_string, errors);
  json_object *json_input_data = get_json_object("Experiment_step::json_parse", json_step, "input-data",
                                                 json_type_array, errors);
  json_object *json_output_data = get_json_object("Experiment_step::json_parse", json_step, "output-data",
                                                  json_type_array, errors);
  json_object *json_parameters = get_json_object("Experiment_step::json_parse", json_step, "parameters",
                                                 json_type_object, errors);
  Experiment_step *experiment_step = new Experiment_step();
  if (json_id != nullptr)
    experiment_step->id = json_object_get_int(json_id);
  if (json_operator != nullptr)
    experiment_step->operator_name = json_object_get_string(json_operator);
  // parse input data array
  if (json_input_data != nullptr) {
    int nsteps = json_object_array_length(json_input_data);
    for (int i = 0; i < nsteps; i++) {
      json_object *json_input_data_descriptor =
          json_object_array_get_idx(json_input_data, i);
      if (error_check_type("Experiment_step::json_parse", "input-data descriptor",
                           json_input_data_descriptor,
                           json_type_object, errors)) {
        Data_source_descriptor *input_data_store_descriptor =
            json_parse_data_descriptor(json_input_data_descriptor, errors);
        if (input_data_store_descriptor != nullptr)
          experiment_step->input_data_sources.push_back(input_data_store_descriptor);
      }
    }
  }
  // parse output data array
  if (json_output_data != nullptr) {
    int nsteps = json_object_array_length(json_output_data);
    for (int i = 0; i < nsteps; i++) {
      json_object *json_output_data_descriptor =
          json_object_array_get_idx(json_output_data, i);
      if (error_check_type("Experiment_step::json_parse", "output-data descriptor",
                           json_output_data_descriptor, json_type_object, errors)) {
        Data_source_descriptor *output_data_store_descriptor =
            json_parse_data_descriptor(json_output_data_descriptor, errors);
        if (output_data_store_descriptor != nullptr)
          experiment_step->output_data_stores.push_back(output_data_store_descriptor);
      }
    }
  }
  // parse parameters
  if (json_parameters != nullptr) {
    if (debug)
      cout << "json_parameters type = '" << json_type_to_name(json_object_get_type(json_parameters)) << "'" << endl;
    if (error_check_type("Experiment_step::json_parse", "parameters",
                         json_parameters, json_type_object, errors)) {
      json_object_object_foreach(json_parameters, key, val) {
        json_type type = json_object_get_type(val);
        if (type == json_type_string) {
          string val_str = json_object_get_string(val);
          experiment_step->operator_parameters[key] = val_str;
        } else {
          errors.add("Experiment_step::json_parse: invalid parameter type '"
                         + string(json_type_to_name(type))
                         + "' for key '"
                         + string(key) + "'");
        }
      }
    }
  }
  return experiment_step;
}

void Experiment_step::run(Errors &errors) {
  Operator *step_operator = Operator_producer::create_operator(operator_name);
  if (step_operator == nullptr) {
    if (debug)
      cout << "Experiment_step::run: invalid operator '" + operator_name + "'" << endl;
    errors.add("Experiment_step::run: invalid operator '" + operator_name + "'");
  } else {
    if (debug) {
      for (Data_source_descriptor *input_data_source: input_data_sources) {
        cout << "Experiment_step::run input_data_source: " << input_data_source->to_string() << endl;
      }
      for (Data_source_descriptor *output_data_store: output_data_stores) {
        cout << "Experiment_step::run output_data_store: " << output_data_store->to_string() << endl;
      }
      cout << "Experiment_step::run operator_parameters: " << endl;
      String_map::iterator it;
      for (it = operator_parameters.begin(); it != operator_parameters.end(); it++) {
        cout << it->first    // string (key)
             << ':'
             << it->second   // string's value
             << std::endl;
      }
    }

    step_operator->run(input_data_sources, output_data_stores, operator_parameters, errors);
  }
}

string Experiment_step::to_string() {
  ostringstream os;
  os << "Experiment_step::run: id " << id << " operator " << operator_name << endl;
  os << "Experiment_step::run: input data sources" << endl;
  for (Data_source_descriptor *descriptor: input_data_sources) {
    if (descriptor != nullptr)
      os << "   " << descriptor->to_string() << endl;
  }
  cout << "Experiment_step::run: output data stores" << endl;
  for (Data_source_descriptor *descriptor: output_data_stores) {
    if (descriptor != nullptr)
      os << "   " << descriptor->to_string() << endl;
  }
  return os.str();
}
