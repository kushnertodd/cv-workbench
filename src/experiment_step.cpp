//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include <utility>
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "experiment_step.hpp"
#include "berkeley_db_data_source_descriptor.hpp"
#include "experiment_step_data_source_descriptor.hpp"
#include "filesystem_data_source_descriptor.hpp"
#include "internet_data_source_descriptor.hpp"
#include "operator.hpp"
#include "operator_dispatcher.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

extern bool debug;

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

  // parse: ' "type": ... `
  cv_enums::CV_data_type data_type;
  json_object *json_data_type =
      get_json_object("json_parse_data_descriptor",
                      json_data_descriptor,
                      "type",
                      json_type_string,
                      errors);
  if (json_data_type != nullptr) {
    std::string data_type_str = json_object_get_string(json_data_type);
    if (debug)
      std::cout << "json_parse_data_descriptor: type '" << data_type_str << "'" << std::endl;
    data_type = wb_utils::string_to_data_type_enum(data_type_str);
    if (data_type == cv_enums::UNDEFINED_DATA_TYPE)
      errors.add("invalid data type: " + data_type_str);
  }

  // parse: ' "format": ... `
  cv_enums::CV_data_format data_format;
  json_object *json_data_format =
      get_json_object("json_parse_data_descriptor",
                      json_data_descriptor,
                      "format",
                      json_type_string,
                      errors);
  if (json_data_format != nullptr) {
    std::string data_format_str = json_object_get_string(json_data_format);
    if (debug)
      std::cout << "json_parse_data_descriptor: type '" << data_format_str << "'" << std::endl;
    data_format =
        wb_utils::string_to_data_format_enum(data_format_str);
    if (data_format == cv_enums::UNDEFINED_DATA_FORMAT)
      errors.add("invalid data format: " + data_format_str);
  }

  // parse: ' "repository": ... `
  json_object *json_repository =
      get_json_object("json_parse_data_descriptor", json_data_descriptor, "repository",
                      json_type_string, errors);
  if (json_repository != nullptr) {
    std::string repository_str = json_object_get_string(json_repository);
    if (repository_str == "berkeley_db") {
      data_source_descriptor =
          Berkeley_db_data_source_descriptor::json_parse(
              json_data_descriptor, id, data_type, data_format, errors);
    } else if (repository_str == "filesystem") {
      data_source_descriptor =
          Filesystem_data_source_descriptor::json_parse(
              json_data_descriptor, id, data_type, data_format, errors);
    } else if (repository_str == "internet") {
      data_source_descriptor =
          Internet_data_source_descriptor::json_parse(
              json_data_descriptor, id, data_type, data_format, errors);
    } else if (repository_str == "step-output") {
      data_source_descriptor =
          Experiment_step_data_source_descriptor::json_parse(
              json_data_descriptor, id, data_type, data_format, errors);
    } else {
      errors.add("invalid data repository type: " + repository_str);
    }
  }
  return data_source_descriptor;
}

Experiment_step::~Experiment_step() {
  for (Data_source_descriptor *descriptor: input_data_sources) {
    delete descriptor;
  }
  for (Data_source_descriptor *descriptor: output_data_stores) {
    delete descriptor;
  }
}

Experiment_step::Experiment_step() : id(0) {}

Experiment_step::Experiment_step(int m_id, std::string m_operator_name)
    : id(m_id), operator_name(std::move(m_operator_name)) {}
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
  auto *experiment_step = new Experiment_step();
  if (json_id != nullptr)
    experiment_step->id = json_object_get_int(json_id);
  if (json_operator != nullptr)
    experiment_step->operator_name = json_object_get_string(json_operator);
  // parse input data array
  if (json_input_data != nullptr) {
    size_t nsteps = json_object_array_length(json_input_data);
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
    size_t nsteps = json_object_array_length(json_output_data);
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
      std::cout << "json_parameters type = '" << json_type_to_name(json_object_get_type(json_parameters)) << "'"
                << std::endl;
    if (error_check_type("Experiment_step::json_parse", "parameters",
                         json_parameters, json_type_object, errors)) {
      json_object_object_foreach(json_parameters, key, val) {
        json_type type = json_object_get_type(val);
        if (type == json_type_string) {
          std::string val_str = json_object_get_string(val);
          experiment_step->operator_parameters[key] = val_str;
        } else {
          errors.add("Experiment_step::json_parse", "", "invalid parameter type '"
              + std::string(json_type_to_name(type))
              + "' for key '"
              + std::string(key) + "'");
        }
      }
    }
  }
  return experiment_step;
}

void Experiment_step::run(Errors &errors) {
  Operator *step_operator = Operator_dispatcher::create_operator(operator_name);
  if (step_operator == nullptr) {
    if (debug)
      std::cout << "Experiment_step::run: invalid operator '" + operator_name + "'" << std::endl;
    errors.add("Experiment_step::run", "", "invalid operator '" + operator_name + "'");
  } else {
    if (debug) {
      for (Data_source_descriptor *input_data_source: input_data_sources) {
        std::cout << "Experiment_step::run input_data_source: " << input_data_source->to_string() << std::endl;
      }
      for (Data_source_descriptor *output_data_store: output_data_stores) {
        std::cout << "Experiment_step::run output_data_store: " << output_data_store->to_string() << std::endl;
      }
      std::cout << "Experiment_step::run operator_parameters: " << std::endl;
      String_map::iterator it;
      for (it = operator_parameters.begin(); it != operator_parameters.end(); it++) {
        std::cout << it->first    // string (key)
                  << ':'
                  << it->second   // string's value
                  << std::endl;
      }
    }

    step_operator->run(input_data_sources, output_data_stores, operator_parameters, errors);
    delete step_operator;
  }
}

std::string Experiment_step::to_string() {
  std::ostringstream os;
  os << "Experiment_step::run: id " << id << " operator " << operator_name << std::endl;
  os << "Experiment_step::run: input data sources" << std::endl;
  for (Data_source_descriptor *descriptor: input_data_sources) {
    if (descriptor != nullptr)
      os << "   " << descriptor->to_string() << std::endl;
  }
  std::cout << "Experiment_step::run: output data stores" << std::endl;
  for (Data_source_descriptor *descriptor: output_data_stores) {
    if (descriptor != nullptr)
      os << "   " << descriptor->to_string() << std::endl;
  }
  return os.str();
}
