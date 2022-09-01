//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "errors.hpp"

/**
 * adds error to error list
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
 * checks for error and exits
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
 * checks if error seen
 * @return
 */
bool Errors::has_error() const {
  return error_ct != 0;
}

/**
 * convert to error list
 * @return
 */
std::string Errors::to_string() {
  std::ostringstream os;
  for (const std::string &error: error_list) {
    os << error << std::endl;
  }
  return os.str();
}
