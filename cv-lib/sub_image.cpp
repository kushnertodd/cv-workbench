// #include <cassert>
// #include <cmath>
// #include <csetjmp>
// #include <cstdio>
// #include <fstream>
// #include <iomanip>
// #include <iostream>
// #include "file_utils.hpp"
// #include "image.hpp"
// #include "image_depth.hpp"
// #include "jpeglib.h"
// #include "wb_utils.hpp"
#include "sub_image.hpp"


extern bool debug;

/**
 * @brief
 */
Sub_image::~Sub_image() {}
/**
 * @brief
 */
Sub_image::Sub_image() = default;
/**
 * kludgy, any bool argument invokes. needed to honor legacy calls.
 * @brief
 * @param m_ncols
 * @param m_nrows
 * @param m_components
 * @param m_depth
 * @param value
 */
Sub_image::Sub_image(Image *m_image, int m_min_col, int m_min_row, int m_max_col, int m_max_row) :
    View(m_max_col - m_min_col + 1, m_max_row - m_min_row + 1), image(m_image), min_col(m_min_col), min_row(m_min_row),
    max_col(m_max_col), max_row(m_max_row), ncols(max_col - min_col + 1), nrows(max_row - min_row + 1) {
    col_offset = ncols / 2.0;
    row_offset = nrows / 2.0;
}
/**
 * @brief
 * @param module
 * @param errors
 * @return
 */
bool Sub_image::check_grayscale(const std::string &module, Errors &errors) const {
    return image->check_grayscale(module, errors);
}
/**
 * @brief
 * @param line_segment
 * @param value
 * @param component
 */
void Sub_image::draw_line_segment(const Image_line_segment &image_line_segment, double value, int component) const {
    image->draw_line_segment(image_line_segment, value, component);
}
/**
 * @brief
 * @param col1
 * @param row1
 * @param col2
 * @param row2
 * @param value
 * @param component
 */
void Sub_image::draw_line_segment(int col1, int row1, int col2, int row2, double value, int component) const {
    image->draw_line_segment(to_image_col(col1), to_image_row(row1), to_image_col(col2), to_image_row(row2), value,
                             component);
}
/**
 * @brief
 * @param col
 * @param row
 * @param component
 * @return
 */
double Sub_image::get(const int col, const int row, const int component) const {
    return image->get(to_image_col(col), to_image_row(row), component);
}
/**
 * @brief
 * @param pixel
 * @param component
 * @return
 */
double Sub_image::get(const Pixel &pixel, const int component) const { return get(pixel.col, pixel.row, component); }
/**
 * @brief
 * @return
 */
int Sub_image::get_max_col() const { return max_col; }
/**
 * @brief
 * @return
 */
int Sub_image::get_max_row() const { return max_row; }
/**
 * @brief
 * @return
 */
int Sub_image::get_min_col() const { return min_col; }
/**
 * @brief
 * @return
 */
int Sub_image::get_min_row() const { return min_row; }
/**
 * @brief
 * @return
 */
int Sub_image::get_ncols() const { return ncols; }
/**
 * @brief
 * @return
 */
int Sub_image::get_nrows() const { return nrows; }
void Sub_image::set(int col, int row, double value, int component) const { image->set(col, row, value, component); }
void Sub_image::set(const Pixel &pixel, double value, int component) const { image->set(pixel, value, component); }
double Sub_image::to_col(double x) const { return x + col_offset - 0.5; }
double Sub_image::to_col(double x, int ncols) { return x + ncols / 2.0 - 0.5; }
int Sub_image::to_image_col(int col) const { return col + min_col; }
/**
 * @brief
 * @param image_line_segment
 * @param line_segment
 */
void Sub_image::to_image_line_segment(Image_line_segment &image_line_segment, Line_segment &line_segment) {
    image->to_image_line_segment(image_line_segment, line_segment);
}
void Sub_image::to_image_pixel(Pixel &image_pixel, Pixel &pixel) {
    pixel.init(to_image_col(image_pixel.col), to_image_row(image_pixel.row));
}
int Sub_image::to_image_row(int row) const { return row + min_row; }
void Sub_image::to_pixel(Pixel &pixel, double x, double y) const { pixel.init(to_col(x), to_row(y)); }
void Sub_image::to_pixel(Pixel &pixel, Point &point) { to_pixel(pixel, point.x, point.y); }
void Sub_image::to_point(Point &point, int col, int row) { point.init(to_x(col), to_y(row)); }
void Sub_image::to_point(Point &point, Pixel &pixel) { to_point(point, pixel.col, pixel.row); }
double Sub_image::to_row(double y) const { return row_offset - y - 0.5; }
double Sub_image::to_row(double y, int nrows) { return nrows / 2.0 - y - 0.5; }
void Sub_image::to_sub_image_pixel(Pixel &pixel, Pixel &image_pixel) const {
    pixel.init(to_image_col(pixel.col), to_image_row(pixel.row));
}
/**
 * @brief
 * @param col
 * @return
 */
double Sub_image::to_x(int col) const {
    double x = col - col_offset + 0.5;
    return x;
}
/*
 * @brief
 * @param col
 * @param ncols
 * @return
 */
double Sub_image::to_x(int col, int ncols) {
    double x = col - ncols / 2.0 + 0.5;
    return x;
}
/**
 * @brief
 * @param row
 * @return
 */
double Sub_image::to_y(int row) const {
    double y = row_offset - row - 0.5;
    return y;
}
/**
 * @brief
 * @param row
 * @param nrows
 * @return
 */
double Sub_image::to_y(int row, int nrows) {
    double y = nrows / 2.0 - row - 0.5;
    return y;
}
