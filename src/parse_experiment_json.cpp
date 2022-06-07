// A simple and complete json parser
// https://linuxprograms.wordpress.com/2010/08/19/json_parser_json-c/

/*

This parser makes use of all the functions which reads the value of a json object. This parser is complete in all respects. You can make use of the functions to create parser for your various requirements

*/

#include <json-c/json.h>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include "file_utils.hpp"
using namespace std;

bool string_to_int(string str, int &value) {
  stringstream s;
  s << str;
  if (s >> value)
    return true;
  else
    return false;
}

bool string_to_bool(string str, bool &bvalue) {
  if (str == "true") {
    bvalue = true;
    return true;
  } else if (str == "false") {
    bvalue = false;
    return true;
  } else {
    return false;
  }
}

class Errors {
 public:
  int error_ct = 0;
  list<string> error_list;
  void add(string error) {
    error_ct++;
    error_list.push_back(error);
  }
  void merge(Errors &errors) {
    error_ct += errors.error_ct;
    error_list.insert(error_list.end(), errors.error_list.begin(), errors.error_list.end());
  }
  string toString() {
    ostringstream os;
    for (string error: error_list) {
      os << error << endl;
    }
    return os.str();
  }
};

/*printing the value corresponding to boolean, double, integer and strings*/
void print_json_value(json_object *jobj) {
  enum json_type type;
  type = json_object_get_type(jobj); /*Getting the type of the json object*/
  //printf("type: %d '%s'\n",type, json_type_to_name(type));
  cout << "type: " << type << "'" << json_type_to_name(type) << "'" << endl;
  switch (type) {
    //case json_type_null: printf("json_type_null\n");
    case json_type_null:
      cout << "json_type_null" << endl;
      //case json_type_boolean: printf("json_type_boolean\n");
    case json_type_boolean:
      cout << "json_type_boolean" << endl;
      //printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
      cout << "value: " << (json_object_get_boolean(jobj) ? "true" : "false") << endl;
      break;
      //case json_type_double: printf("json_type_double\n");
    case json_type_double:
      cout << "json_type_double" << endl;
      //printf("          value: %lf\n", json_object_get_double(jobj));
      cout << "          value: " << json_object_get_double(jobj) << endl;
      break;
      //case json_type_int: printf("json_type_int\n");
    case json_type_int:
      cout << "json_type_int" << endl;
      //printf("          value: %d\n", json_object_get_int(jobj));
      cout << "          value: " << json_object_get_int(jobj) << endl;
      break;
      //case json_type_string: printf("json_type_string\n");
    case json_type_string:
      cout << "json_type_string" << endl;
      //printf("          value: %s\n", json_object_get_string(jobj));
      cout << "          value: " << json_object_get_string(jobj) << endl;
      break;
    case json_type_object:
    case json_type_array:
      break;
  }

}

void json_parse_array(json_object *jobj, char *key) {
  void json_parse(json_object *jobj); /*Forward Declaration*/
  enum json_type type;

  json_object *jarray = jobj; /*Simply get the array*/
  if (key) {
    jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
  }

  int arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
  //printf("Array Length: %d\n",arraylen);
  cout << "Array Length: " << arraylen << endl;
  int i;
  json_object *jvalue;

  for (i = 0; i < arraylen; i++) {
    jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
    type = json_object_get_type(jvalue);
    if (type == json_type_array) {
      json_parse_array(jvalue, NULL);
    } else if (type != json_type_object) {
      //printf("value[%d]: ",i);
      cout << "value[" << i << "]: " << endl;
      print_json_value(jvalue);
    } else {
      json_parse(jvalue);
    }
  }
}

enum repository_type {
  BERKELEY_DB, // separate file for each cv_data_type
  FILESYSTEM, // directory, filename
  INTERNET, // endpoint that produced binary data
  EXPERIMENT_STEP // output of experiment step
};

enum cv_data_type {
  // maybe BINARY_IMAGE for morphological operations
  CONTOUR, // boundary polygon
  CONVOLUTION_KERNEL,
  CONVOLVED_IMAGE, // CV_32F, maybe e.g. FLOAT_IMAGE instead
  CORRELATED_IMAGE, // probably CV_32S/F, image correlated with patter
  IMAGE, // pixels, size, depth is CV_8U, CV_32S, or CV_32F images initially
  JSON_EXPERIMENT, // experiment definition
  JSON_EXPERIMENT_RESULTS, // result of experiment run
  HISTOGRAM, // CV_8U images initially
  HOUGH, // accumulation space + found features
  PATTERN_FEATURE, // e.g. lines, circles for matching
  PATTERN_IMAGE, // for exact sub-image matching
  PYRAMID, // Burt structure
  QUADTREE, // Samet structure
  REGION // complex area, shape properties
};

