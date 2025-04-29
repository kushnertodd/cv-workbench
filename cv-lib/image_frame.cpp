#include "image_frame.hpp"
#include <iomanip>
#include <iostream>
#include "wb_utils.hpp"

extern bool debug;
/**
 * @brief
 */
Image_frame::Image_frame() = default;
/*
 * @brief
 * @param m_ncols
 * @param m_nrows
 */
Image_frame::Image_frame(const int m_ncols, const int m_nrows) : ncols(m_ncols), nrows(m_nrows) {
    if (debug)
        std::cout << "Image_frame::Image_frame: " << to_string() << std::endl;
    col_offset = ncols / 2.0;
    row_offset = nrows / 2.0;
}
Image_frame::Image_frame(const Image_frame &image_frame) : Image_frame(image_frame.ncols, image_frame.nrows) {}
void Image_frame::check_pixel_valid(int col, int row) const { assert(!is_pixel_valid(col, row)); }
/**
 * @brief distance from (col, row) to center of elipse inscribed into rectangle (ncols, nrows) is:
 *   a = ncols/2
 *   b = nrows/2
 *   dist = x^2/a^2 + y^2/b^2
 * @param col
 * @param row
 * @return
 */
double Image_frame::ellipse_dist(int col, int row) const {
    double a_sq = ncols * ncols / 4.0;
    double b_sq = nrows * nrows / 4.0;
    double x = col_to_x(col, ncols);
    double y = row_to_y(row, nrows);
    double dist = x * x / a_sq + y * y / b_sq;
    return dist;
}
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
bool Image_frame::in_ellipse(int col, int row) const {
    double dist = ellipse_dist(col, row, ncols, nrows);
    return dist <= 1.0;
}
/**
 * @brief
 * @param m_ncols
 * @param m_nrows
 */
void Image_frame::init(const int m_ncols, const int m_nrows) {
    ncols = m_ncols;
    nrows = m_nrows;
}
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
bool Image_frame::is_pixel_valid(int col, int row) const {
    return (col >= 0 && col < ncols && row >= 0 && row < nrows);
}
/**
 * @brief
 * @param polar_trig
 * @param col
 * @param row
 * @param theta_index
 * @return
 */
int Image_frame::pixel_theta_to_rho(Polar_trig &polar_trig, int col, int row, int theta_index) {
    int rho_index = Polar_trig::point_theta_to_rho(polar_trig.to_x(col), polar_trig.to_y(row), theta_index);
    return rho_index;
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
void Image_frame::plot_line_low(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2) {
    int d_col = col2 - col1;
    int d_row = row2 - row1;
    int row_i = 1;
    if (d_row < 0) {
        row_i = -1;
        d_row = -d_row;
    }
    int D = (2 * d_row) - d_col;
    int row = row1;

    for (int x = col1; x <= col2; x++) {
        image_line_segment.add(x, row);
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
void Image_frame::plot_line_high(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2) {
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
        image_line_segment.add(col, row);
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
void Image_frame::plot_line(Image_line_segment &image_line_segment) {
    int col1 = image_line_segment.pixel1.col;
    int row1 = image_line_segment.pixel1.row;
    int col2 = image_line_segment.pixel2.col;
    int row2 = image_line_segment.pixel2.row;
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
 * @param x
 * @return
 */
int Image_frame::to_col(double x) const { return wb_utils::double_to_int_round(x + col_offset); }
/**
 * @brief
 * @param pixel
 * @param x
 * @param y
 */
void Image_frame::to_pixel(Pixel &pixel, double x, double y) const { pixel.init(to_col(x), to_row(y)); }
/**
 * @brief
 * @param pixel
 * @param point
 */
void Image_frame::to_pixel(Pixel &pixel, Point &point) { to_pixel(point.x, point.y); }
/**
 * @brief
 * @param point
 * @param col
 * @param row
 */
void Image_frame::to_point(Point &point, int col, int row) const { pixel.init(to_x(col), to_y(row)); }
/**
 * @brief
 * @param point
 * @param pixel
 */
void Image_frame::to_point(Point &point, Pixel &pixel) const { to_point(point, pixel.col, pixel.row); }
/**
 * @brief
 * @param y
 * @return
 */
int Image_frame::to_row(double y) const { return wb_utils::double_to_int_round(row_offset - y); }
/**
 * @brief
 * @param prefix
 * @return
 */
std::string Image_frame::to_string(const std::string &prefix) const {
    std::ostringstream os;
    os << prefix << std::setw(20) << std::left << "ncols " << ncols << std::endl
       << prefix << std::setw(20) << std::left << " nrows " << nrows << std::endl;
    return os.str();
}
/**
 * @brief
 * @param col
 * @return
 */
double Image_frame::to_x(int col) const { return col - col_offset; }
/**
 * @brief
 * @param row
 * @return
 */
double Image_frame::to_y(int row) const { return row_offset - row; }
