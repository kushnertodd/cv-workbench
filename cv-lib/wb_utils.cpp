#include "wb_utils.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "errors.hpp"
#include "wb_defs.hpp"

extern bool debug;

/**
 * @brief determine character for Ascii code
 * @param n to convert
 * @return C char
 */
char wb_utils::ascii_to_char(int n) { return char(n); }
/**
 * @brief convert C char to string
 * @param c to convert
 * @return c++ string
 */
std::string wb_utils::char_to_string(char c) {
    std::string s(1, c);
    return s;
}
/**
 * @brief
 * @param value
 * @return
 */
pixel_32F wb_utils::cv_32S_to_cv_32F(pixel_32S value) { return int_to_float(value); }
/**
 * @brief
 * @param value
 * @return
 */
pixel_32S wb_utils::cv_32F_to_cv_32S(pixel_32F value) { return float_to_int(value); }
/**
 * @brief
 * @param value
 * @return
 */
pixel_32S wb_utils::cv_32F_to_cv_32S_round(pixel_32F value) { return float_to_int_round(value); }
/**
 * @brief
 * @param value
 * @return
 */
float wb_utils::double_to_float(double value) { return static_cast<float>(value); }
/**
 * @brief copies with truncation
 * @param value
 * @return
 */
int wb_utils::double_to_int(double value) { return static_cast<int>(value); }

int wb_utils::double_to_int_round(double value) { return static_cast<int>(round(value)); }
/**
 * @brief
 * @param x
 * @param width
 * @return
 */
std::string wb_utils::double_to_string(double x, int width) {
    std::ostringstream os;
    if (width == -1) {
        os << x;
    } else {
        os << std::setw(width) << x;
    }
    return os.str();
}
/**
 * @brief
 * @param message
 */
void wb_utils::error_exit(const std::string &message) {
    std::cout << message << std::endl;
    exit(0);
}
/**
 * @brief copies with truncation
 * @param value
 * @return
 */
int wb_utils::float_to_int(float value) { return static_cast<int>(value); }
/**
 * @brief
 * @param value
 * @return
 */
int wb_utils::float_to_int_round(float value) { return static_cast<int>(round((double) value)); }
/**
 * @brief decode hex string to integer
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
/**
 * @brief
 * @param n
 * @return
 */
std::string wb_utils::indent(int n) {
    std::string s;
    for (int i = 0; i < n; i++) {
        s += " ";
    }
    return s;
}
/**
 * @brief
 * @param value
 * @return
 */
float wb_utils::int_to_float(int value) { return static_cast<float>(value); }
/**
 * @brief convert int to hex string
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
 * @brief convert int to string
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
 * @brief verify string is numeric
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
 * @brief Parsing the json object
 * @param jobj json-c parsed json
 */
void wb_utils::json_parse(json_object *jobj) {
    enum json_type type;
    json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
        type = json_object_get_type(val);
        // printf("\nkey: '%s' type: %d '%s'\n",key, type, json_type_to_name(type));
        std::cout << std::endl
                  << "key: '" << key << "' type: " << type << " '" << json_type_to_name(type) << "'" << std::endl;
        switch (type) {
            case json_type_boolean:
            case json_type_double:
            case json_type_int:
            case json_type_string:
            case json_type_null:
                json_print_value(val);
                break;
                // case json_type_object: printf("json_type_object\n");
            case json_type_object:
                std::cout << "json_type_object" << std::endl;
                jobj = json_object_object_get(jobj, key);
                json_parse(jobj);
                break;
                // case json_type_array: printf("type: json_type_array, ");
            case json_type_array:
                std::cout << "type: json_type_array, ";
                json_parse_array(jobj, key);
                break;
        }
    }
}
/**
 * @brief
 * @param jobj
 * @param key
 */
