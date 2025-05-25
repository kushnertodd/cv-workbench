#ifndef SRC__CV_CONVERT_TYPE_HPP_
#define SSRC__CV_CONVERT_TYPE_HPP_

#include <map>
#include <string>
/**
 * @brief
 */
class WB_convert_types {
public:
    enum class Convert_type { ABS, LOG, SQR, SQRT, UNDEFINED };
    static const std::map<WB_convert_types::Convert_type, std::string> to_strings;
    static const std::map<std::string, WB_convert_types::Convert_type> from_strings;
    static std::string to_string(WB_convert_types::Convert_type convert_type);
    static WB_convert_types::Convert_type from_string(const std::string &text);
};

#endif // SRC__CV_CONVERT_TYPE_HPP_
