//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_ENUMS_HPP_
#define CV_WORKBENCH_SRC_WB_ENUMS_HPP_

#include <map>
#include <string>

namespace cv_enums {

enum class WB_threshold_type {
  FIXED,
  PERCENTAGE
};
}

// built-in types
// 0..255
typedef unsigned char pixel_8U;
const int pixel_8U_MIN = 0;
const int pixel_8U_MAX = 255;
// unsupported -128..127
typedef char pixel_8S;
// unsupported 0..65535
typedef unsigned short pixel_16U;
// unsupported -32768..32767
typedef short pixel_16S;
// -2147483648..2147483647
typedef int pixel_32S;
// -FLT_MAX..FLT_MAX
typedef float pixel_32F;
// unsupported -DBL_MAX..DBL_MAX
typedef double pixel_64F;
// unsupported -- CV_16F pretty much doesn't exist in C++
typedef float pixel_16F;

typedef std::map<std::string, std::string> String_map;

#endif //CV_WORKBENCH_SRC_WB_ENUMS_HPP_
