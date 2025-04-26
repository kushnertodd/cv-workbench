//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_FRAME_HPP_
#define CV_WORKBENCH_SRC_IMAGE_FRAME_HPP_

#include <cstdio>
#include "errors.hpp"
#include "image_depth.hpp"
#include "image_line_segment.hpp"
#include "pixel.hpp"
#include "point.hpp"
#include "polar_trig.hpp"

class Image_frame {
    friend class Image_header;
    double col_offset{};
    int ncols{};
    int nrows{};
    double row_offset{};

public:
    Image_frame();
    Image_frame(const int m_ncols, const int m_nrows);
    Image_frame(const Image_frame &image_frame);

    void check_pixel_valid(int col, int row) const;
    double ellipse_dist(int col, int row) const;
    bool in_ellipse(int col, int row) const;
    bool is_pixel_valid(int col, int row) const;
    int pixel_theta_to_rho(Polar_trig &polar_trig, int col, int row, int theta_index);
    void plot_line_low(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2);
    void plot_line_high(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2);
    void plot_line(Image_line_segment &image_line_segment);
    int to_col(double x) const;
    void to_pixel(Pixel &pixel, double x, double y) const;
    void to_pixel(Pixel &pixel, Point &point);
    void to_point(Point &point, int col, int row) const;
    void to_point(Point &point, Pixel &pixel) const;
    int to_row(double y) const;
    std::string to_string(const std::string &prefix = "") const;
    double to_x(int col) const;
    double to_y(int row) const;
};

#endif // CV_WORKBENCH_SRC_IMAGE_FRAME_HPP_