class data_source_descriptor {
 public:
  int id;
  repository_type repository_type_;
  data_source_descriptor(int m_id, repository_type m_repository_type_) :
      id(m_id),
      repository_type_(m_repository_type_) {}
};

class berkeley_db_data_source_descriptor : data_source_descriptor {
 public:
  cv_data_type cv_data_type_; // implies database file
  int ref_id; // database key
  berkeley_db_data_source_descriptor(cv_data_type m_cv_data_type_, int m_ref_id) :
      data_source_descriptor(BERKELEY_DB),
      cv_data_type_(m_cv_data_type_),
      ref_id(m_ref_id) {}
};

class filesystem_data_source_descriptor : data_source_descriptor {
 public:
  string directory;
  string filename;
  cv_data_type cv_data_type_;
// image data type
  string depth; // CV_8U, CV_32S, or CV_32F
  int rows;
  int cols;
  filesystem_data_source_descriptor(string m_directory,
                                    string m_filename,
                                    cv_data_type m_cv_data_type_,
                                    string depth, m_depth,
                                    int m_rows,
                                    int m_cols) :
      repository_type_(FILESYSTEM),
      directory(m_directory),
      filename(m_filename),
      cv_data_type_(m_cv_data_type_),
      depth(m_depth),
      rows(m_rows),
      cols(m_cols) {}
};

class internet_data_source_descriptor : data_source_descriptor {
 public:
  string url;
  cv_data_type cv_data_type_;
  string depth; // CV_8U, CV_32S, or CV_32F
  int rows;
  int cols;
  internet_data_source_descriptor(string m_directory,
                                  string m_url,
                                  cv_data_type m_cv_data_type_,
                                  string depth, m_depth,
                                  int m_rows,
                                  int m_cols) :
      repository_type_(INTERNET),
      url(m_url),
      cv_data_type_(m_cv_data_type_),
      depth(m_depth),
      rows(m_rows),
      cols(m_cols) {}
};

class experiment_step_data_source_descriptor : data_source_descriptor {
 public:
  int step_id; // prior step id; implies cv_data_type
  int ref_id; // output data source id
  experiment_step_data_source_descriptor(int m_step_id, m_ref_id) :
      repository_type_(EXPERIMENT_STEP),
      step_id(m_step_id),
      ref_id(m_ref_id) {}
};

class operator_parameters {
 public:
  // not sure
};

class Experiment_step {
 public:
  int id;
  string operator;
  list<data_source_descriptor *> input_data_sources;
  list<data_source_descriptor *> output_data_stores;
  list<operator_parameter> operator_parameters;
  Experiment_step() {}
  Experiment_step(int m_id, string m_operator) : id(m_id), operator(
  m_operator) {}
};

class Experiment {
 public:
  list<Experiment_step *> experiment_steps;
  Experiment() {}
};

void json_parse_step_item_type_check(string item, json_type type_expected,
                                     json_type type_found, Errors &errors) {
  ostringstream os;
  if (jobj == nullptr) {
    os << "step " << i << ": expected " << item << " as " << json_type_to_name(type_expected)
       << ", found to be " << json_type_to_name(type_found);
    errors.add(os.str());
  }
}
/**
 * parse json experiment step;
 * Assumes:
 *   all json_object* arguments non-null
 * @param id
 * @param json_id
 * @param json_operator
 * @param json_input_data
 * @param json_output_data
 * @param json_parameters
 */
Experiment_step *json_parse_step(
    int id,
    json_object *json_id,
    json_object *json_operator,
    json_object *json_input_data,
    json_object *json_output_data,
    json_object *json_parameters,
    Errors &errors
) {
  Experiment_step *experiment_step = new Experiment_step();
  json_type json_id_type = json_object_get_type(json_id);
  if (json_id_type != json_type_int) {
    json_parse_step_item_type_check("id", json_type_int, json_id_type, errors);
  } else {
    experiment_step->id = json_object_get_int(json_id);
  }
  json_type json_operator_type = json_object_get_type(json_operator);
  if (json_operator_type != json_type_string) {
    json_parse_step_item_type_check("operator", json_type_string, json_operator_type, errors);
  } else {
    experiment_step->operator=
    json_object_get_int(json_operator);
  }
  json_type json_input_data_input_data = json_object_get_type(json_input_data);
  if (json_input_data_type != json_type_array) {
    json_parse_step_item_type_check("input-data", json_type_array, json_input_data_type, errors);
  } else {
    // parse input data array
    int nsteps = json_object_array_length(json_input_data);
    for (int i = 0; i < nsteps; i++) {
      json_object *json_input_data_descriptor = json_object_array_get_idx(json_input_data, i);
      experiment_step->input_data_sources.push_back(
          json_parse_data_descriptor(json_input_data_descriptor, errors));
    }
  }
  json_type json_output_data_output_data = json_object_get_type(json_output_data);
  if (json_output_data_type != json_type_array) {
    json_parse_step_item_type_check("output-data", json_type_array, json_output_data_type, errors);
  } else {
    // parse output data array
    int nsteps = json_object_array_length(json_output_data);
    for (int i = 0; i < nsteps; i++) {
      json_object *json_output_data_descriptor = json_object_array_get_idx(json_output_data, i);
      experiment_step->output_data_sources.push_back(
          json_parse_data_descriptor(json_output_data_descriptor, errors));
    }
  }
  return experiment_step;
}

