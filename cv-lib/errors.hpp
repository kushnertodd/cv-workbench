#ifndef CV_WORKBENCH_SRC_ERRORS_HPP_
#define CV_WORKBENCH_SRC_ERRORS_HPP_

#include <list>
#include <string>

class Errors {
public:
    int error_ct = 0;
    std::list<std::string> error_list;

    void add(const std::string &module, const std::string &id, const std::string &error);
    void check_exit(const std::string &message = "");
    bool has_error() const;
    std::string to_string();
};

#endif // CV_WORKBENCH_SRC_ERRORS_HPP_
