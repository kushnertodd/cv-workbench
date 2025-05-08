#ifndef SRC__WB_LOG_HPP_
#define SRC__WB_LOG_HPP_
#include <string>
#include "errors.hpp"

/**
 * @brief
 */
class WB_log_entry {
public:
    std::string item{};
    std::string value{};

    WB_log_entry(std::string m_item, std::string m_value);
};
/**
 * @brief
 */
class WB_log {
public:
    static void log_to_file(const std::string &filename, const std::string &text, Errors &errors);
};

#endif // SRC__WB_LOG_HPP_
