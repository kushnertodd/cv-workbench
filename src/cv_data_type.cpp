//
// Created by kushn on 7/27/2022.
//

#include <string>
#include "cv_data_type.hpp"

const std::map<CV_data_type::Data_type, std::string> CV_data_type::to_strings =
    {
        {CV_data_type::Data_type::CONTOUR, "contour"},
        {CV_data_type::Data_type::CONVOLUTION_KERNEL, "convolution kernel"},
        {CV_data_type::Data_type::CONVOLVED_IMAGE, "convolved image"},
        {CV_data_type::Data_type::CORRELATED_IMAGE, "correlated image"},
        {CV_data_type::Data_type::IMAGE, "image"},
        {CV_data_type::Data_type::JSON_EXPERIMENT, "json experiment"},
        {CV_data_type::Data_type::JSON_EXPERIMENT_RESULTS, "json experiment results"},
        {CV_data_type::Data_type::HISTOGRAM, "histogram"},
        {CV_data_type::Data_type::HOUGH, "hough"},
        {CV_data_type::Data_type::PATTERN_FEATURE, "pattern feature"},
        {CV_data_type::Data_type::PATTERN_IMAGE, "pattern image"},
        {CV_data_type::Data_type::PYRAMID, "pyramid"},
        {CV_data_type::Data_type::QUADTREE, "quadtree"},
        {CV_data_type::Data_type::REGION, "region"},
    };
const std::map<std::string, CV_data_type::Data_type> CV_data_type::from_strings =
    {
        {"contour", CV_data_type::Data_type::CONTOUR},
        {"convolution kernel", CV_data_type::Data_type::CONVOLUTION_KERNEL},
        {"convolved image", CV_data_type::Data_type::CONVOLVED_IMAGE},
        {"correlated image", CV_data_type::Data_type::CORRELATED_IMAGE},
        {"image", CV_data_type::Data_type::IMAGE},
        {"json experiment", CV_data_type::Data_type::JSON_EXPERIMENT},
        {"json experiment results", CV_data_type::Data_type::JSON_EXPERIMENT_RESULTS},
        {"histogram", CV_data_type::Data_type::HISTOGRAM},
        {"hough", CV_data_type::Data_type::HOUGH},
        {"pattern feature", CV_data_type::Data_type::PATTERN_FEATURE},
        {"pattern image", CV_data_type::Data_type::PATTERN_IMAGE},
        {"pyramid", CV_data_type::Data_type::PYRAMID},
        {"quadtree", CV_data_type::Data_type::QUADTREE},
        {"region", CV_data_type::Data_type::REGION},

    };

std::string CV_data_type::to_string(CV_data_type::Data_type repository_type) {
  return CV_data_type::to_strings.at(repository_type);
}

CV_data_type::Data_type CV_data_type::from_string(const std::string &text) {
  if (CV_data_type::from_strings.count(text))
    return CV_data_type::from_strings.at(text);
  else
    return CV_data_type::Data_type::UNDEFINED;
}
