#ifndef CV_WORKBENCH_SRC_DATA_HPP_
#define CV_WORKBENCH_SRC_DATA_HPP_

#include <memory>
#include <string>
#include "errors.hpp"
#include "wb_defs.hpp"
#include "wb_log.hpp"

class Data {

public:
    std::list<std::string> lines;
    virtual ~Data();
    Data();
    static Data *read_text(const std::string &path, Errors &errors);
    static Data *read_text(std::ifstream &ifs, Errors &errors);
    void write_text(const std::string &path, Errors &errors) const;
    void write_text(std::ofstream &ofs, Errors &errors) const;
};

#endif // CV_WORKBENCH_SRC_DATA_HPP_