void wb_utils::json_parse_array(json_object *jobj, char *key) {
    // void json_parse(json_object *jobj); /*Forward Declaration*/
    enum json_type type;

    json_object *jarray = jobj; /*Simply get the array*/
    if (key) {
        jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
    }

    size_t arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
    // printf("Array Length: %d\n",arraylen);
    std::cout << "Array Length: " << arraylen << std::endl;
    json_object *jvalue;

    for (int i = 0; i < arraylen; i++) {
        jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
        type = json_object_get_type(jvalue);
        if (type == json_type_array) {
            json_parse_array(jvalue, nullptr);
        } else if (type != json_type_object) {
            // printf("value[%d]: ",i);
            std::cout << "value[" << i << "]: " << std::endl;
            json_print_value(jvalue);
        } else {
            json_parse(jvalue);
        }
    }
}
/**
 * @brief printing the value corresponding to boolean, double, integer and strings
 * @param jobj
 */
void wb_utils::json_print_value(json_object *jobj) {
    enum json_type type;
    type = json_object_get_type(jobj); /*Getting the type of the json object*/
    // printf("type: %d '%s'\n",type, json_type_to_name(type));
    std::cout << "type: " << type << "'" << json_type_to_name(type) << "'" << std::endl;
    switch (type) {
        // case json_type_null: printf("json_type_null\n");
        case json_type_null:
            std::cout << "json_type_null" << std::endl;
            // case json_type_boolean: printf("json_type_boolean\n");
        case json_type_boolean:
            std::cout << "json_type_boolean" << std::endl;
            // printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
            std::cout << "value: " << (json_object_get_boolean(jobj) ? "true" : "false") << std::endl;
            break;
            // case json_type_double: printf("json_type_double\n");
        case json_type_double:
            std::cout << "json_type_double" << std::endl;
            // printf("          value: %lf\n", json_object_get_double(jobj));
            std::cout << "          value: " << json_object_get_double(jobj) << std::endl;
            break;
            // case json_type_int: printf("json_type_int\n");
        case json_type_int:
            std::cout << "json_type_int" << std::endl;
            // printf("          value: %d\n", json_object_get_int(jobj));
            std::cout << "          value: " << json_object_get_int(jobj) << std::endl;
            break;
            // case json_type_string: printf("json_type_string\n");
        case json_type_string:
            std::cout << "json_type_string" << std::endl;
            // printf("          value: %s\n", json_object_get_string(jobj));
            std::cout << "          value: " << json_object_get_string(jobj) << std::endl;
            break;
        case json_type_object:
        case json_type_array:
            break;
    }
}
/**
 * @brief
 * @param fp
 * @param var
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::read_byte(FILE *fp, pixel_8U &var, const std::string &module, const std::string &id,
                         const std::string &error, Errors &errors) {
    size_t newLen = fread(&var, sizeof(pixel_8U), 1, fp);
    if (ferror(fp) != 0 || newLen != 1) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param buf
 * @param count
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::read_byte_buffer(FILE *fp, pixel_8U *buf, int count, const std::string &module, const std::string &id,
                                const std::string &error, Errors &errors) {
    size_t newLen = fread(buf, sizeof(pixel_8U), count, fp);
    if (ferror(fp) != 0 || newLen != count) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param var
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::read_double(FILE *fp, double &var, const std::string &module, const std::string &id,
                           const std::string &error, Errors &errors) {
    size_t newLen = fread(&var, sizeof(double), 1, fp);
    if (ferror(fp) != 0 || newLen != 1) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param buf
 * @param count
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::read_double_buffer(FILE *fp, double *buf, int count, const std::string &module, const std::string &id,
                                  const std::string &error, Errors &errors) {
    size_t newLen = fread(buf, sizeof(double), count, fp);
    if (ferror(fp) != 0 || newLen != count) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param var
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::read_float(FILE *fp, float &var, const std::string &module, const std::string &id,
                          const std::string &error, Errors &errors) {
    size_t newLen = fread(&var, sizeof(float), 1, fp);
    if (ferror(fp) != 0 || newLen != 1) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param buf
 * @param count
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::read_float_buffer(FILE *fp, float *buf, int count, const std::string &module, const std::string &id,
                                 const std::string &error, Errors &errors) {
    size_t newLen = fread(buf, sizeof(float), count, fp);
    if (ferror(fp) != 0 || newLen != count) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param var
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::read_int(FILE *fp, int &var, const std::string &module, const std::string &id, const std::string &error,
                        Errors &errors) {
    size_t newLen = fread(&var, sizeof(int), 1, fp);
    if (ferror(fp) != 0 || newLen != 1) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param buf
 * @param count
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::read_int_buffer(FILE *fp, int *buf, int count, const std::string &module, const std::string &id,
                               const std::string &error, Errors &errors) {
    size_t newLen = fread(buf, sizeof(int), count, fp);
    if (ferror(fp) != 0 || newLen != count) {
        errors.add(module, id, error);
    }
}
/**
 * @brief convert int to string
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
/**
 * @brief
 * @param text
 * @param prefix
 * @param suffix
 * @param pat
 * @param at_beginning
 * @param at_end
 * @return
 */
