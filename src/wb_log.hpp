//
// Created by kushn on 7/30/2022.
//

#ifndef SRC__WB_LOG_HPP_
#define SRC__WB_LOG_HPP_
#include <string>
#include "errors.hpp"

class WB_log {
 public:
  static void log_to_file(std::string filename, std::string text, Errors &errors);

};

#endif //SRC__WB_LOG_HPP_
