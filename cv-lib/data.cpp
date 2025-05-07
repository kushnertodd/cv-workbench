#include "data.hpp"
#include <fstream>
#include <iostream>
#include "file_utils.hpp"
#include "wb_utils.hpp"

extern bool debug;

/**
 * @brief
 */
Data::~Data() {}
/**
 * @brief
 */
Data::Data() = default;
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
Data *Data::read_text(const std::string &path, Errors &errors) {
    std::ifstream ifs = file_utils::open_file_read_text(path, errors);
    Data *data = nullptr;
    if (ifs) {
        data = read_text(ifs, errors);
        ifs.close();
    }
    return data;
}
/**
 * @brief
 * @param ifs
 * @param errors
 * @return
 */
Data *Data::read_text(std::ifstream &ifs, Errors &errors) {
    Data *data = new Data();
    std::string line;
    while (getline(ifs, line)) {
        data->lines.push_back(line);
    }
    return data;
}
/**
 * @brief
 * @param path
 * @param delim
 * @param errors
 */
void Data::write_text(const std::string &path, Errors &errors) const {
    if (std::ofstream ofs = file_utils::open_file_write_text(path, errors)) {
        write_text(ofs, errors);
        ofs.close();
    }
}
/**
 * @brief
 * @param ofs
 * @param delim
 * @param errors
 */
void Data::write_text(std::ofstream &ofs, Errors &errors) const {
    for (std::string line: lines) {
        ofs << line << std::endl;
    }
    ofs.close();
}
