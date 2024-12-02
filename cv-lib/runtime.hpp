//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_RUNTIME_HPP_
#define CV_WORKBENCH_SRC_RUNTIME_HPP_

#include <string>
#include "json-c/json.h"

class Runtime {
 public:
  static const char *path;
  static const char *run_time;

  static const char *get_path();
  static const char *get_username();
  static const char *get_version();
  static const char *get_run_time();
  static void init(const char *m_path);
  static json_object *to_log();
};

#endif //CV_WORKBENCH_SRC_RUNTIME_HPP_
