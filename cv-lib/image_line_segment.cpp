#include "image_line_segment.hpp"
#include <iostream>
#include <sstream>
#include "wb_utils.hpp"

extern bool debug;

/**
 * @brief
 */
Image_line_segment::Image_line_segment() = default;
/**
 * @brief
 * @param m_pixel1
 * @param m_pixel2
 */
Image_line_segment::Image_line_segment(const Pixel &m_pixel1, const Pixel &m_pixel2) :
    Image_line_segment(m_pixel1.col, m_pixel1.row, m_pixel2.col, m_pixel1.row) {}
/**
 * @brief
 * @param col1
 * @param row1
 * @param col2
 * @param row2
 */
Image_line_segment::Image_line_segment(int col1, int row1, int col2, int row2) {
    if (debug)
        std::cout << "Image_line_segment::Image_line_segment pixel1 (" << pixel1.to_string() << ") pixel2 ("
                  << pixel2.to_string() << ")" << std::endl;
    pixel1.init(col1, row1);
    pixel2.init(col2, row2);
    init(pixel1, pixel2);
}
/**
 * @brief
 * @param col
 * @param row
 */
void Image_line_segment::add(int col, int row) {
    Pixel pixel(col, row);
    add(pixel);
}
/**
 * @brief
 * @param pixel
 */
void Image_line_segment::add(const Pixel &pixel) { line_pixels.push_back(pixel); }
/**
 * @brief
 * @param m_pixel1
 * @param m_pixel2
 */
void Image_line_segment::init(const Pixel &m_pixel1, const Pixel &m_pixel2) {
    pixel1 = m_pixel1;
    pixel2 = m_pixel2;
    plot_line();
}
/**
 * @brief
 * @param log_entries
 */
void Image_line_segment::log(std::vector<WB_log_entry> &log_entries) const {
    WB_log_entry log_entry_start_row("start row", wb_utils::int_to_string(pixel1.row));
    log_entries.push_back(log_entry_start_row);
    WB_log_entry log_entry_start_col("start col", wb_utils::int_to_string(pixel1.col));
    log_entries.push_back(log_entry_start_col);
    WB_log_entry log_entry_end_row("end row", wb_utils::int_to_string(pixel2.row));
    log_entries.push_back(log_entry_end_row);
    WB_log_entry log_entry_end_col("end col", wb_utils::int_to_string(pixel2.col));
    log_entries.push_back(log_entry_end_col);
}
/**
 * @brief
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 * This fills in line segment pixels with Bresenham's line algorithm
 * @param image_line_segment
 * @param col1
 * @param row1
 * @param col2
 * @param row2
 */
void Image_line_segment::plot_line_low(int col1, int row1, int col2, int row2) {
    int d_col = col2 - col1;
    int d_row = row2 - row1;
    int row_i = 1;
    if (d_row < 0) {
        row_i = -1;
        d_row = -d_row;
    }
    int D = (2 * d_row) - d_col;
    int row = row1;

    for (int col = col1; col <= col2; col++) {
        add(col, row);
        if (D > 0) {
            row = row + row_i;
            D = D + (2 * (d_row - d_col));
        } else {
            D = D + 2 * d_row;
        }
    }
}
/**
 * @brief
 * @param image_line_segment
 * @param col1
 * @param row1
 * @param col2
 * @param row2
 */
void Image_line_segment::plot_line_high(int col1, int row1, int col2, int row2) {
    int d_col = col2 - col1;
    int d_row = row2 - row1;
    int col_i = 1;
    if (d_col < 0) {
        col_i = -1;
        d_col = -d_col;
    }
    int D = (2 * d_col) - d_row;
    int col = col1;
    for (int row = row1; row <= row2; row++) {
        add(col, row);
        if (D > 0) {
            col = col + col_i;
            D = D + (2 * (d_col - d_row));
        } else {
            D = D + 2 * d_col;
        }
    }
}
/**
 * @brief
 * @param image_line_segment
 */
void Image_line_segment::plot_line() {
    int col1 = pixel1.col;
    int row1 = pixel1.row;
    int col2 = pixel2.col;
    int row2 = pixel2.row;
    if (abs(row2 - row1) < abs(col2 - col1)) {
        if (col1 > col2) {
            plot_line_low(col2, row2, col1, row1);
        } else {
            plot_line_low(col1, row1, col2, row2);
        }
    } else {
        if (row1 > row2) {
            plot_line_high(col2, row2, col1, row1);
        } else {
            plot_line_high(col1, row1, col2, row2);
        }
    }
}
/**
 * @brief
 * @return
 */
std::string Image_line_segment::to_string() const {
    std::ostringstream os{};
    os << "pixel 1 " << pixel1.to_string() << " pixel 2 " << pixel2.to_string();
    return os.str();
}
void Image_line_segment::translate(int col, int row) {
    pixel1.translate(col, row);
    pixel2.translate(col, row);
    for (Pixel pixel: line_pixels)
        pixel.translate(col, row);
}
void Image_line_segment::translate(Pixel pixel) { translate(pixel.col, pixel.row); }
