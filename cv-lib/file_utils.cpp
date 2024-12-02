#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
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

FILE *file_utils::open_file_read(const std::string &path, Errors &errors) {
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == nullptr) {
    errors.add("file_utils::open_file", "", "cannot open file " + path + " for reading: " + strerror(errno));
  }
  return fp;
}

std::ifstream file_utils::open_file_read_text(const std::string &path, Errors &errors) {
  std::ifstream ifs(path, std::ifstream::in);
  if (!ifs) {
    errors.add("file_utils::open_file", "", "cannot open file " + path + " for reading: " + strerror(errno));
  }
  return ifs;
}

FILE *file_utils::open_file_write(const std::string &path, Errors &errors) {
  FILE *fp = fopen(path.c_str(), "w");
  if (fp == nullptr) {
    errors.add("file_utils::open_file", "", "cannot open file " + path + " for writing: " + strerror(errno));
  }
  return fp;
}

std::ofstream file_utils::open_file_write_text(const std::string &path, Errors &errors) {
  std::ofstream ofs(path, std::ofstream::out);
  if (!ofs) {
    errors.add("file_utils::open_file", "", "cannot open file " + path + " for reading: " + strerror(errno));
  }
  return ofs;
}

/**
 * reads all characters in filename and returns length in file_bytes
 * (m)allocates buffer and fills with file contents
 * be sure to free()
 * @return file contents
 * @throws errno on open error
 */
bool file_utils::read_file(const std::string &filename, std::string &contents) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    contents.resize(file_size(in));
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return true;
  }
  return false;
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

