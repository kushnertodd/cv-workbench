#include "file_utils.hpp"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

/**
 * @brief returns size of file in bytes
 * @param fp file pointer
 * @return long byte count
 */
long file_utils::file_size(std::ifstream &in) {
    // Get the number of bytes
    in.seekg(0, std::ios::end);
    return in.tellg();
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
FILE *file_utils::open_file_read(const std::string &path, Errors &errors) {
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == nullptr)
        errors.add("file_utils::open_file_read", "", "cannot open file " + path + " for reading: " + strerror(errno));
    return fp;
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
std::ifstream file_utils::open_file_read_binary(const std::string &path, Errors &errors) {
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    if (!ifs.is_open())
        errors.add("file_utils::open_file_read_binary", "",
                   "cannot open file " + path + " for reading: " + strerror(errno));
    return ifs;
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
std::ifstream file_utils::open_file_read_text(const std::string &path, Errors &errors) {
    std::ifstream ifs(path, std::ifstream::in);
    if (!ifs.is_open()) {
        errors.add("file_utils::open_file_read_text", "",
                   "cannot open file " + path + " for reading: " + strerror(errno));
    }
    return ifs;
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
FILE *file_utils::open_file_write(const std::string &path, Errors &errors) {
    FILE *fp = fopen(path.c_str(), "w");
    if (fp == nullptr)
        errors.add("file_utils::open_file_write", "", "cannot open file " + path + " for writing: " + strerror(errno));
    return fp;
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
std::ofstream file_utils::open_file_write_binary(const std::string &path, Errors &errors) {
    std::ofstream ofs(path, std::ios::out | std::ios::binary);
    if (!ofs.is_open())
        errors.add("file_utils::open_file_write_binary", "",
                   "cannot open file " + path + " for writing: " + strerror(errno));
    return ofs;
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
std::ofstream file_utils::open_file_write_text(const std::string &path, Errors &errors) {
    std::ofstream ofs(path, std::ofstream::out);
    if (!ofs.is_open())
        errors.add("file_utils::open_file_write_text", "",
                   "cannot open file " + path + " for reading: " + strerror(errno));
    return ofs;
}
/**
 * @brief read entire binary file
 * @param filename
 * @param contents
 * @return
 */
char *file_utils::read_file_binary(const std::string &filename, int &length, Errors &errors) {
    char *buffer = nullptr;
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (!in.is_open()) {
        errors.add("file_utils::read_file_binary", "",
                   "cannot open file " + filename + " for reading: " + strerror(errno));
    } else {
        length = file_size(in);
        in.seekg(0, std::ios::beg);
        buffer = new char[length];
        in.read(buffer, length);
        in.close();
    }
    return buffer;
}
/**
 * @brief read entire text file as string
 * @param filename
 * @param file contents
 * @return
 */
bool file_utils::read_file_text(const std::string &filename, std::string &contents, Errors &errors) {
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (!in.is_open()) {
        errors.add("file_utils::read_file_text", "",
                   "cannot open file " + filename + " for reading: " + strerror(errno));
        return false;
    } else {
        contents.resize(file_size(in));
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return true;
    }
}
/**
 * @brief
 * @param fp
 * @param var
 * @return
 */
bool file_utils::read_double(FILE *fp, double &var) {
    size_t newLen = fread(&var, sizeof(double), 1, fp);
    return (ferror(fp) == 0 && newLen == 1);
}
/**
 * @brief
 * @param fp
 * @param var
 * @return
 */
bool file_utils::read_float(FILE *fp, float &var) {
    size_t newLen = fread(&var, sizeof(float), 1, fp);
    return (ferror(fp) == 0 && newLen == 1);
}
/**
 * @brief
 * @param fp
 * @param var
 * @return
 */
bool file_utils::read_int(FILE *fp, int &var) {
    size_t newLen = fread(&var, sizeof(int), 1, fp);
    return (ferror(fp) == 0 && newLen == 1);
}
