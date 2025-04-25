//
// Created by kushn on 6/14/2022.
//

#include <iomanip>
#include <iostream>
#include "image_frame.hpp"
#include "wb_utils.hpp"

extern bool debug;

Image_frame::Image_frame() = default;
/*
 *
 * @param m_ncols
 * @param m_nrows
 */
Image_frame::Image_frame(const int m_ncols, const int m_nrows) : ncols(m_ncols), nrows(m_nrows) {
    if (debug)
        std::cout << "Image_frame::Image_frame: " << to_string() << std::endl;
}
Image_frame::Image_frame(const Image_frame &image_frame) : Image_frame(image_frame.ncols, image_frame.nrows) {}

void Image_frame::check_point_valid(int col, int row) const {
    assert(col >= 0 && col < ncols && row >= 0 && row < nrows);
}
/**
 * distance from (row, col) to center of elipse inscribed into rectangle (nrows, ncols) is:
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
bool Image_frame::in_ellipse(int col, int row) const {
    double dist = ellipse_dist(row, col, nrows, ncols);
    return dist <= 1.0;
}
void init(const int m_ncols, const int m_nrows) {
    ncols = m_ncols;
    nrows = m_nrows;
}
bool Image_frame::is_valid(int col, int row) const { return (col >= 0 && col < ncols && row >= 0 && row < nrows); }
int Image_frame::to_col(double x) const { return wb_utils::double_to_int_round(x + ncols / 2.0); }
void Image_frame::to_pixel(Pixel &pixel, double x, double y) { pixel.init(to_col(x), to_row(y)); }
void Image_frame::to_pixel(Pixel &pixel, Point &point) { to_pixel(point.x, point.y); }
void Image_frame::to_point(Point &point, int col, int row) const { pixel.init(to_x(col), to_y(row)); }
void Image_frame::to_point(Point &point, Pixel &pixel) const { pixel.col, pixel.row);
}
int Image_frame::to_row(double y) const { return wb_utils::double_to_int_round(nrows / 2.0 - y); }
std::string Image_frame::to_string(const std::string &prefix) const {
    std::ostringstream os;
    os << prefix << std::setw(20) << std::left << "ncols " << ncols << std::endl
       << prefix << std::setw(20) << std::left << "nrows " << nrows << std::endl;
    return os.str();
}
double Image_frame::to_x(int col) const { return (col + 0.5) - ncols / 2.0; }
double Image_frame::to_y(int row) const { return nrows / 2.0 - (row + 0.5); }
