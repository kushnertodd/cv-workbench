//
// Created by kushn on 7/27/2022.
//

#include "cv_image_depth.hpp"

std::string CV_image_depth::image_depth_enum_to_string(CV_image_depth::depth depth) {
  switch (depth) {
    case CV_image_depth::depth::CV_8U:
      return "CV_image_depth::depth::CV_8U";
//    case CV_image_depth::depth::CV_8S:
//      return "CV_8S";
//    case CV_image_depth::depth::CV_16U:
//      return "CV_16U";
//    case CV_image_depth::depth::CV_16S:
//      return "CV_16S";
//    case CV_image_depth::depth::CV_32S:
//      return "CV_image_depth::depth::CV_32S";
    case CV_image_depth::depth::CV_32F:
      return "CV_image_depth::depth::CV_32F";
//    case CV_image_depth::depth::CV_64F:
//      return "CV_64F";
//    case CV_image_depth::depth::CV_16F:
//      return "CV_16F";
    default:
      return "unknown image depth";
  }
}

CV_image_depth::depth CV_image_depth::string_to_image_depth_enum(const std::string &depth) {
  if (depth == "CV_8U") return CV_image_depth::depth::CV_8U;
//  else if (depth == "CV_8S") return cv_enums::CV_8S;
//  else if (depth == "CV_16U") return cv_enums::CV_16U;
//  else if (depth == "CV_16S") return cv_enums::CV_16S;
  else if (depth == "CV_32S") return CV_image_depth::depth::CV_32S;
  else if (depth == "CV_32F") return CV_image_depth::depth::CV_32F;
//  else if (depth == "CV_64F") return cv_enums::CV_64F;
//  else if (depth == "CV_16F") return cv_enums::CV_16F;
  else return CV_image_depth::depth::UNDEFINED_IMAGE_DEPTH;
}
