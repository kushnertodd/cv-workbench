#ifndef SRC__WB_FILENAME_HPP_
#define SRC__WB_FILENAME_HPP_

#include <string>
#include "errors.hpp"
#include "wb_data_format.hpp"
#include "wb_defs.hpp"
/**
 * @brief
 */
class Wb_filename {
    std::string filename{};
    std::string root{};
    std::string ext{};
    WB_data_format::Data_format format{};

public:
    Wb_filename();
    Wb_filename(std::string m_filename, std::string m_root, std::string m_ext, WB_data_format::Data_format m_format);
    void add_suffix(const std::string &suffix);
    static Wb_filename *create_wb_filename(const std::string &m_filename, Errors &errors);
    bool is_bin() const;
    bool is_jpeg() const;
    bool is_json() const;
    bool is_log() const;
    bool is_text() const;
    static bool match_ext(const std::string &filename, const std::string &ext, std::string &root);
    std::string to_bin() const;
    std::string to_hist() const;
    std::string to_hist_script() const;
    std::string to_hist_text() const;
    std::string to_hough() const;
    std::string to_hough_text() const;
    std::string to_jpeg() const;
    std::string to_json() const;
    std::string to_log() const;
    std::string to_peaks() const;
    std::string to_peaks_text() const;
    std::string to_text() const;
};

#endif // SRC__WB_FILENAME_HPP_
