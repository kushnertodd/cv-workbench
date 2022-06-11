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
#include "experiment.hpp"

bool debug = false;

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
