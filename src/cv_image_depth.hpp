//
// Created by kushn on 7/27/2022.
//

#ifndef SRC__CV_IMAGE_DEPTH_HPP_
#define SRC__CV_IMAGE_DEPTH_HPP_

#include <string>

class CV_image_depth {
 public:
  enum class depth {
    CV_8U,
    CV_32S,
    CV_32F,
    //CV_8S,
    //CV_16U,
    //CV_16S,
    //CV_64F,
    //CV_16F,
    UNDEFINED_IMAGE_DEPTH
  };

  static  std::string image_depth_enum_to_string(CV_image_depth::depth depth);
  static depth string_to_image_depth_enum(const std::string &depth);
};

#endif //SRC__CV_IMAGE_DEPTH_HPP_
