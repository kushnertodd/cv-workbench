//
// Created by kushn on 6/11/2022.
//

#include <cstdio>
#include <iostream>
#include <iomanip>
#include "errors.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

extern bool debug;

//using namespace std;

/**
 * determine character for Ascii code
 * @param n to convert
 * @return C char
 */
char Workbench_utils::ascii_to_char(int n) {
  return char(n);
}

/**
 * convert C char to string
 * @param c to convert
 * @return c++ string
 */
string Workbench_utils::char_to_string(char c) {
  string s(1, c);
  return s;
}

string Workbench_utils::data_type_enum_to_string(cv_enums::CV_data_type type) {
  switch (type) {
    case cv_enums::CONTOUR:
      return "contour";
    case cv_enums::CONVOLUTION_KERNEL:
      return "convolution kernel";
    case cv_enums::CONVOLVED_IMAGE:
      return "convolved image";
    case cv_enums::CORRELATED_IMAGE:
      return "correlated image";
    case cv_enums::IMAGE:
      return "image";
    case cv_enums::JSON_EXPERIMENT:
      return "json experiment";
    case cv_enums::JSON_EXPERIMENT_RESULTS:
      return "json experiment results";
    case cv_enums::HISTOGRAM:
      return "histogram";
    case cv_enums::HOUGH:
      return "hough";
    case cv_enums::PATTERN_FEATURE:
      return "pattern feature";
    case cv_enums::PATTERN_IMAGE:
      return "pattern image";
    case cv_enums::PYRAMID:
      return "pyramid";
    case cv_enums::QUADTREE:
      return "quadtree";
    case cv_enums::REGION:
      return "region";
    default:
      return "unknown data type";
  }
}

