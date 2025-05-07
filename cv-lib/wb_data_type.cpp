#include "wb_data_type.hpp"

/**
 * @brief
 */
const std::map<WB_data_type::Data_type, std::string> WB_data_type::to_strings = {
        {WB_data_type::Data_type::CONTOUR, "contour"},
        {WB_data_type::Data_type::CONVOLUTION_KERNEL, "convolution kernel"},
        {WB_data_type::Data_type::CONVOLVED_IMAGE, "convolved image"},
        {WB_data_type::Data_type::CORRELATED_IMAGE, "correlated image"},
        {WB_data_type::Data_type::DATA, "data"},
        {WB_data_type::Data_type::IMAGE, "image"},
        {WB_data_type::Data_type::JSON_EXPERIMENT, "json experiment"},
        {WB_data_type::Data_type::JSON_EXPERIMENT_RESULTS, "json experiment results"},
        {WB_data_type::Data_type::HISTOGRAM, "histogram"},
        {WB_data_type::Data_type::HOUGH, "hough"},
        {WB_data_type::Data_type::HOUGH_PEAKS, "hough peaks"},
        {WB_data_type::Data_type::PATTERN_FEATURE, "pattern feature"},
        {WB_data_type::Data_type::PATTERN_IMAGE, "pattern image"},
        {WB_data_type::Data_type::PYRAMID, "pyramid"},
        {WB_data_type::Data_type::QUADTREE, "quadtree"},
        {WB_data_type::Data_type::REGION, "region"},
};
/**
 * @brief
 */
const std::map<std::string, WB_data_type::Data_type> WB_data_type::from_strings = {
        {"contour", WB_data_type::Data_type::CONTOUR},
        {"convolution kernel", WB_data_type::Data_type::CONVOLUTION_KERNEL},
        {"convolved image", WB_data_type::Data_type::CONVOLVED_IMAGE},
        {"correlated image", WB_data_type::Data_type::CORRELATED_IMAGE},
        {"data", WB_data_type::Data_type::DATA},
        {"image", WB_data_type::Data_type::IMAGE},
        {"json experiment", WB_data_type::Data_type::JSON_EXPERIMENT},
        {"json experiment results", WB_data_type::Data_type::JSON_EXPERIMENT_RESULTS},
        {"histogram", WB_data_type::Data_type::HISTOGRAM},
        {"hough", WB_data_type::Data_type::HOUGH},
        {"hough peaks", WB_data_type::Data_type::HOUGH_PEAKS},
        {"pattern feature", WB_data_type::Data_type::PATTERN_FEATURE},
        {"pattern image", WB_data_type::Data_type::PATTERN_IMAGE},
        {"pyramid", WB_data_type::Data_type::PYRAMID},
        {"quadtree", WB_data_type::Data_type::QUADTREE},
        {"region", WB_data_type::Data_type::REGION},

};
/**
 * @brief
 * @param repository_type
 * @return
 */
std::string WB_data_type::to_string(WB_data_type::Data_type repository_type) {
    return WB_data_type::to_strings.at(repository_type);
}
/**
 * @brief
 * @param text
 * @return
 */
WB_data_type::Data_type WB_data_type::from_string(const std::string &text) {
    if (WB_data_type::from_strings.count(text))
        return WB_data_type::from_strings.at(text);
    else
        return WB_data_type::Data_type::UNDEFINED;
}
