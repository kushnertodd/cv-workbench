//
// Created by kushn on 7/27/2022,
//

#ifndef SRC__CV_DATA_FORMAT_HPP_
#define SRC__CV_DATA_FORMAT_HPP_

#include <map>
#include <string>

class CV_data_format {
 public:
  enum class Data_format {
    BINARY,
    JPEG,
    JSON,
    LOG,
    TEXT,
    UNDEFINED
  };

  static const std::string bin_string;
  static const std::string jpeg_string;
  static const std::string json_string;
  static const std::string log_string;
  static const std::string text_string;

  static const std::map<CV_data_format::Data_format, std::string> to_exts;
  static const std::map<CV_data_format::Data_format, std::string> to_strings;
  static const std::map<std::string, CV_data_format::Data_format> from_exts;
  static const std::map<std::string, CV_data_format::Data_format> from_strings;
  static std::string to_ext(CV_data_format::Data_format data_format);
  static std::string to_string(CV_data_format::Data_format data_format);
  static CV_data_format::Data_format from_ext(const std::string &ext);
  static CV_data_format::Data_format from_string(const std::string &type);

};

#endif //SRC__CV_DATA_FORMAT_HPP_
