#include "errors.hpp"
#include <iostream>
#include <sstream>

/**
 * @brief
 * @param module
 * @param id
 * @param error
 */
void Errors::add(const std::string &module, const std::string &id, const std::string &error) {
    error_ct++;
    std::string message;
    if (module.empty() && id.empty())
        message = error;
    else if (id.empty())
        message = module + ": " + error;
    else
        message = module + " " + id + ": " + error;
    error_list.push_back(message);
}
/**
 * @brief
 * @param message
 */
void Errors::check_exit(const std::string &message) {
    if (error_ct > 0) {
        if (!message.empty())
            std::cerr << message << std::endl;
        std::cerr << to_string() << std::endl;
        exit(1);
    }
}
/**
 * @brief
 * @return
 */
bool Errors::has_error() const { return error_ct != 0; }
/**
 * @brief string list of errors
 * @return
 */
std::string Errors::to_string() {
    std::ostringstream os;
    for (const std::string &error: error_list) {
        os << error << std::endl;
    }
    return os.str();
}
