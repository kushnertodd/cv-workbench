#ifndef SRC__CV_DATA_TYPE_HPP_
#define SRC__CV_DATA_TYPE_HPP_

#include <map>
#include <string>
/**
 * @brief
 */
class WB_data_type {

public:
    enum class Data_type {
        // maybe BINARY_IMAGE for morphological operations
        CONTOUR, // boundary polygon
        CONVOLUTION_KERNEL,
        CONVOLVED_IMAGE, // CV_32F, maybe e.g. FLOAT_IMAGE instead
        CORRELATED_IMAGE, // probably CV_32S/F, image correlated with patter
        DATA, // raw binary or text lines
        IMAGE, // pixels, size, depth is CV_8U, CV_32S, or CV_32F images initially
        JSON_EXPERIMENT, // experiment definition
        JSON_EXPERIMENT_RESULTS, // result of experiment run
        HISTOGRAM, // CV_8U images initially
        HOUGH, // accumulation space + found features
        HOUGH_PEAKS, // hough accumulator peaks
        PATTERN_FEATURE, // e.g. lines, circles for matching
        PATTERN_IMAGE, // for exact sub-image matching
        PYRAMID, // Burt structure
        QUADTREE, // Samet structure
        REGION, // complex area, shape properties
        UNDEFINED
    };
    static const std::map<WB_data_type::Data_type, std::string> to_strings;
    static const std::map<std::string, WB_data_type::Data_type> from_strings;
    static std::string to_string(WB_data_type::Data_type repository_type);
    static WB_data_type::Data_type from_string(const std::string &text);
};

#endif // SRC__CV_DATA_TYPE_HPP_
