//
// Created by kushn on 7/27/2022.
//

#ifndef SRC__CV_DATA_FORMAT_HPP_
#define SRC__CV_DATA_FORMAT_HPP_

#include <string>

class CV_data_format {
public:
  enum class format {
    BINARY,
    JPEG, // CV_data_type::IMAGE only
    JSON,
    LOG,
    TEXT,
    UNDEFINED_DATA_FORMAT
  };
  static std::string data_format_enum_to_ext(CV_data_format::format type);
  static std::string data_format_enum_to_string(CV_data_format::format type);
  static CV_data_format::format ext_to_data_format_enum(const std::string &ext);
  static CV_data_format::format string_to_data_format_enum(const std::string &type);

};

#endif //SRC__CV_DATA_FORMAT_HPP_
