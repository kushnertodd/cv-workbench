#include <string>
#include <vector>
#include <iostream>
#include "file_utils.hpp"

using namespace std;



int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "usage: " << argv[0] << " data-file" << endl;
    exit(0);
  }
  string data_file = argv[1];
  string data = File_utils::read_file(data_file);
  vector<string> tokens = File_utils::string_split(data);
  for (string token: tokens) {
    cout << "'" << token << "'" << endl;
  }
}
