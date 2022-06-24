//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_ERRORS_HPP_
#define CV_WORKBENCH_SRC_ERRORS_HPP_

#include <list>
#include <string>

using namespace std;

class Errors {
 public:
  int error_ct = 0;
  list<string> error_list;
  void add(string error);
  void merge(Errors &errors) ;
  string to_string();
};

#endif //CV_WORKBENCH_SRC_ERRORS_HPP_
