#include <fstream>
#include <string>
#include <cerrno>
#include <vector>
#include <sstream>
#include "file_utils.hpp"

using namespace std;

/**
 * returns size of file in bytes
 * @param fp file pointer
 * @return long byte count
 */
long File_utils::file_size(ifstream &in) {
  // Get the number of bytes
  in.seekg(0, ios::end);
  return in.tellg();
}

/**
 * reads all characters in filename and returns length in file_bytes
 * (m)allocates buffer and fills with file contents
 * be sure to free()
 * @return file contents
 * @throws errno on open error
 */
string File_utils::read_file(string filename) {
  ifstream in(filename, ios::in | ios::binary);
  if (in) {
    string contents;
    contents.resize(file_size(in));
    in.seekg(0, ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw (errno);
}

vector<string> File_utils::string_split(const string& str) {
  vector<string> result;
  istringstream iss(str);
  for (string s; iss >> s; )
    result.push_back(s);
  return result;
}
