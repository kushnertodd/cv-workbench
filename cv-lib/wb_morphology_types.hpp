//
// Created by kushn on 7/27/2022,
//

#ifndef SRC__CV_MORPHOLOGY_TYPES_HPP_
#define SRC__CV_MORPHOLOGY_TYPES_HPP_

#include <map>
#include <string>

class WB_morphology_types {
 public:
  enum class Convolution_type {
    NUMERIC,
    ERODE,
    DILATE,
    UNDEFINED
  };

  enum class Structuring_element_type {
    RECTANGLE,
    CROSS,
    ELLIPSE,
    UNDEFINED
  };

  static const std::string bin_string;
  static const std::string jpeg_string;
  static const std::string json_string;
  static const std::string log_string;
  static const std::string text_string;

  static const std::map<WB_morphology_types::Convolution_type, std::string> to_convolution_type_strings;
  static const std::map<WB_morphology_types::Structuring_element_type, std::string> to_structuring_element_type_strings;
  static const std::map<std::string, WB_morphology_types::Convolution_type> from_convolution_type_strings;
  static const std::map<std::string, WB_morphology_types::Structuring_element_type>
      from_structuring_element_type_strings;
  static std::string to_convolution_type_string(WB_morphology_types::Convolution_type convolution_type);
  static std::string to_structuring_element_type_string(WB_morphology_types::Structuring_element_type structuring_element_type);
  static WB_morphology_types::Convolution_type from_convolution_type_string(const std::string &text);
  static WB_morphology_types::Structuring_element_type from_structuring_element_type_string(const std::string &text);

};

#endif //SRC__CV_MORPHOLOGY_TYPES_HPP_
