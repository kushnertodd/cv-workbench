//
// Created by kushn on 5/21/2022.
//

#ifndef CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_
#define CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_

#include <vector>

//

namespace file_utils {

long file_size(std::ifstream &in);
std::string read_file(std::string filename);
bool read_int(FILE *fp, int &var);
std::vector<std::string> string_split(const std::string &str);
}

#endif //CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_
