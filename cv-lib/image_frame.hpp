//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_

#include <cstdio>
#include "errors.hpp"
#include "image_depth.hpp"

class Image_frame {
    friend class Image_header;
    int ncols{};
    int nrows{};

public:
    Image_frame();
    Image_frame(const int m_ncols, const int m_nrows);
    Image_frame(const Image_frame &image_frame);

    void check_point_valid(int col, int row) const;
    double ellipse_dist(int col, int row) const;
    bool in_ellipse(int col, int row) const;
    bool is_valid(int col, int row) const;
    int to_col(double x) const;
    void to_pixel(Pixel &pixel, double x, double y);
    void to_pixel(Pixel &pixel, Point &point);
    void to_point(Point &point, int col, int row) const;
    void to_point(Point &point, Pixel &pixel) const;
    int to_row(double y) const;
    std::string to_string(const std::string &prefix = "") const;
    double to_x(int col) const;
    double to_y(int row) const;
};

#endif // CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
