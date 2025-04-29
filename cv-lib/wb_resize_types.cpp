#include "wb_resize_types.hpp"

/**
 * @brief
 */
const std::map<WB_resize_types::Resize_type, std::string> WB_resize_types::to_strings = {
        {WB_resize_types::Resize_type::AVERAGE, "average"},
        {WB_resize_types::Resize_type::MAX, "max"},
        {WB_resize_types::Resize_type::MIN, "min"},
        {WB_resize_types::Resize_type::SUM, "sum"}};
/**
 * @brief
 */
const std::map<std::string, WB_resize_types::Resize_type> WB_resize_types::from_strings = {
        {"average", WB_resize_types::Resize_type::AVERAGE},
        {"max", WB_resize_types::Resize_type::MAX},
        {"min", WB_resize_types::Resize_type::MIN},
        {"sum", WB_resize_types::Resize_type::SUM}};
/**
 * @brief
 * @param resize_type
 * @return
 */
std::string WB_resize_types::to_string(WB_resize_types::Resize_type resize_type) {
    return WB_resize_types::to_strings.at(resize_type);
}
/**
 * @brief
 * @param text
 * @return
 */
WB_resize_types::Resize_type WB_resize_types::from_string(const std::string &text) {
    if (WB_resize_types::from_strings.count(text))
        return WB_resize_types::from_strings.at(text);
    else
        return WB_resize_types::Resize_type::UNDEFINED;
}
