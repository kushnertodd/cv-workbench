//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_ENUMS_HPP_
#define CV_WORKBENCH_SRC_WB_ENUMS_HPP_

#include <cfloat>
#include <map>
#include <string>

namespace cv_enums {

enum class WB_threshold_type {
  FIXED,
  PERCENTAGE
};
}

// built-in types
const int pixel_8U_MIN = 0;
const int pixel_8U_MAX = 255;
typedef unsigned char pixel_8U;

const int pixel_32S_MIN = -2147483648;
const int pixel_32S_MAX = 2147483647;
typedef int pixel_32S;

const float pixel_32F_MIN = -FLT_MAX;
const float pixel_32F_MAX = FLT_MAX;
typedef float pixel_32F;

typedef std::map<std::string, std::string> String_map;

#endif //CV_WORKBENCH_SRC_WB_ENUMS_HPP_