bool wb_utils::string_find(const std::string &text, std::string &prefix, std::string &suffix, const std::string &pat,
                           bool &at_beginning, bool &at_end) {
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
/**
 * @brief
 * @param
 * @param
 * @return
 */
bool wb_utils::string_in_list(const std::string find_string, const std::list<std::string> string_list) {
    return std::find(string_list.begin(), string_list.end(), find_string) != string_list.end();
}
/**
 * @brief
 * @param str
 * @return
 */
std::vector<std::string> wb_utils::string_split(const std::string &str) {
    std::vector<std::string> result;
    std::istringstream iss(str);
    for (std::string s; iss >> s;)
        result.push_back(s);
    return result;
}
/**
 * @brief
 * @param str
 * @param bvalue
 * @return
 */
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
/**
 * @brief
 * @param str
 * @param value
 * @return
 */
bool wb_utils::string_to_double(const std::string &str, double &value) {
    if (!is_numeric(str))
        return false;
    std::stringstream ss(str);
    if (ss >> value)
        return true;
    else
        return false;
}
/**
 * @brief
 * @param str
 * @param value
 * @return
 */
bool wb_utils::string_to_int(const std::string &str, int &value) {
    if (!is_numeric(str))
        return false;
    std::stringstream ss(str);
    if (ss >> value)
        return true;
    else
        return false;
}
/**
 * @brief
 * @return
 */
std::string wb_utils::timestamp() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%Y-%m-%d %T", timeinfo);
    return buffer;
}
/**
 * @brief
 * @param str
 * @param delims
 * @return
 */
std::vector<std::string> wb_utils::tokenize(std::string const &str, const std::string &delims) {
    size_t start;
    size_t end = 0;
    std::vector<std::string> out;

    while ((start = str.find_first_not_of(delims, end)) != std::string::npos) {
        end = str.find(delims, start);
        out.push_back(str.substr(start, end - start));
    }
    return out;
}
/**
 * @brief
 * @param fp
 * @param value
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::write_double(FILE *fp, double value, const std::string &module, const std::string &id,
                            const std::string &error, Errors &errors) {
    fwrite(&value, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param buf
 * @param count
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::write_double_buffer(FILE *fp, double *buf, int count, const std::string &module, const std::string &id,
                                   const std::string &error, Errors &errors) {
    fwrite(buf, sizeof(double), count, fp);
    if (ferror(fp) != 0) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param value
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::write_float(FILE *fp, float value, const std::string &module, const std::string &id,
                           const std::string &error, Errors &errors) {
    fwrite(&value, sizeof(float), 1, fp);
    if (ferror(fp) != 0) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param buf
 * @param count
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::write_float_buffer(FILE *fp, float *buf, int count, const std::string &module, const std::string &id,
                                  const std::string &error, Errors &errors) {
    fwrite(buf, sizeof(float), count, fp);
    if (ferror(fp) != 0) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param value
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::write_int(FILE *fp, int value, const std::string &module, const std::string &id,
                         const std::string &error, Errors &errors) {
    fwrite(&value, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add(module, id, error);
    }
}
/**
 * @brief
 * @param fp
 * @param buf
 * @param count
 * @param module
 * @param id
 * @param error
 * @param errors
 */
void wb_utils::write_int_buffer(FILE *fp, int *buf, int count, const std::string &module, const std::string &id,
                                const std::string &error, Errors &errors) {
    fwrite(buf, sizeof(int), count, fp);
    if (ferror(fp) != 0) {
        errors.add(module, id, error);
    }
}
