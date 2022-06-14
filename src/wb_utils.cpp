//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include "image.hpp"
#include "wb_enums.hpp"
#include "wb_utils.hpp"

extern bool debug;

using namespace std;

/**
 * determine character for Ascii code
 * @param n to convert
 * @return C char
 */
char ascii_to_char(int n) {
  return char(n);
}

/**
 * convert C char to string
 * @param c to convert
 * @return c++ string
 */
string char_to_string(char c) {
  string s(1, c);
  return s;
}

string data_type_enum_to_string(Cv_data_type_enum type) {
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

/**
 * decode hex string to integer
 * @param arg
 * @param value
 * @return
 */
bool hex_string_to_int(string arg, unsigned long long &value) {
  stringstream ss;
  ss << std::hex << arg;
  if (ss >> value) {
    return true;
  } else
    return false;
}

string image_depth_enum_to_string(Cv_image_depth_enum depth) {
  switch (depth) {
    case CV_8U:
      return "CV_8U";
    case CV_8S:
      return "CV_8S";
    case CV_16U:
      return "CV_16U";
    case CV_16S:
      return "CV_16S";
    case CV_32S:
      return "CV_32S";
    case CV_32F:
      return "CV_32F";
    case CV_64F:
      return "CV_64F";
    case CV_16F:
      return "CV_16F";
  }
}

string indent(int n) {
  string s;
  for (int i = 0; i < n; i++) {
    s += " ";
  }
  return s;
}

/**
 * convert int to hex string
 * @param i integer toconvert
 * @param width optional field width
 * @return int formatted in field of width (if specified)
 */
string int_to_hex_string(unsigned long long i, int width) {
  ostringstream os;
  if (width == -1) {
    os << setbase(16) << i;
  } else {
    os << setbase(16) << setw(width) << i;
  }
  return os.str();
}

/**
 * convert int to string
 * @param i integer toconvert
 * @param width optional field width
 * @return int formatted in field of width (if specified)
 */
string int_to_string(int i, int width) {
  ostringstream os;
  if (width == -1) {
    os << i;
  } else {
    os << setw(width) << i;
  }
  return os.str();
}

/**
 * verify string is numeric
 * a [+-]\d+
 * b [+-]\d+.
 * c [+-].\d+
 * d [+-]\d+.\d+
 * possibilites:
 *  1 [+-]                 false
 *  2 [+-]\D               false
 *  3 [+-]\d+              a      intdigits
 *  4   [+-]\d+\D          false
 *  5   [+-]\d+.           b      intdigits
 *  6     [+-]\d+.\D       false
 *  7     [+-]\d+.\d+      d      intdigits, fracdigits
 *  8       [+-]\d+.\d+\D  false
 *  9 [+-].                false
 * 10  [+-].\D             false
 * 11  [+-].\d+            c      fracdigits
 * 12    [+-].\d+\D        false
 * @param number
 * @return
 */
bool is_numeric(string number) {
  int len = number.size();
  int pos = 0;
  // look for [+-]
  if (pos < len && (number[pos] == '+' || number[pos] == '-'))
    pos++;
  bool sawIntDigits = false;
  bool sawFracDigits = false;
  bool sawPeriod = false;
  for (; pos < len && isdigit(number[pos]); pos++) {
    sawIntDigits = true; // a, b
  }
  if (pos >= len)
    return sawIntDigits; // a, b, d
  if (number[pos] == '.') {
    sawPeriod = true; // 5-12
    pos++;
    for (; pos < len && isdigit(number[pos]); pos++) {
      sawFracDigits = true; // 7, 8, 11, 12
    }
  }
  if (pos >= len)
    return sawIntDigits || (sawPeriod && sawFracDigits); // 3, 5, 7, 11
  return false; // 1-2, 4, 6, 8-10, 12
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
      json_print_value(jvalue);
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
        json_print_value(val);
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

/*printing the value corresponding to boolean, double, integer and strings*/
void json_print_value(json_object *jobj) {
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

/**
 * convert int to string
 * @param i integer toconvert
 * @param width optional field width
 * @return int formatted in field of width (if specified)
 */
string real_to_string(double i, int width) {
  ostringstream os;
  if (width == -1) {
    os << i;
  } else {
    os << setw(width) << i;
  }
  return os.str();
}

string repository_type_enum_to_string(Cv_repository_type_enum type) {
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

Cv_data_type_enum string_to_data_type_enum(string type) {
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

Cv_image_file_format_enum string_to_file_format_enum(string type) {
  if (type == "binary")
    return BINARY;
  else if (type == "jpeg")
    return JPEG;
  else return UNDEFINED_FILE_FORMAT;
}

Cv_image_depth_enum string_to_image_depth_enum(string depth) {
  if (depth == "CV_8U") return CV_8U;
  else if (depth == "CV_8U") return CV_8U;
  else if (depth == "CV_8S") return CV_8S;
  else if (depth == "CV_16U") return CV_16U;
  else if (depth == "CV_16S") return CV_16S;
  else if (depth == "CV_32S") return CV_32S;
  else if (depth == "CV_32F") return CV_32F;
  else if (depth == "CV_64F") return CV_64F;
  else if (depth == "CV_16F") return CV_16F;

}

Cv_repository_type_enum string_to_repository_type_enum(string type) {
  if (type == "berkeley_db") return BERKELEY_DB;
  else if (type == "filesystem") return FILESYSTEM;
  else if (type == "internet") return INTERNET;
  else if (type == "step-output") return EXPERIMENT_STEP;
}

bool string_to_int(string str, int &value) {
  stringstream ss(str);
  if (ss >> value) return true;
  else return false;
}

bool string_to_real(string arg, double &value) {
  stringstream ss(arg);
  if (ss >> value) return true;
  else return false;
}

/**
 * orientation:
 *      0 = [-1, 0, 1], [-2, 0, 2], [-1, 0, 1]
 *     90 = [1, 2, 1],  [0, 0, 0],  [-1, -2, -1]
 * @param input_data_source
 * @param output_data_store
 * @param operator_parameters
 * @param errors
 */
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
      Image *input = input_data_source->read_image(errors);
      int rows = input->get_rows();
      int cols = input->get_cols();
      int row_stride = input->get_row_stride();
      Image *output = new Image(rows, cols, input->get_components(), CV_8U);
      // Image *output = output_data_store->read_image(errors);
      cout << "still sobeling!" << endl;
      int ptr = 0;
      for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
          if (col < cols - 1) {
            output->buf_8U[row * row_stride + col] =
                255 - abs(input->buf_8U[row * row_stride + col] -
                    input->buf_8U[row * row_stride + col + 1]);
          }
          ptr++;
        }
      }
      output->write_jpeg("sobel.jpg", errors);
    } else {
      errors.add("operator_filter_edge_sobel: invalid 'orientation' parameter: '" + orientation_str + "'");
    }
  }
}












