// A simple and complete json parser
// https://linuxprograms.wordpress.com/2010/08/19/json_parser_json-c/

/*

This parser makes use of all the functions which reads the value of a json object. This parser is complete in all respects. You can make use of the functions to create parser for your various requirements

*/

#include <iostream>
#include <string>
#include <json-c/json.h>
#include "file_utils.hpp"
#include "image.hpp"
#include "experiment.hpp"
#include "hough_accum.hpp"

//bool debug = true;
bool debug = false;


int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "usage: %s json-template-filename" << argv[0] << std::endl;
    exit(0);
  }
  char *filename = argv[1];
  std::string string_val = file_utils::read_file(filename);
  std::cout << "JSON string: " << string_val << std::endl;
  json_object *jobj = json_tokener_parse(string_val.c_str());
  if (jobj == NULL)
    printf("json_tokener_parse() failed\n");
  else {
    Errors errors;
    Experiment *experiment = Experiment::json_parse(jobj, errors);
    errors.check_exit("parse_experiment_json: there were errors.");
      experiment->run(errors);
  }
}
