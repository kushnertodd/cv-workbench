// A simple and complete json parser
// https://linuxprograms.wordpress.com/2010/08/19/json_parser_json-c/

/*

This parser makes use of all the functions which reads the value of a json object. This parser is complete in all respects. You can make use of the functions to create parser for your various requirements

*/

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include "wb_log.hpp"
#include "errors.hpp"
#include "experiment.hpp"
#include "file_utils.hpp"
#include "runtime.hpp"
#include "wb_filename.hpp"

bool debug = false;

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "usage: %s json-template-filename" << argv[0] << std::endl;
    exit(0);
  }
  try {
    char *path = argv[1];
    debug = (argc > 2);
    Runtime::init(path);
    Errors errors;
    std::string contents;
    if (!file_utils::read_file(path, contents))
      errors.add("", "", "cannot read in-filename");
    errors.check_exit("");
    std::unique_ptr<Wb_filename> wb_in_filename(Wb_filename::create_wb_filename(path, errors));
    errors.check_exit("invalid in-filename");

    json_object *jobj = json_tokener_parse(contents.c_str());
    if (jobj == nullptr)
      wb_utils::error_exit("invalid input json");
    else {
      std::string log_filename = wb_in_filename->to_log();
      errors.check_exit();
      Experiment *experiment = Experiment::from_json(jobj, path, errors);
      errors.check_exit();
      experiment->run(errors);
      WB_log::log_to_file(log_filename,
                          json_object_to_json_string_ext(jobj,
                                                         JSON_C_TO_STRING_PRETTY + JSON_C_TO_STRING_NOSLASHESCAPE),
                          errors);
      errors.check_exit();
      exit(0);
    }
  }
  catch (std::exception &ex) {
    std::cerr << "cv-workbench: exception '" << ex.what() << "'" << std::endl;
  }
  catch (const char *ex) {
    std::cerr << "cv-workbench: exception '" << ex << "'" << std::endl;
  }
  catch (std::string &ex) {
    std::cerr << "cv-workbench: exception '" << ex << "'" << std::endl;
  }
  catch (int ex) {
    std::cerr << "cv-workbench: exception id " << ex << std::endl;
  }
}

