#ifndef CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_
#define CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_

#include <vector>
#include "errors.hpp"

namespace file_utils {
    long file_size(std::ifstream &in);
    FILE *open_file_read(const std::string &path, Errors &errors);
    std::ifstream open_file_read_binary(const std::string &path, Errors &errors);
    std::ifstream open_file_read_text(const std::string &path, Errors &errors);
    FILE *open_file_write(const std::string &path, Errors &errors);
    std::ofstream open_file_write_binary(const std::string &path, Errors &errors);
    std::ofstream open_file_write_text(const std::string &path, Errors &errors);
    bool read_file(const std::string &filename, std::string &contents);
    char *read_file_binary(const std::string &filename, int &length, Errors &errors);
    bool read_double(FILE *fp, double &var);
    bool read_float(FILE *fp, float &var);
    bool read_int(FILE *fp, int &var);
} // namespace file_utils

#endif // CV_WORKBENCH_CONFIG_FILE_UTILS_HPP_
