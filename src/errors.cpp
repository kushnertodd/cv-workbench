//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "errors.hpp"

void Errors::add(std::string error) {
  error_ct++;
  error_list.push_back(error);
}

void Errors::add(std::string module, std::string id, std::string error) {
  error_ct++;
  std::string message;
  if (module == "" && id == "")
    message = error;
  else if (id == "")
    message = module + ": " + error;
  else
    message = module + " " + id + ": " + error;
  error_list.push_back(message);
}

void Errors::check_exit(std::string message){
  if (error_ct > 0) {
    std::cout << message << std::endl << to_string() << std::endl;
    exit(0);
  }
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
