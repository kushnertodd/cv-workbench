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
#include "experiment_step.hpp"
#include "filesystem_data_source_descriptor.hpp"
#include "internet_data_source_descriptor.hpp"
#include "experiment_step_data_source_descriptor.hpp"

bool debug = false;


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