string Workbench_utils::file_format_to_string(cv_enums::CV_image_file_format type) {
  switch (type) {
    case cv_enums::BINARY:
      return "binary";
    case cv_enums::JPEG:
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
bool Workbench_utils::hex_string_to_int(string arg, unsigned long long &value) {
  stringstream ss;
  ss << std::hex << arg;
  if (ss >> value) {
    return true;
  } else
    return false;
}

string Workbench_utils::image_depth_enum_to_string(cv_enums::CV_image_depth depth) {
  switch (depth) {
    case cv_enums::CV_8U:
      return "cv_enums::CV_8U";
    case cv_enums::CV_8S:
      return "CV_8S";
    case cv_enums::CV_16U:
      return "CV_16U";
    case cv_enums::CV_16S:
      return "CV_16S";
    case cv_enums::CV_32S:
      return "cv_enums::CV_32S";
    case cv_enums::CV_32F:
      return "cv_enums::CV_32F";
    case cv_enums::CV_64F:
      return "CV_64F";
    case cv_enums::CV_16F:
      return "CV_16F";
    default:
      return "unknown image depth";
  }
}

string Workbench_utils::indent(int n) {
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
string Workbench_utils::int_to_hex_string(unsigned long long i, int width) {
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
string Workbench_utils::int_to_string(int i, int width) {
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
bool Workbench_utils::is_numeric(string number) {
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

/**
 * Parsing the json object
 * @param jobj json-c parsed json
 */
void Workbench_utils::json_parse(json_object *jobj) {
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

void Workbench_utils::json_parse_array(json_object *jobj, char *key) {
  //void json_parse(json_object *jobj); /*Forward Declaration*/
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

/*printing the value corresponding to boolean, double, integer and strings*/
void Workbench_utils::json_print_value(json_object *jobj) {
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
string Workbench_utils::real_to_string(double i, int width) {
  ostringstream os;
  if (width == -1) {
    os << i;
  } else {
    os << setw(width) << i;
  }
  return os.str();
}

string Workbench_utils::repository_type_enum_to_string(cv_enums::CV_repository_type type) {
  switch (type) {
    case cv_enums::BERKELEY_DB:
      return "Berkeley DB";
    case cv_enums::FILESYSTEM:
      return "Filesystem";
    case cv_enums::INTERNET:
      return "Internet";
    case cv_enums::EXPERIMENT_STEP:
      return "Experiment step";
    default:
      return "unknown repository type";
  }
}

bool Workbench_utils::string_to_bool(string str, bool &bvalue) {
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

cv_enums::CV_data_type Workbench_utils::string_to_data_type_enum(string type) {
  if (type == "contour")
    return cv_enums::CONTOUR;
  else if (type == "convolution kernel")
    return cv_enums::CONVOLUTION_KERNEL;
  else if (type == "convolved image")
    return cv_enums::CONVOLVED_IMAGE;
  else if (type == "correlated image")
    return cv_enums::CORRELATED_IMAGE;
  else if (type == "image")
    return cv_enums::IMAGE;
  else if (type == "json experiment")
    return cv_enums::JSON_EXPERIMENT;
  else if (type == "json experiment results")
    return cv_enums::JSON_EXPERIMENT_RESULTS;
  else if (type == "histogram")
    return cv_enums::HISTOGRAM;
  else if (type == "hough")
    return cv_enums::HOUGH;
  else if (type == "pattern feature")
    return cv_enums::PATTERN_FEATURE;
  else if (type == "pattern image")
    return cv_enums::PATTERN_IMAGE;
  else if (type == "pyramid")
    return cv_enums::PYRAMID;
  else if (type == "quadtree")
    return cv_enums::QUADTREE;
  else if (type == "region")
    return cv_enums::REGION;
  else
    return cv_enums::UNDEFINED_DATA_TYPE;
}

cv_enums::CV_image_file_format Workbench_utils::string_to_file_format_enum(string type) {
  if (type == "binary")
    return cv_enums::BINARY;
  else if (type == "jpeg")
    return cv_enums::JPEG;
  else return cv_enums::UNDEFINED_FILE_FORMAT;
}

cv_enums::CV_image_depth Workbench_utils::string_to_image_depth_enum(string depth) {
  if (depth == "cv_enums::CV_8U") return cv_enums::CV_8U;
  else if (depth == "CV_8S") return cv_enums::CV_8S;
  else if (depth == "CV_16U") return cv_enums::CV_16U;
  else if (depth == "CV_16S") return cv_enums::CV_16S;
  else if (depth == "cv_enums::CV_32S") return cv_enums::CV_32S;
  else if (depth == "cv_enums::CV_32F") return cv_enums::CV_32F;
  else if (depth == "CV_64F") return cv_enums::CV_64F;
  else if (depth == "CV_16F") return cv_enums::CV_16F;
  else return cv_enums::UNDEFINED_IMAGE_DEPTH;
}

bool Workbench_utils::string_to_int(string str, int &value) {
  if (!is_numeric(str)) return false;
  stringstream ss(str);
  if (ss >> value) return true;
  else return false;
}

cv_enums::CV_repository_type Workbench_utils::string_to_repository_type_enum(string type) {
  if (type == "berkeley_db") return cv_enums::BERKELEY_DB;
  else if (type == "filesystem") return cv_enums::FILESYSTEM;
  else if (type == "internet") return cv_enums::INTERNET;
  else if (type == "step-output") return cv_enums::EXPERIMENT_STEP;
  else return cv_enums::UNDEFINED_REPOSITORY_TYPE;
}

bool Workbench_utils::string_to_real(string str, double &value) {
  if (!is_numeric(str)) return false;
  stringstream ss(str);
  if (ss >> value) return true;
  else return false;
}

bool Workbench_utils::write_double(FILE *fp, double value, string message, Errors &errors) {
  fwrite(&value, sizeof(double), 1, fp);
  if (ferror(fp) != 0) {
    errors.add(message);
    return false;
  }
  return true;
}

bool Workbench_utils::write_double_buffer(FILE *fp, double *buf, double count, string message, Errors &errors) {
  fwrite(buf, sizeof(double), count, fp);
  if (ferror(fp) != 0) {
    errors.add(message);
    return false;
  }
  return true;
}

bool Workbench_utils::write_float(FILE *fp, float value, string message, Errors &errors) {
  fwrite(&value, sizeof(float), 1, fp);
  if (ferror(fp) != 0) {
    errors.add(message);
    return false;
  }
  return true;
}

bool Workbench_utils::write_float_buffer(FILE *fp, float *buf, float count, string message, Errors &errors) {
  fwrite(buf, sizeof(float), count, fp);
  if (ferror(fp) != 0) {
    errors.add(message);
    return false;
  }
  return true;
}

bool Workbench_utils::write_int(FILE *fp, int value, string message, Errors &errors) {
  fwrite(&value, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add(message);
    return false;
  }
  return true;
}

bool Workbench_utils::write_int_buffer(FILE *fp, int *buf, int count, string message, Errors &errors) {
  fwrite(buf, sizeof(int), count, fp);
  if (ferror(fp) != 0) {
    errors.add(message);
    return false;
  }
  return true;
}











