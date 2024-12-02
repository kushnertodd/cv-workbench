//
// Created by kushn on 7/27/2022.
//

#ifndef SRC__CV_IMAGE_DEPTH_HPP_
#define SRC__CV_IMAGE_DEPTH_HPP_

#include <map>
#include <string>

class WB_image_depth {
 public:
  enum class Image_depth {
    CV_8U,
    CV_32S,
    CV_32F,
    //CV_8S,
    //CV_16U,
    //CV_16S,
    //CV_64F,
    //CV_16F,
    UNDEFINED
  };

  static const std::map<WB_image_depth::Image_depth, std::string> to_strings;
  static const std::map<std::string, WB_image_depth::Image_depth> from_strings;
  static std::string to_string(WB_image_depth::Image_depth depth);
  static WB_image_depth::Image_depth from_string(const std::string &text);
};

#endif //SRC__CV_IMAGE_DEPTH_HPP_
