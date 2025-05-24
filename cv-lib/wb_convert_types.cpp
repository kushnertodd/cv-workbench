#include "wb_convert_types.hpp"

/**
 * @brief
 */
const std::map<WB_convert_types::Convert_type, std::string> WB_convert_types::to_strings = {
        {WB_convert_types::Convert_type::ABS, "abs"}, {WB_convert_types::Convert_type::LOG, "log"}};
/**
 * @brief
 */
const std::map<std::string, WB_convert_types::Convert_type> WB_convert_types::from_strings = {
        {"abs", WB_convert_types::Convert_type::ABS}, {"log", WB_convert_types::Convert_type::LOG}};
/**
 * @brief
 * @param convert_type
 * @return
 */
std::string WB_convert_types::to_string(WB_convert_types::Convert_type convert_type) {
    return WB_convert_types::to_strings.at(convert_type);
}
/**
 * @brief
 * @param text
 * @return
 */
WB_convert_types::Convert_type WB_convert_types::from_string(const std::string &text) {
    if (WB_convert_types::from_strings.count(text))
        return WB_convert_types::from_strings.at(text);
    else
        return WB_convert_types::Convert_type::UNDEFINED;
}
