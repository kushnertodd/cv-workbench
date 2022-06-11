// A simple and complete json parser
// https://linuxprograms.wordpress.com/2010/08/19/json_parser_json-c/

/*

This parser makes use of all the functions which reads the value of a json object. This parser is complete in all respects. You can make use of the functions to create parser for your various requirements

*/

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <json-c/json.h>
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "wb_json_utils.hpp"
#include "errors.hpp"
#include "wb_enums.hpp"
#include "image.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "data_source_descriptor.hpp"
#include "berkeley_db_data_source_descriptor.hpp"
#include "filesystem_data_source_descriptor.hpp"
#include "internet_data_source_descriptor.hpp"
#include "experiment_step_data_source_descriptor.hpp"

bool debug = false;

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
  Cv_data_type_enum cv_data_type_enum;
  json_object *json_type =
      get_json_object("json_parse_data_descriptor", json_data_descriptor, "type",
                      json_type_string, errors);
  if (json_type != nullptr) {
    string data_type = json_object_get_string(json_type);
    if (data_type == "image") {
      cv_data_type_enum = IMAGE;
    } else if (data_type == "histogram") {
      cv_data_type_enum = HISTOGRAM;
    } else if (data_type == "hough") {
      cv_data_type_enum = HOUGH;
    } else {
      errors.add("invalid data descriptor type: " + data_type);
    }
  }
  json_object *json_repository =
      get_json_object("json_parse_data_descriptor", json_data_descriptor, "repository",
                      json_type_string, errors);
  if (json_repository != nullptr) {
    string repository = json_object_get_string(json_repository);
    if (repository == "berkeley_db") {
      data_source_descriptor =
          Berkeley_db_data_source_descriptor::json_parse(
              json_data_descriptor, id, cv_data_type_enum, errors);
    } else if (repository == "filesystem") {
      data_source_descriptor =
          Filesystem_data_source_descriptor::json_parse(
              json_data_descriptor, id, cv_data_type_enum, errors);
    } else if (repository == "internet") {
      data_source_descriptor =
          Internet_data_source_descriptor::json_parse(
              json_data_descriptor, id, cv_data_type_enum, errors);
    } else if (repository == "step-output") {
      data_source_descriptor =
          Experiment_step_data_source_descriptor::json_parse(
              json_data_descriptor, id, cv_data_type_enum, errors);
    } else {
      errors.add("invalid data repository type: " + repository);
    }
  }
  return data_source_descriptor;
}

class Experiment_step {
 public:
  int id;
  string step_operator;
  list<Data_source_descriptor *> input_data_sources;
  list<Data_source_descriptor *> output_data_stores;
  map<string, string> Operator_parameters;
  Experiment_step() {}
  Experiment_step(int m_id, string m_step_operator) : id(m_id), step_operator(m_step_operator) {}
/**
 * Parse experiment json
 * @param jobj  json-c parsed json
 * @param errors experiment parse errors
 */
  static Experiment_step *json_parse(json_object *json_step, Errors &errors) {
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
    return experiment_step;
  }
};

class Experiment {
 public:
  list<Experiment_step *> experiment_steps;
  Experiment() {}
  /**
  * Parse experiment json
  * @param jobj  json-c parsed json
  * @param errors experiment parse errors
  */
  static Experiment *json_parse(json_object *jobj, Errors &errors) {
    // parse: ' "experiment": { ... `
    Experiment *experiment = new Experiment();
    json_object *json_experiment =
        get_json_object("Experiment::json_parse", jobj, "experiment", json_type_object, errors);
    if (json_experiment != nullptr) {
      // parse: ' "steps": [ ... '
      json_object
          *json_steps = get_json_object("Experiment::json_parse", json_experiment, "steps", json_type_array, errors);
      if (json_steps != nullptr) {
        int nsteps = json_object_array_length(json_steps);
        for (int i = 0; i < nsteps; i++) {
          json_object *json_step = json_object_array_get_idx(json_steps, i);
          if (error_check_type("Experiment::json_parse", "step", json_step, json_type_object, errors)) {
            Experiment_step *experiment_step = Experiment_step::json_parse(json_step, errors);
            if (experiment_step != nullptr) {
              experiment->experiment_steps.push_back(experiment_step);
            }
          }
        }
      }
    }
    return experiment;
  }
};

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "usage: %s json-template-filename" << argv[0] << endl;
    exit(0);
  }
  char *filename = argv[1];
  string string_val = file_utils::read_file(filename);
  cout << "JSON string: " << string_val << endl;
  json_object *jobj = json_tokener_parse(string_val.c_str());
  if (jobj == NULL)
    printf("json_tokener_parse() failed\n");
  else {
    Errors errors;
    Experiment *experiment = Experiment::json_parse(jobj, errors);
    if (errors.error_ct > 0) {
      cout << "parse_experiment_json: there were errors." << endl << errors.toString();
    }
  }
}
