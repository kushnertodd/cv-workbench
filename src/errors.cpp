//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "errors.hpp"

/*
void Errors::add(const std::string &error) {
  error_ct++;
  error_list.push_back(error);
}
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

void Errors::check_exit(const std::string &message) {
  if (error_ct > 0) {
    std::cerr
    //<< message << std::endl
    << to_string() << std::endl;
    exit(1);
  }
}

void Errors::merge(Errors &errors) {
  error_ct += errors.error_ct;
  error_list.insert(error_list.end(), errors.error_list.begin(), errors.error_list.end());
}

std::string Errors::to_string() {
  std::ostringstream os;
  for (const std::string &error: error_list) {
    os << error << std::endl;
  }
  return os.str();
}
