//
// Created by kushn on 6/11/2022.
//

#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include "cv_data_format.hpp"
#include "cv_data_type.hpp"
#include "cv_repository_type.hpp"
#include "errors.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

extern bool debug;

//

/**
 * determine character for Ascii code
 * @param n to convert
 * @return C char
 */
char wb_utils::ascii_to_char(int n) {
  return char(n);
}

/**
 * convert C char to string
 * @param c to convert
 * @return c++ string
 */
std::string wb_utils::char_to_string(char c) {
  std::string s(1, c);
  return s;
}

/*
std::string wb_utils::data_format_enum_to_ext(CV_data_format::format type) {
  switch (type) {
    case CV_data_format::format::BINARY:
      return "bin";
    case CV_data_format::format::JPEG:
      return "jpg";
    case CV_data_format::format::JSON:
      return "json";
    case CV_data_format::format::LOG:
      return "log";
    case CV_data_format::format::TEXT:
      return "txt";
    default:
      return "invalid image format";
  }
}
*/

/*
std::string wb_utils::data_format_enum_to_string(CV_data_format::format type) {
  switch (type) {
    case CV_data_format::format::BINARY:
      return "binary";
    case CV_data_format::format::JPEG:
      return "jpeg";
    case CV_data_format::format::JSON:
      return "json";
    case CV_data_format::format::LOG:
      return "log";
    case CV_data_format::format::TEXT:
      return "text";
    default:
      return "invalid image format";
  }
}
*/

/*
std::string wb_utils::data_type_enum_to_string(CV_data_type::type type) {
  switch (type) {
    case CV_data_type::type::CONTOUR:
      return "contour";
    case CV_data_type::type::CONVOLUTION_KERNEL:
      return "convolution kernel";
    case CV_data_type::type::CONVOLVED_IMAGE:
      return "convolved image";
    case CV_data_type::type::CORRELATED_IMAGE:
      return "correlated image";
    case CV_data_type::type::IMAGE:
      return "image";
    case CV_data_type::type::JSON_EXPERIMENT:
      return "json experiment";
    case CV_data_type::type::JSON_EXPERIMENT_RESULTS:
      return "json experiment results";
    case CV_data_type::type::HISTOGRAM:
      return "histogram";
    case CV_data_type::type::HOUGH:
      return "hough";
    case CV_data_type::type::PATTERN_FEATURE:
      return "pattern feature";
    case CV_data_type::type::PATTERN_IMAGE:
      return "pattern image";
    case CV_data_type::type::PYRAMID:
      return "pyramid";
    case CV_data_type::type::QUADTREE:
      return "quadtree";
    case CV_data_type::type::REGION:
      return "region";
    default:
      return "unknown data type";
  }
}
*/

float wb_utils::double_to_float(double value) {
  return static_cast<float>(value);
}

void wb_utils::error_exit(const std::string &message) {
  std::cout << message << std::endl;
  exit(0);
}

/*
CV_data_format::format wb_utils::ext_to_data_format_enum(const std::string &ext) {
  if (ext == "bin")
    return CV_data_format::format::BINARY;
  else if (ext == "jpg")
    return CV_data_format::format::JPEG;
  else if (ext == "json")
    return CV_data_format::format::JSON;
  else if (ext == "log")
    return CV_data_format::format::LOG;
  else if (ext == "txt")
    return CV_data_format::format::TEXT;
  else return CV_data_format::format::UNDEFINED_DATA_FORMAT;
}
*/

/**
 * decode hex string to integer
 * @param arg
 * @param value
 * @return
 */
bool wb_utils::hex_string_to_int(const std::string &arg, unsigned long long &value) {
  std::stringstream ss;
  ss << std::hex << arg;
  if (ss >> value) {
    return true;
  } else
    return false;
}

/*
std::string wb_utils::image_depth_enum_to_string(CV_image_depth::depth depth) {
  switch (depth) {
    case CV_image_depth::depth::CV_8U:
      return "CV_image_depth::depth::CV_8U";
//    case CV_image_depth::depth::CV_8S:
//      return "CV_8S";
//    case CV_image_depth::depth::CV_16U:
//      return "CV_16U";
//    case CV_image_depth::depth::CV_16S:
//      return "CV_16S";
//    case CV_image_depth::depth::CV_32S:
//      return "CV_image_depth::depth::CV_32S";
    case CV_image_depth::depth::CV_32F:
      return "CV_image_depth::depth::CV_32F";
//    case CV_image_depth::depth::CV_64F:
//      return "CV_64F";
//    case CV_image_depth::depth::CV_16F:
//      return "CV_16F";
    default:
      return "unknown image depth";
  }
}
*/

