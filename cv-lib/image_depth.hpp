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

enum Image_colors {
    RGB_RED = 0, // Offset of Red in an RGB scanline element
    RGB_GREEN = 1, // Offset of Green
    RGB_BLUE = 2 // Offset of Blue
};

enum Image_components {
    COMPONENTS_GRAYSCALE = 1,
    COMPONENTS_RGB = 3
};

class WB_image_depth {
    static const std::map<Image_depth, std::string> to_strings;
    static const std::map<std::string, Image_depth> from_strings;

public:
    static std::string to_string(Image_depth depth);

    static Image_depth from_string(const std::string &text);
};

#endif //SRC__CV_IMAGE_DEPTH_HPP_
