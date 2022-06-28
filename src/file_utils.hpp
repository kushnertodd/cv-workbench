//
// Created by kushn on 5/21/2022.
//

#ifndef CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_
#define CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_

#include <vector>

using namespace std;

class File_utils {
 public:
  static long file_size(std::ifstream &in);
  static std::string read_file(std::string filename);
  static bool read_int(FILE *fp, int &var);
  static vector<string> string_split(const string &str);
};

#endif //CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_