std::string wb_utils::indent(int n) {
  std::string s;
  for (int i = 0; i < n; i++) {
    s += " ";
  }
  return s;
}

float wb_utils::int_to_float(int value) {
  return static_cast<float>(value);
}

/**
 * convert int to hex string
 * @param i integer toconvert
 * @param width optional field width
 * @return int formatted in field of width (if specified)
 */
std::string wb_utils::int_to_hex_string(unsigned long long i, int width) {
  std::ostringstream os;
  if (width == -1) {
    os << std::setbase(16) << i;
  } else {
    os << std::setbase(16) << std::setw(width) << i;
  }
  return os.str();
}

/**
 * convert int to string
 * @param i integer toconvert
 * @param width optional field width
 * @return int formatted in field of width (if specified)
 */
std::string wb_utils::int_to_string(int i, int width) {
  std::ostringstream os;
  if (width == -1) {
    os << i;
  } else {
    os << std::setw(width) << i;
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
bool wb_utils::is_numeric(std::string number) {
  int len = static_cast<int>(number.size());
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
void wb_utils::json_parse(json_object *jobj) {
  enum json_type type;
  json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
    type = json_object_get_type(val);
    //printf("\nkey: '%s' type: %d '%s'\n",key, type, json_type_to_name(type));
    std::cout << std::endl << "key: '" << key << "' type: " << type << " '" << json_type_to_name(type) << "'"
              << std::endl;
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
        std::cout << "json_type_object" << std::endl;
        jobj = json_object_object_get(jobj, key);
        json_parse(jobj);
        break;
        //case json_type_array: printf("type: json_type_array, ");
      case json_type_array:
        std::cout << "type: json_type_array, ";
        json_parse_array(jobj, key);
        break;
    }
  }
}

void wb_utils::json_parse_array(json_object *jobj, char *key) {
  //void json_parse(json_object *jobj); /*Forward Declaration*/
  enum json_type type;

  json_object *jarray = jobj; /*Simply get the array*/
  if (key) {
    jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
  }

  size_t arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
  //printf("Array Length: %d\n",arraylen);
  std::cout << "Array Length: " << arraylen << std::endl;
  json_object *jvalue;

  for (int i = 0; i < arraylen; i++) {
    jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
    type = json_object_get_type(jvalue);
    if (type == json_type_array) {
      json_parse_array(jvalue, nullptr);
    } else if (type != json_type_object) {
      //printf("value[%d]: ",i);
      std::cout << "value[" << i << "]: " << std::endl;
      json_print_value(jvalue);
    } else {
      json_parse(jvalue);
    }
  }
}

/*printing the value corresponding to boolean, double, integer and strings*/
void wb_utils::json_print_value(json_object *jobj) {
  enum json_type type;
  type = json_object_get_type(jobj); /*Getting the type of the json object*/
  //printf("type: %d '%s'\n",type, json_type_to_name(type));
  std::cout << "type: " << type << "'" << json_type_to_name(type) << "'" << std::endl;
  switch (type) {
    //case json_type_null: printf("json_type_null\n");
    case json_type_null:
      std::cout << "json_type_null" << std::endl;
      //case json_type_boolean: printf("json_type_boolean\n");
    case json_type_boolean:
      std::cout << "json_type_boolean" << std::endl;
      //printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
      std::cout << "value: " << (json_object_get_boolean(jobj) ? "true" : "false") << std::endl;
      break;
      //case json_type_double: printf("json_type_double\n");
    case json_type_double:
      std::cout << "json_type_double" << std::endl;
      //printf("          value: %lf\n", json_object_get_double(jobj));
      std::cout << "          value: " << json_object_get_double(jobj) << std::endl;
      break;
      //case json_type_int: printf("json_type_int\n");
    case json_type_int:
      std::cout << "json_type_int" << std::endl;
      //printf("          value: %d\n", json_object_get_int(jobj));
      std::cout << "          value: " << json_object_get_int(jobj) << std::endl;
      break;
      //case json_type_string: printf("json_type_string\n");
    case json_type_string:
      std::cout << "json_type_string" << std::endl;
      //printf("          value: %s\n", json_object_get_string(jobj));
      std::cout << "          value: " << json_object_get_string(jobj) << std::endl;
      break;
    case json_type_object:
    case json_type_array:
      break;
  }
}

void wb_utils::read_byte(FILE *fp,
                         pixel_8U &var,
                         const std::string &module,
                         const std::string &id,
                         const std::string &error,
                         Errors &errors) {
  size_t newLen = fread(&var, sizeof(pixel_8U), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    errors.add(module, id, error);
  }
}

void wb_utils::read_byte_buffer(FILE *fp,
                                pixel_8U *buf,
                                int count,
                                const std::string &module,
                                const std::string &id,
                                const std::string &error,
                                Errors &errors) {
  size_t newLen = fread(buf, sizeof(pixel_8U), count, fp);
  if (ferror(fp) != 0 || newLen != count) {
    errors.add(module, id, error);
  }
}

void wb_utils::read_double(FILE *fp,
                           double &var,
                           const std::string &module,
                           const std::string &id,
                           const std::string &error,
                           Errors &errors) {
  size_t newLen = fread(&var, sizeof(double), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    errors.add(module, id, error);
  }
}

void wb_utils::read_double_buffer(FILE *fp,
                                  double *buf,
                                  int count,
                                  const std::string &module,
                                  const std::string &id,
                                  const std::string &error,
                                  Errors &errors) {
  size_t newLen = fread(buf, sizeof(double), count, fp);
  if (ferror(fp) != 0 || newLen != count) {
    errors.add(module, id, error);
  }
}

void wb_utils::read_float(FILE *fp,
                          float &var,
                          const std::string &module,
                          const std::string &id,
                          const std::string &error,
                          Errors &errors) {
  size_t newLen = fread(&var, sizeof(float), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    errors.add(module, id, error);
  }
}

void wb_utils::read_float_buffer(FILE *fp,
                                 float *buf,
                                 int count,
                                 const std::string &module,
                                 const std::string &id,
                                 const std::string &error,
                                 Errors &errors) {
  size_t newLen = fread(buf, sizeof(float), count, fp);
  if (ferror(fp) != 0 || newLen != count) {
    errors.add(module, id, error);
  }
}

void wb_utils::read_int(FILE *fp,
                        int &var,
                        const std::string &module,
                        const std::string &id,
                        const std::string &error,
                        Errors &errors) {
  size_t newLen = fread(&var, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    errors.add(module, id, error);
  }
}

void wb_utils::read_int_buffer(FILE *fp,
                               int *buf,
                               int count,
                               const std::string &module,
                               const std::string &id,
                               const std::string &error,
                               Errors &errors) {
  size_t newLen = fread(buf, sizeof(int), count, fp);
  if (ferror(fp) != 0 || newLen != count) {
    errors.add(module, id, error);
  }
}

/**
 * convert int to string
 * @param i integer toconvert
 * @param width optional field width
 * @return int formatted in field of width (if specified)
 */
std::string wb_utils::real_to_string(double i, int width) {
  std::ostringstream os;
  if (width == -1) {
    os << i;
  } else {
    os << std::setw(width) << i;
  }
  return os.str();
}

/*
std::string wb_utils::repository_type_enum_to_string(CV_repository_type::type type) {
  switch (type) {
    case CV_repository_type::type::BERKELEY_DB:
      return "Berkeley DB";
    case CV_repository_type::type::FILESYSTEM:
      return "Filesystem";
    case CV_repository_type::type::INTERNET:
      return "Internet";
    case CV_repository_type::type::EXPERIMENT_STEP:
      return "Experiment step";
    default:
      return "unknown repository type";
  }
}
*/

int wb_utils::round_double_to_int(double value) {
  return static_cast<int>(round(value));
}

int wb_utils::round_float_to_int(float value) {
  return static_cast<int>(round((double) value));
}

bool wb_utils::string_find(const std::string& text,
                           std::string &prefix,
                           std::string &suffix,
                           const std::string& pat,
                           bool &at_beginning,
                           bool &at_end) {
  size_t text_len = text.length();
  size_t pat_len = pat.length();
  size_t pos = text.find(pat);
  at_beginning = false;
  at_end = false;
  bool found = true;
  if (pos != std::string::npos) {
    at_beginning = (pos == 0);
    at_end = (text_len - pat_len == pos);
    prefix = text.substr(0, pos);
    suffix = text.substr(pos + pat_len);
  } else {
    prefix = "";
    suffix = text;
    found = false;
  }
  return found;
}

bool wb_utils::string_to_bool(const std::string &str, bool &bvalue) {
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

/*
CV_data_format::format wb_utils::string_to_data_format_enum(const std::string &type) {
  if (type == "binary")
    return CV_data_format::format::BINARY;
  else if (type == "jpeg")
    return CV_data_format::format::JPEG;
  else if (type == "text")
    return CV_data_format::format::TEXT;
  else return CV_data_format::format::UNDEFINED_DATA_FORMAT;
}
*/

/*
CV_data_type::type wb_utils::string_to_data_type_enum(const std::string &type) {
  if (type == "contour")
    return CV_data_type::type::CONTOUR;
  else if (type == "convolution kernel")
    return CV_data_type::type::CONVOLUTION_KERNEL;
  else if (type == "convolved image")
    return CV_data_type::type::CONVOLVED_IMAGE;
  else if (type == "correlated image")
    return CV_data_type::type::CORRELATED_IMAGE;
  else if (type == "image")
    return CV_data_type::type::IMAGE;
  else if (type == "json experiment")
    return CV_data_type::type::JSON_EXPERIMENT;
  else if (type == "json experiment results")
    return CV_data_type::type::JSON_EXPERIMENT_RESULTS;
  else if (type == "histogram")
    return CV_data_type::type::HISTOGRAM;
  else if (type == "hough")
    return CV_data_type::type::HOUGH;
  else if (type == "pattern feature")
    return CV_data_type::type::PATTERN_FEATURE;
  else if (type == "pattern image")
    return CV_data_type::type::PATTERN_IMAGE;
  else if (type == "pyramid")
    return CV_data_type::type::PYRAMID;
  else if (type == "quadtree")
    return CV_data_type::type::QUADTREE;
  else if (type == "region")
    return CV_data_type::type::REGION;
  else
    return CV_data_type::type::UNDEFINED_DATA_TYPE;
}
*/

/*
CV_image_depth::depth wb_utils::string_to_image_depth_enum(const std::string &depth) {
  if (depth == "CV_8U") return CV_image_depth::depth::CV_8U;
//  else if (depth == "CV_8S") return cv_enums::CV_8S;
//  else if (depth == "CV_16U") return cv_enums::CV_16U;
//  else if (depth == "CV_16S") return cv_enums::CV_16S;
  else if (depth == "CV_32S") return CV_image_depth::depth::CV_32S;
  else if (depth == "CV_32F") return CV_image_depth::depth::CV_32F;
//  else if (depth == "CV_64F") return cv_enums::CV_64F;
//  else if (depth == "CV_16F") return cv_enums::CV_16F;
  else return CV_image_depth::depth::UNDEFINED_IMAGE_DEPTH;
}
*/

bool wb_utils::string_to_int(const std::string &str, int &value) {
  if (!is_numeric(str)) return false;
  std::stringstream ss(str);
  if (ss >> value) return true;
  else return false;
}

/*
CV_repository_type::type wb_utils::string_to_repository_type_enum(const std::string &type) {
  if (type == "berkeley_db") return CV_repository_type::type::BERKELEY_DB;
  else if (type == "filesystem") return CV_repository_type::type::FILESYSTEM;
  else if (type == "internet") return CV_repository_type::type::INTERNET;
  else if (type == "step-output") return CV_repository_type::type::EXPERIMENT_STEP;
  else return CV_repository_type::type::UNDEFINED_REPOSITORY_TYPE;
}
*/

bool wb_utils::string_to_double(const std::string &str, double &value) {
  if (!is_numeric(str)) return false;
  std::stringstream ss(str);
  if (ss >> value) return true;
  else return false;
}

void wb_utils::write_double(FILE *fp,
                            double value,
                            const std::string &module,
                            const std::string &id,
                            const std::string &error,
                            Errors &errors) {
  fwrite(&value, sizeof(double), 1, fp);
  if (ferror(fp) != 0) {
    errors.add(module, id, error);
  }
}

void wb_utils::write_double_buffer(FILE *fp,
                                   double *buf,
                                   int count,
                                   const std::string &module,
                                   const std::string &id,
                                   const std::string &error,
                                   Errors &errors) {
  fwrite(buf, sizeof(double), count, fp);
  if (ferror(fp) != 0) {
    errors.add(module, id, error);
  }
}

void wb_utils::write_float(FILE *fp,
                           float value,
                           const std::string &module,
                           const std::string &id,
                           const std::string &error,
                           Errors &errors) {
  fwrite(&value, sizeof(float), 1, fp);
  if (ferror(fp) != 0) {
    errors.add(module, id, error);
  }
}

void wb_utils::write_float_buffer(FILE *fp,
                                  float *buf,
                                  int count,
                                  const std::string &module,
                                  const std::string &id,
                                  const std::string &error,
                                  Errors &errors) {
  fwrite(buf, sizeof(float), count, fp);
  if (ferror(fp) != 0) {
    errors.add(module, id, error);
  }
}

void wb_utils::write_int(FILE *fp,
                         int value,
                         const std::string &module,
                         const std::string &id,
                         const std::string &error,
                         Errors &errors) {
  fwrite(&value, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add(module, id, error);
  }
}

void wb_utils::write_int_buffer(FILE *fp,
                                int *buf,
                                int count,
                                const std::string &module,
                                const std::string &id,
                                const std::string &error,
                                Errors &errors) {
  fwrite(buf, sizeof(int), count, fp);
  if (ferror(fp) != 0) {
    errors.add(module, id, error);
  }
}











