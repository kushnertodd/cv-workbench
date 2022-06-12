//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_utils.hpp"

extern bool debug;

using namespace std;

string indent(int n) {
  string s;
  for (int i = 0; i < n; i++) {
    s += " ";
  }
  return s;
}

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
  json_object *jvalue;

  for (int i = 0; i < arraylen; i++) {
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

string repository_name_to_string(Repository_type_enum type) {
  switch (type) {
    case BERKELEY_DB:
      return "Berkeley DB";
    case FILESYSTEM:
      return "Filesystem";
    case INTERNET:
      return "Internet";
    case EXPERIMENT_STEP:
      return "Experiment step";
    default:
      return "unknown repository type";
  }
}

string data_type_to_string(Cv_data_type_enum type) {
  switch (type) {
    case CONTOUR:
      return "contour";
    case CONVOLUTION_KERNEL:
      return "convolution kernel";
    case CONVOLVED_IMAGE:
      return "convolved image";
    case CORRELATED_IMAGE:
      return "correlated image";
    case IMAGE:
      return "image";
    case JSON_EXPERIMENT:
      return "json experiment";
    case JSON_EXPERIMENT_RESULTS:
      return "json experiment results";
    case HISTOGRAM:
      return "histogram";
    case HOUGH:
      return "hough";
    case PATTERN_FEATURE:
      return "pattern feature";
    case PATTERN_IMAGE:
      return "pattern image";
    case PYRAMID:
      return "pyramid";
    case QUADTREE:
      return "quadtree";
    case REGION:
      return "region";
    default:
      return "unknown data type";
  }
}

Cv_data_type_enum string_to_data_type(string type) {
  if (type == "contour")
    return CONTOUR;
  else if (type == "convolution kernel")
    return CONVOLUTION_KERNEL;
  else if (type == "convolved image")
    return CONVOLVED_IMAGE;
  else if (type == "correlated image")
    return CORRELATED_IMAGE;
  else if (type == "image")
    return IMAGE;
  else if (type == "json experiment")
    return JSON_EXPERIMENT;
  else if (type == "json experiment results")
    return JSON_EXPERIMENT_RESULTS;
  else if (type == "histogram")
    return HISTOGRAM;
  else if (type == "hough")
    return HOUGH;
  else if (type == "pattern feature")
    return PATTERN_FEATURE;
  else if (type == "pattern image")
    return PATTERN_IMAGE;
  else if (type == "pyramid")
    return PYRAMID;
  else if (type == "quadtree")
    return QUADTREE;
  else if (type == "region")
    return REGION;
  else
    return UNDEFINED_DATA_TYPE;
}

string file_format_to_string(Cv_image_file_format_enum type) {
  switch (type) {
    case BINARY:
      return "binary";
    case JPEG:
      return "jpeg";
    default:
      return "invalid image format";
  }
}

Cv_image_file_format_enum string_to_file_format(string type) {
  if (type == "binary")
    return BINARY;
  else if (type == "jpeg")
    return JPEG;
  else return UNDEFINED_FILE_FORMAT;
}

void operator_filter_edge_sobel(Data_source_descriptor *input_data_source,
                                Data_source_descriptor *output_data_store,
                                map<string, string> operator_parameters,
                                Errors &errors) {
  if (debug)
    cout << "operator_filter_edge_sobel: " << endl
         << "   input_data_source '"
         << input_data_source->toString()
         << "'" << endl
         << "   output_data_store '"
         << output_data_store->toString()
         << "'" << endl << "   parameters " << endl;

  if (debug) {
    map<string, string>::iterator it;
    for (it = operator_parameters.begin(); it != operator_parameters.end(); it++) {
      cout << "      '" << it->first    // string (key)
           << "': '"
           << it->second   // string's value
           << "'" << endl;
    }
  }
  if (operator_parameters.find("orientation") == operator_parameters.end()) {
    errors.add("operator_filter_edge_sobel: missing 'orientation' parameter");
  } else {
    int orientation;
    string orientation_str = operator_parameters["orientation"];
    if (string_to_int(orientation_str, orientation)) {
      cout << "sobeling! orientation " << orientation << endl;
    } else {
      errors.add("operator_filter_edge_sobel: invalid 'orientation' parameter: '" + orientation_str + "'");
    }
  }
}
