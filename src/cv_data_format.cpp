//
// Created by kushn on 7/27/2022.
//

#include "cv_data_format.hpp"

std::string CV_data_format::data_format_enum_to_ext(CV_data_format::format type) {
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

std::string CV_data_format::data_format_enum_to_string(CV_data_format::format type) {
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

CV_data_format::format CV_data_format::ext_to_data_format_enum(const std::string &ext) {
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

CV_data_format::format CV_data_format::string_to_data_format_enum(const std::string &type) {
  if (type == "binary")
    return CV_data_format::format::BINARY;
  else if (type == "jpeg")
    return CV_data_format::format::JPEG;
  else if (type == "text")
    return CV_data_format::format::TEXT;
  else return CV_data_format::format::UNDEFINED_DATA_FORMAT;
}