void json_parse_step_item_check(json_object *jobj, int i, string key, Errors &errors) {
  ostringstream os;
  if (jobj == nullptr) {
    os << "steps: step " << i << " missing key " << key;
    errors.add(os.str());
  }
}
/**
 * Parse experiment json
 * @param jobj  json-c parsed json
 * @param errors experiment parse errors
 */
Experiment_step *json_parse_steps(json_object *jobj, Experiment *experiment, Errors &errors) {
  Experiment_step *experiment_step = new Experiment_step();
  json_object *json_steps = json_object_object_get(jobj, "steps");
  if (json_steps == nullptr) {
    errors.add("'steps' key missing");
  } else {
    enum json_type type = json_object_get_type(json_steps);
    if (type != json_type_array) {
      errors.add("expected 'steps' value as json array, not "
                     + string(json_type_to_name(type)) + ".");
    } else {
      int nsteps = json_object_array_length(json_steps);
      for (int i = 0; i < nsteps; i++) {
        json_object *json_step = json_object_array_get_idx(json_steps, i);
        json_object *json_id = json_object_get(json_step, "id"));
        json_parse_step_item_check(json_id, i, "id", errors);
        json_object *json_operator = json_object_get(json_step, "operator"));
        json_parse_step_item_check(json_operator, i, "operator", errors);
        json_object *json_input_data = json_object_get(json_step, "input-data"));
        json_parse_step_item_check(json_input_data, i, "input-data", errors);
        json_object *json_output_data = json_object_get(json_step, "output-data"));
        json_parse_step_item_check(json_output_data, i, "output-data", errors);
        json_object *json_parameters = json_object_get(json_step, "parameters"));
        json_parse_step_item_check(json_parameters, i, "parameters", errors);
        if (errors.error_ct == 0) {
          experiment->experiment_steps.push_back(json_parse_step(i, json_id,
                                                                 json_operator,
                                                                 json_input_data,
                                                                 json_output_data,
                                                                 json_parameters,
                                                                 errors));
        }
      }
    }
  }
}
/**
 * Parse experiment json
 * @param jobj  json-c parsed json
 * @param errors experiment parse errors
 */
Experiment *json_parse_experiment(json_object *jobj, Errors &errors) {
  Experiment *experiment = nullptr;
  json_object *json_experiment = json_object_object_get(jobj, "experiment");
  if (json_experiment == nullptr) {
    errors.add("'experiment' key missing");
  } else {
    enum json_type type = json_object_get_type(json_experiment);
    if (type != json_type_object) {
      errors.add("expected 'experiment' value as json object, not "
                     + string(json_type_to_name(type)) + ".");
    } else {
      experiment = new Experiment();
      json_parse_steps(json_experiment, experiment, errors);
    }
  }
  return experiment;
}

/**
 * Parsing the json object
 * @param jobj json-c parsed json
 */
void json_parse(json_object *jobj) {
  enum json_type type;
  json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
    type = json_object_get_type(val);
    //printf("\nkey: '%s' type: %d '%s'\n",key, type, json_type_to_name(type));
    cout << endl << "key: '" << key << "' type: " << type << " '" << json_type_to_name(type) << "'" << endl;
    switch (type) {
      case json_type_boolean:
      case json_type_double:
      case json_type_int:
      case json_type_string:
      case json_type_null:
        print_json_value(val);
        break;
        //case json_type_object: printf("json_type_object\n");
      case json_type_object:
        cout << "json_type_object" << endl;
        jobj = json_object_object_get(jobj, key);
        json_parse(jobj);
        break;
        //case json_type_array: printf("type: json_type_array, ");
      case json_type_array:
        cout << "type: json_type_array, ";
        json_parse_array(jobj, key);
        break;
    }
  }
}

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
    Experiment *experiment_ =
        json_parse_experiment(jobj, errors);
    if (errors.error_ct > 0) {
      cout << "parse_experiment_json: there were errors." << endl << errors.toString();
    }
  }
}
