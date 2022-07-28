//
// Created by kushn on 7/27/2022.
//

#include "cv_image_depth.hpp"

const std::map<CV_image_depth::Image_depth, std::string> CV_image_depth::to_strings =
    {
        {CV_image_depth::Image_depth::CV_8U, "CV_8U"},
        {CV_image_depth::Image_depth::CV_32S, "CV_32S"},
        {CV_image_depth::Image_depth::CV_32F, "CV_32F"}
    };
const std::map<std::string, CV_image_depth::Image_depth> CV_image_depth::from_strings =
    {
        {"CV_8U", CV_image_depth::Image_depth::CV_8U},
        {"CV_32S", CV_image_depth::Image_depth::CV_32S},
        {"CV_32F", CV_image_depth::Image_depth::CV_32F}
    };

std::string CV_image_depth::to_string(CV_image_depth::Image_depth depth) {
  return CV_image_depth::to_strings.at(depth);
}
CV_image_depth::Image_depth CV_image_depth::from_string(const std::string &text) {
  if (CV_image_depth::from_strings.count(text))
    return CV_image_depth::from_strings.at(text);
  else
    return CV_image_depth::Image_depth::UNDEFINED;
}
