//
// Created by kushn on 7/27/2022.
//

#ifndef SRC__CV_DATA_TYPE_HPP_
#define SRC__CV_DATA_TYPE_HPP_

class CV_data_type {
 public:
  enum class type {
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
  static std::string data_type_enum_to_string(CV_data_type::type type);
  static CV_data_type::type string_to_data_type_enum(const std::string &type);
  };

#endif //SRC__CV_DATA_TYPE_HPP_
