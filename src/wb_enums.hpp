//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_WB_ENUMS_HPP_
#define CV_WORKBENCH_SRC_WB_ENUMS_HPP_

enum Repository_type_enum {
  BERKELEY_DB, // separate file for each Cv_data_type_enum
  FILESYSTEM, // directory, filename
  INTERNET, // endpoint that produced binary data
  EXPERIMENT_STEP // output of experiment step
};

enum Cv_data_type_enum {
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
  REGION // complex area, shape properties
};

enum Cv_image_file_format_enum {
  BINARY, // includes header [int rows, int cols, int components]
  JPEG
};

#endif //CV_WORKBENCH_SRC_WB_ENUMS_HPP_
