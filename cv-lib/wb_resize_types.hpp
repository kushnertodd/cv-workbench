//
// Created by kushn on 7/27/2022.
//

#ifndef SRC__CV_RESIZE_TYPE_HPP_
#define SSRC__CV_RESIZE_TYPE_HPP_

#include <map>
#include <string>

class WB_resize_types {
public:
    enum class Resize_type { AVERAGE, MAX, MIN, SUM, UNDEFINED };
    static const std::map<WB_resize_types::Resize_type, std::string> to_strings;
    static const std::map<std::string, WB_resize_types::Resize_type> from_strings;
    static std::string to_string(WB_resize_types::Resize_type resize_type);
    static WB_resize_types::Resize_type from_string(const std::string &text);
};

#endif // SRC__CV_RESIZE_TYPE_HPP_
