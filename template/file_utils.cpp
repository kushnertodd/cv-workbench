#include <fstream>
#include <string>
#include <cerrno>
#include "file_utils.hpp"

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
std::string file_utils::read_file(std::string filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    std::string contents;
    contents.resize(file_size(in));
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw (errno);
}
