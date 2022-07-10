#include <string>
#include <vector>
#include <iostream>
#include "file_utils.hpp"

//



int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "usage: " << argv[0] << " data-file" << std::endl;
    exit(0);
  }
  std::string data_file = argv[1];
  std::string data = file_utils::read_file(data_file);
  std::vector<std::string> tokens = file_utils::string_split(data);
  for (std::string token: tokens) {
    std::cout << "'" << token << "'" << std::endl;
  }
}
