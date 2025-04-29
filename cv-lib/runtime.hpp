#ifndef CV_WORKBENCH_SRC_RUNTIME_HPP_
#define CV_WORKBENCH_SRC_RUNTIME_HPP_

#include <string>
#include "json-c/json.h"
/**
 * @brief
 */
class Runtime {
    static const char *path;
    static const char *run_time;

public:
    static const char *get_path();
    static const char *get_username();
    static const char *get_version();
    static const char *get_run_time();
    static void init(const char *m_path);
    static json_object *to_log();
};

#endif // CV_WORKBENCH_SRC_RUNTIME_HPP_
