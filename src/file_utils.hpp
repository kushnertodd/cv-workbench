//
// Created by kushn on 5/21/2022.
//

#ifndef CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_
#define CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_

class file_utils_cpp {
 public:
  static long file_size(std::ifstream &in);
  static std::string read_file(std::string filename);
};

#endif //CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_