//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "experiment_step.hpp"
#include "berkeley_db_data_source_descriptor.hpp"
#include "experiment_step_data_source_descriptor.hpp"
#include "filesystem_data_source_descriptor.hpp"
#include "internet_data_source_descriptor.hpp"
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
    if (true)
      cout << "json_parse_data_descriptor: type '" << data_type_str << "'" << endl;
    data_type = string_to_data_type(data_type_str);
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
Experiment_step::Experiment_step(int m_id, string m_step_operator) : id(m_id), step_operator(m_step_operator) {}
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
    experiment_step->step_operator = json_object_get_string(json_operator);
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
  cout << "Experiment_step::run: id " << id << " operator " << step_operator << endl;
  cout << "Experiment_step::run: input data sources" << endl;
  for (Data_source_descriptor *descriptor: input_data_sources) {
    if (descriptor != nullptr)
      cout << "   " << descriptor->toString() << endl;
  }
  cout << "Experiment_step::run: output data stores" << endl;
  for (Data_source_descriptor *descriptor: output_data_stores) {
    if (descriptor != nullptr)
      cout << "   " << descriptor->toString() << endl;
  }
  if (step_operator == "filter-edge-Sobel") {
    if (input_data_sources.size() == 0)
      errors.add("Experiment_step::run filter-edge-Sobel: missing input data source");
    else if (input_data_sources.size() > 1)
      errors.add("Experiment_step::run filter-edge-Sobel: too many input data sources");
    if (output_data_stores.size() == 0)
      errors.add("Experiment_step::run filter-edge-Sobel: missing output data source");
    else if (output_data_stores.size() > 1)
      errors.add("Experiment_step::run filter-edge-Sobel: too many output data sources");
    operator_filter_edge_sobel(input_data_sources.front(), output_data_stores.front(),
                               operator_parameters);
  }
}