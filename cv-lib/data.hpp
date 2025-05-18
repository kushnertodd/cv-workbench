#ifndef CV_WORKBENCH_SRC_DATA_HPP_
#define CV_WORKBENCH_SRC_DATA_HPP_

#include <memory>
#include <string>
#include "errors.hpp"
#include "wb_data_format.hpp"
#include "wb_defs.hpp"
#include "wb_log.hpp"

class Data {

public:
    WB_data_format::Data_format format;
    std::list<std::string> lines;
    std::unique_ptr<char *> binary_data;
    int length{};
    virtual ~Data();
    Data();
    static Data *read(const std::string &path, Errors &errors);
    static Data *read_text(const std::string &path, Errors &errors);
    static Data *read_text(std::ifstream &ifs, Errors &errors);
    void write(const std::string &path, Errors &errors) const;
    void write_text(const std::string &path, Errors &errors) const;
    void write_text(std::ofstream &ofs, Errors &errors) const;
};

#endif // CV_WORKBENCH_SRC_DATA_HPP_
