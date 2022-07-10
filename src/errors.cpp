//
// Created by kushn on 6/11/2022.
//

#include <sstream>
#include "errors.hpp"

void Errors::add(std::string error) {
  error_ct++;
  error_list.push_back(error);
}

void Errors::merge(Errors &errors) {
  error_ct += errors.error_ct;
  error_list.insert(error_list.end(), errors.error_list.begin(), errors.error_list.end());
}

std::string Errors::to_string() {
  std::ostringstream os;
  for (std::string error: error_list) {
    os << error << std::endl;
  }
  return os.str();
}
