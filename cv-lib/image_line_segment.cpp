//
// Created by kushn on 7/5/2022.
//

#include "image_line_segment.hpp"
#include <iostream>
#include <sstream>
#include "wb_utils.hpp"

extern bool debug;

Image_line_segment::Image_line_segment() = default;
Image_line_segment::Image_line_segment(const Pixel &m_pixel1, const Pixel &m_pixel2) :
    pixel1(m_pixel1), pixel2(m_pixel2) {
    if (debug)
        std::cout << "Image_line_segment::Image_line_segment pixel1 (" << pixel1.to_string() << ") pixel2 ("
                  << pixel2.to_string() << ")" << std::endl;
}
void Image_line_segment::add(int col, int row) {
    Pixel pixel(row, col);
    add(pixel);
}
void Image_line_segment::add(const Pixel &pixel) { line_pixels.push_back(pixel); }
void Image_line_segment::init(const Pixel &m_pixel1, const Pixel &m_pixel2) {
    pixel1 = m_pixel1;
    pixel2 = m_pixel2;
}
void Image_line_segment::log(std::list<WB_log_entry> &log_entries) const {
    WB_log_entry log_entry_start_row("start row", wb_utils::int_to_string(pixel1.row));
    log_entries.push_back(log_entry_start_row);
    WB_log_entry log_entry_start_col("start col", wb_utils::int_to_string(pixel1.col));
    log_entries.push_back(log_entry_start_col);
    WB_log_entry log_entry_end_row("end row", wb_utils::int_to_string(pixel2.row));
    log_entries.push_back(log_entry_end_row);
    WB_log_entry log_entry_end_col("end col", wb_utils::int_to_string(pixel2.col));
    log_entries.push_back(log_entry_end_col);
}
std::string Image_line_segment::to_string() const {
    std::ostringstream os;
    os << "pixel 1 " << pixel1.to_string() << " pixel 2 " << pixel2.to_string();
    return os.str();
}
