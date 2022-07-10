#include <fstream>
#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <vector>
#include <sstream>
#include "file_utils.hpp"

//

/**
 * returns size of file in bytes
 * @param fp file pointer
 * @return long byte count
 */
long File_utils::file_size(std::ifstream &in) {
  // Get the number of bytes
  in.seekg(0, std::ios::end);
  return in.tellg();
}

/**
 * reads all characters in filename and returns length in file_bytes
 * (m)allocates buffer and fills with file contents
 * be sure to free()
 * @return file contents
 * @throws errno on open error
 */
std::string File_utils::read_file(std::string filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    std::string contents;
    contents.resize(file_size(in));
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  std::cout << filename << ": " << strerror(errno) << std::endl;
  throw (errno);
}

bool File_utils::read_int(FILE *fp, int &var) {
  int newLen = fread(&var, sizeof(int), 1, fp);
  return (ferror(fp) == 0 && newLen == 1);
}

std::vector<std::string> File_utils::string_split(const std::string& str) {
  std::vector<std::string> result;
  std::istringstream iss(str);
  for (std::string s; iss >> s; )
    result.push_back(s);
  return result;
}
