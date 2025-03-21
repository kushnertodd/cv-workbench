//
// Created by kushn on 7/27/2022.
//

#ifndef SRC__CV_IMAGE_DEPTH_HPP_
#define SRC__CV_IMAGE_DEPTH_HPP_

#include <map>
#include <string>

enum class Image_depth {
    CV_8U,
    CV_32S,
    CV_32F,
    UNDEFINED
};

class WB_image_depth {
public:
    static const std::map<Image_depth, std::string> to_strings;
    static const std::map<std::string, Image_depth> from_strings;

    static std::string to_string(Image_depth depth);

    static Image_depth from_string(const std::string &text);
};

#endif //SRC__CV_IMAGE_DEPTH_HPP_
