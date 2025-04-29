#include "runtime.hpp"
#include <string>
#include "wb_utils.hpp"
#include "wb_version.hpp"

const char *Runtime::path = "";
const char *Runtime::run_time = Runtime::get_run_time();
/**
 * @brief
 * @return
 */
const char *Runtime::get_path() { return path; }
/**
 * @brief
 * @return
 */
const char *Runtime::get_run_time() { return run_time; }
/**
 * @brief
 * @return
 */
const char *Runtime::get_username() { return std::getenv("USER"); }
/**
 * @brief
 * @return
 */
const char *Runtime::get_version() { return VERSION; }
/**
 * @brief
 * @param m_path
 */
void Runtime::init(const char *m_path) {
    path = m_path;
    run_time = wb_utils::timestamp().c_str();
}
/**
 * @brief
 * @return
 */
json_object *Runtime::to_log() {
    json_object *log_entry = json_object_new_object();
    json_object_object_add(log_entry, "script-path", json_object_new_string(get_path()));
    json_object_object_add(log_entry, "run-time", json_object_new_string(get_run_time()));
    json_object_object_add(log_entry, "username", json_object_new_string(get_username()));
    json_object_object_add(log_entry, "version", json_object_new_string(get_version()));
    return log_entry;
}
