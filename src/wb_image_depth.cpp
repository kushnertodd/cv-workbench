//
// Created by kushn on 7/27/2022.
//

#include "wb_image_depth.hpp"

const std::map<WB_image_depth::Image_depth, std::string> WB_image_depth::to_strings =
    {
        {WB_image_depth::Image_depth::CV_8U, "CV_8U"},
        {WB_image_depth::Image_depth::CV_32S, "CV_32S"},
        {WB_image_depth::Image_depth::CV_32F, "CV_32F"}
    };
const std::map<std::string, WB_image_depth::Image_depth> WB_image_depth::from_strings =
    {
        {"CV_8U", WB_image_depth::Image_depth::CV_8U},
        {"CV_32S", WB_image_depth::Image_depth::CV_32S},
        {"CV_32F", WB_image_depth::Image_depth::CV_32F}
    };

std::string WB_image_depth::to_string(WB_image_depth::Image_depth depth) {
  return WB_image_depth::to_strings.at(depth);
}
WB_image_depth::Image_depth WB_image_depth::from_string(const std::string &text) {
  if (WB_image_depth::from_strings.count(text))
    return WB_image_depth::from_strings.at(text);
  else
    return WB_image_depth::Image_depth::UNDEFINED;
}
