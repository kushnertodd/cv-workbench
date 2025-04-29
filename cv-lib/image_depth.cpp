#include "image_depth.hpp"
#include <string>

const std::map<Image_depth, std::string> WB_image_depth::to_strings = {
        {Image_depth::CV_8U, "CV_8U"}, {Image_depth::CV_32S, "CV_32S"}, {Image_depth::CV_32F, "CV_32F"}};
const std::map<std::string, Image_depth> WB_image_depth::from_strings = {
        {"CV_8U", Image_depth::CV_8U}, {"CV_32S", Image_depth::CV_32S}, {"CV_32F", Image_depth::CV_32F}};
std::string WB_image_depth::to_string(Image_depth depth) { return WB_image_depth::to_strings.at(depth); }
Image_depth WB_image_depth::from_string(const std::string &text) {
    if (WB_image_depth::from_strings.count(text))
        return WB_image_depth::from_strings.at(text);
    else
        return Image_depth::UNDEFINED;
}
