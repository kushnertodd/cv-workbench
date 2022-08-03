//
// Created by kushn on 7/27/2022.
//

#include "wb_morphology_types.hpp"

const std::map<WB_morphology_types::Convolution_type,
               std::string> WB_morphology_types::to_convolution_type_strings =
    {
        {WB_morphology_types::Convolution_type::NUMERIC, "numeric"},
        {WB_morphology_types::Convolution_type::ERODE, "erode"},
        {WB_morphology_types::Convolution_type::DILATE, "dilate"}
    };
const std::map<WB_morphology_types::Structuring_element_type, std::string>
    WB_morphology_types::to_structuring_element_type_strings =
    {
        {WB_morphology_types::Structuring_element_type::RECTANGLE, "rectangle"},
        {WB_morphology_types::Structuring_element_type::CROSS, "cross"},
        {WB_morphology_types::Structuring_element_type::ELLIPSE, "ellipse"}
    };
const std::map<std::string, WB_morphology_types::Convolution_type>
    WB_morphology_types::from_convolution_type_strings =
    {
        {"numeric", WB_morphology_types::Convolution_type::NUMERIC},
        {"erode", WB_morphology_types::Convolution_type::ERODE},
        {"dilate", WB_morphology_types::Convolution_type::DILATE}
    };
const std::map<std::string, WB_morphology_types::Structuring_element_type>
    WB_morphology_types::from_structuring_element_type_strings =
    {
        {"rectangle", WB_morphology_types::Structuring_element_type::RECTANGLE},
        {"cross", WB_morphology_types::Structuring_element_type::CROSS},
        {"ellipse", WB_morphology_types::Structuring_element_type::ELLIPSE}
    };

std::string WB_morphology_types::to_convolution_type_string(
    WB_morphology_types::Convolution_type convolution_type) {
  return WB_morphology_types::to_convolution_type_strings.at(convolution_type);
}

std::string WB_morphology_types::to_structuring_element_type_string(
    WB_morphology_types::Structuring_element_type structuring_element_type) {
  return WB_morphology_types::to_structuring_element_type_strings.at(structuring_element_type);
}

WB_morphology_types::Convolution_type WB_morphology_types::from_convolution_type_string(
    const std::string &text) {
  if (WB_morphology_types::from_convolution_type_strings.count(text))
    return WB_morphology_types::from_convolution_type_strings.at(text);
  else
    return WB_morphology_types::Convolution_type::UNDEFINED;
}

WB_morphology_types::Structuring_element_type
WB_morphology_types::from_structuring_element_type_string(const std::string &text) {
  if (WB_morphology_types::from_structuring_element_type_strings.count(text))
    return WB_morphology_types::from_structuring_element_type_strings.at(text);
  else
    return WB_morphology_types::Structuring_element_type::UNDEFINED;
}
