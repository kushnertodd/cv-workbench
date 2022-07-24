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
long file_utils::file_size(std::ifstream &in) {
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
std::string file_utils::read_file(const std::string &filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    std::string contents;
    contents.resize(file_size(in));
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw (filename + ": " + strerror(errno));
}

bool file_utils::read_double(FILE *fp, double &var) {
  size_t newLen = fread(&var, sizeof(double), 1, fp);
  return (ferror(fp) == 0 && newLen == 1);
}

bool file_utils::read_float(FILE *fp, float &var) {
  size_t newLen = fread(&var, sizeof(float), 1, fp);
  return (ferror(fp) == 0 && newLen == 1);
}

bool file_utils::read_int(FILE *fp, int &var) {
  size_t newLen = fread(&var, sizeof(int), 1, fp);
  return (ferror(fp) == 0 && newLen == 1);
}

std::vector<std::string> file_utils::string_split(const std::string &str) {
  std::vector<std::string> result;
  std::istringstream iss(str);
  for (std::string s; iss >> s;)
    result.push_back(s);
  return result;
}
