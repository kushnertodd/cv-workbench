//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_ENUMS_HPP_
#define CV_WORKBENCH_SRC_WB_ENUMS_HPP_

#include <map>
#include <string>

using namespace std;

namespace cv_enums {

enum CV_data_type {
  // maybe BINARY_IMAGE for morphological operations
  CONTOUR, // boundary polygon
  CONVOLUTION_KERNEL,
  CONVOLVED_IMAGE, // CV_32F, maybe e.g. FLOAT_IMAGE instead
  CORRELATED_IMAGE, // probably CV_32S/F, image correlated with patter
  IMAGE, // pixels, size, depth is CV_8U, CV_32S, or CV_32F images initially
  JSON_EXPERIMENT, // experiment definition
  JSON_EXPERIMENT_RESULTS, // result of experiment run
  HISTOGRAM, // CV_8U images initially
  HOUGH, // accumulation space + found features
  PATTERN_FEATURE, // e.g. lines, circles for matching
  PATTERN_IMAGE, // for exact sub-image matching
  PYRAMID, // Burt structure
  QUADTREE, // Samet structure
  REGION, // complex area, shape properties
  UNDEFINED_DATA_TYPE
};

enum CV_image_file_format {
  BINARY, // includes header [int rows, int cols, int components]
  JPEG,
  UNDEFINED_FILE_FORMAT
};

enum CV_image_depth {
  CV_8U,
  CV_8S,
  CV_16U,
  CV_16S,
  CV_32S,
  CV_32F,
  CV_64F,
  CV_16F,
  UNDEFINED_IMAGE_DEPTH
};

enum CV_repository_type {
  BERKELEY_DB, // separate file for each CV_data_type
  FILESYSTEM, // directory, filename
  INTERNET, // endpoint that produced binary data
  EXPERIMENT_STEP, // output of experiment step
  UNDEFINED_REPOSITORY_TYPE
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

typedef map<string, string> String_map;

#endif //CV_WORKBENCH_SRC_WB_ENUMS_HPP_
