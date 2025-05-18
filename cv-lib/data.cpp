#include "data.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
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
Data *Data::read(const std::string &path, Errors &errors) {
    int length{};
    Data *data = new Data();
    data->binary_data = std::make_unique<char *>(file_utils::read_file_binary(path, data->length, errors));
    if (errors.has_error())
        return nullptr;
    data->format = WB_data_format::Data_format::BINARY;
    return data;
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
Data *Data::read_text(const std::string &path, Errors &errors) {
    Data *data = nullptr;
    std::ifstream ifs = file_utils::open_file_read_text(path, errors);
    if (!errors.has_error()) {
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
    data->format = WB_data_format::Data_format::TEXT;
    return data;
}
/**
 * @brief
 * @param path
 * @param delim
 * @param errors
 */
void Data::write(const std::string &path, Errors &errors) const {
    assert(format == WB_data_format::Data_format::BINARY);
    std::ofstream ofs = file_utils::open_file_write_binary(path, errors);
    if (!errors.has_error()) {
        ofs.write(reinterpret_cast<char *>(binary_data.get()), length);
        ofs.close();
    }
}
/**
 * @brief
 * @param path
 * @param delim
 * @param errors
 */
void Data::write_text(const std::string &path, Errors &errors) const {
    assert(format == WB_data_format::Data_format::TEXT);
    std::ofstream ofs = file_utils::open_file_write_text(path, errors);
    if (!errors.has_error()) {
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
    assert(format == WB_data_format::Data_format::TEXT);
    assert(ofs.is_open());
    for (std::string line: lines) {
        ofs << line << std::endl;
    }
    ofs.close();
}
