//
// Created by kushn on 7/27/2022.
//

#include <string>
#include "cv_data_type.hpp"

std::string CV_data_type::data_type_enum_to_string(CV_data_type::type type) {
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

CV_data_type::type CV_data_type::string_to_data_type_enum(const std::string &type) {
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
