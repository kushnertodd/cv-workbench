#include "wb_data_format.hpp"

/**
 * @brief
 */
const std::map<WB_data_format::Data_format, std::string> WB_data_format::to_exts = {
        {WB_data_format::Data_format::BINARY, "bin"},
        {WB_data_format::Data_format::JPEG, "jpg"},
        {WB_data_format::Data_format::JSON, "json"},
        {WB_data_format::Data_format::LOG, "log"},
        {WB_data_format::Data_format::TEXT, "txt"}};
/**
 * @brief
 */
const std::map<WB_data_format::Data_format, std::string> WB_data_format::to_strings = {
        {WB_data_format::Data_format::BINARY, "binary"},
        {WB_data_format::Data_format::JPEG, "jpeg"},
        {WB_data_format::Data_format::JSON, "json"},
        {WB_data_format::Data_format::LOG, "log"},
        {WB_data_format::Data_format::TEXT, "text"}};
/**
 * @brief
 */
const std::map<std::string, WB_data_format::Data_format> WB_data_format::from_exts = {
        {"bin", WB_data_format::Data_format::BINARY}, {"jpg", WB_data_format::Data_format::JPEG},
        {"jpeg", WB_data_format::Data_format::JPEG},  {"json", WB_data_format::Data_format::JSON},
        {"log", WB_data_format::Data_format::LOG},    {"txt", WB_data_format::Data_format::TEXT}};
/**
 * @brief
 */
const std::map<std::string, WB_data_format::Data_format> WB_data_format::from_strings = {
        {"binary", WB_data_format::Data_format::BINARY},
        {"jpeg", WB_data_format::Data_format::JPEG},
        {"json", WB_data_format::Data_format::JSON},
        {"log", WB_data_format::Data_format::LOG},
        {"text", WB_data_format::Data_format::TEXT}};
/**
 * @brief
 * @param data_format
 * @return
 */
std::string WB_data_format::to_ext(WB_data_format::Data_format data_format) {
    return WB_data_format::to_exts.at(data_format);
}
/**
 * @brief
 * @param data_format
 * @return
 */
std::string WB_data_format::to_string(WB_data_format::Data_format data_format) {
    return WB_data_format::to_strings.at(data_format);
}
/**
 * @brief
 * @param ext
 * @return
 */
WB_data_format::Data_format WB_data_format::from_ext(const std::string &ext) {
    if (WB_data_format::from_exts.count(ext))
        return WB_data_format::from_exts.at(ext);
    else
        return WB_data_format::Data_format::UNDEFINED;
}
/**
 * @brief
 * @param text
 * @return
 */
WB_data_format::Data_format WB_data_format::from_string(const std::string &text) {
    if (WB_data_format::from_strings.count(text))
        return WB_data_format::from_strings.at(text);
    else
        return WB_data_format::Data_format::UNDEFINED;
}
