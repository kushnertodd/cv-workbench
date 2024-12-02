//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_UTILS_HPP_
#define CV_WORKBENCH_SRC_WB_UTILS_HPP_

#include <map>
#include <string>
#include <vector>
#include <json-c/json.h>
#include "wb_data_format.hpp"
#include "wb_data_type.hpp"
#include "wb_image_depth.hpp"
#include "wb_repository_type.hpp"
#include "errors.hpp"
#include "wb_defs.hpp"

namespace wb_utils {

char ascii_to_char(int n);
std::string char_to_string(char c);
pixel_32F cv_32S_to_cv_32F(pixel_32S value);
pixel_32S cv_32F_to_cv_32S(pixel_32F value);
pixel_32S cv_32F_to_cv_32S_round(pixel_32F value);
float double_to_float(double value);
int double_to_int(double value);
int double_to_int_round(double value);
std::string double_to_string(double x, int width = -1);
void error_exit(const std::string &message);
int float_to_int(float value);
int float_to_int_round(float value);
bool hex_string_to_int(const std::string &text, unsigned long long &value);
std::string indent(int n);
float int_to_float(int value);
std::string int_to_hex_string(unsigned long long i, int width = -1);
std::string int_to_string(int i, int width = -1);
bool is_numeric(std::string number);
void json_parse(json_object *jobj);
void json_parse_array(json_object *jobj, char *key);
void json_print_value(json_object *jobj);
void read_byte(FILE *fp,
               pixel_8U &var,
               const std::string &module,
               const std::string &id,
               const std::string &error,
               Errors &errors);
void read_byte_buffer(FILE *fp,
                      pixel_8U *buf,
                      int count,
                      const std::string &module,
                      const std::string &id,
                      const std::string &error,
                      Errors &errors);
void read_double(FILE *fp,
                 double &var,
                 const std::string &module,
                 const std::string &id,
                 const std::string &error,
                 Errors &errors);
void read_double_buffer(FILE *fp,
                        double *buf,
                        int count,
                        const std::string &module,
                        const std::string &id,
                        const std::string &error,
                        Errors &errors);
void read_float(FILE *fp,
                float &var,
                const std::string &module,
                const std::string &id,
                const std::string &error,
                Errors &errors);
void read_float_buffer(FILE *fp,
                       float *buf,
                       int count,
                       const std::string &module,
                       const std::string &id,
                       const std::string &error,
                       Errors &errors);
void read_int(FILE *fp,
              int &var,
              const std::string &module,
              const std::string &id,
              const std::string &error,
              Errors &errors);
void read_int_buffer(FILE *fp,
                     int *buf,
                     int count,
                     const std::string &module,
                     const std::string &id,
                     const std::string &error,
                     Errors &errors);
std::string real_to_string(double i, int width = -1);
bool string_find(const std::string &text,
                 std::string &prefix,
                 std::string &suffix,
                 const std::string &pat,
                 bool &at_beginning,
                 bool &at_end);
std::vector<std::string> string_split(const std::string &str);
bool string_to_bool(const std::string &str, bool &bvalue);
bool string_to_double(const std::string &text, double &value);
bool string_to_int(const std::string &str, int &value);
std::string timestamp();
std::vector<std::string> tokenize(std::string const &str, const std::string& delims);
void write_double(FILE *fp,
                  double value,
                  const std::string &module,
                  const std::string &id,
                  const std::string &error,
                  Errors &errors);
void write_double_buffer(FILE *fp,
                         double *buf,
                         int count,
                         const std::string &module,
                         const std::string &id,
                         const std::string &error,
                         Errors &errors);
void write_float(FILE *fp,
                 float value,
                 const std::string &module,
                 const std::string &id,
                 const std::string &error,
                 Errors &errors);
void write_float_buffer(FILE *fp,
                        float *buf,
                        int count,
                        const std::string &module,
                        const std::string &id,
                        const std::string &error,
                        Errors &errors);
void write_int(FILE *fp,
               int value,
               const std::string &module,
               const std::string &id,
               const std::string &error,
               Errors &errors);
void write_int_buffer(FILE *fp,
                      int *buf,
                      int count,
                      const std::string &module,
                      const std::string &id,
                      const std::string &error,
                      Errors &errors);

}

#endif //CV_WORKBENCH_SRC_WB_UTILS_HPP_
