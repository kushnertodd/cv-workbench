#include <iomanip>
#include <iostream>

using namespace std;

void stringFind(string text, string& prefix, string& suffix, string pat, bool &found, bool &at_beginning, bool &at_end) {
  size_t text_len = text.length();
  size_t pat_len = pat.length();
  size_t pos = text.find(pat);
  at_beginning = false;
  at_end = false;
  found = false;
  if (pos != string::npos) {
    at_beginning = (pos == 0);
    at_end = (text_len - pat_len == pos);
    prefix = text.substr(0, pos);
    suffix = text.substr(pos+pat_len);
  } else {
    prefix = "";
    suffix = text;
    found = true;
  }
}

int main(int argc, char **argv) {
  if (argc < 3) {
    cout << "usage: " << argv[0] << " string substring" << endl;
    exit(0);
  }
  string text = argv[1];
  string substring = argv[2];

  string prefix, suffix;
  bool at_beginning = false;
  bool at_end = false;
  bool found = false;
  stringFind(text, prefix, suffix, substring, found, at_beginning, at_end);
  cout << "found  at end  at beginning  prefix            suffix" << endl;
  cout << "-----  ------  ------------  ----------------  -----------------" << endl;
  cout << (found ?         "true   " : "false  ");
  cout << (at_end ?        "true    " : "false   ");
  cout << (at_beginning ?  "true   " : "false  ");
  cout << "       ";
  cout << setw(15) << left << prefix;
  cout << "   ";
  cout << setw(15) << left << suffix;
  cout << endl;
}
