//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_

#include <cstdio>
#include "errors.hpp"
#include "image_depth.hpp"

class Image_header {
    friend class Image;
    Image_frame image_frame;
    int ncomponents{}; // we're only supported 1 grayscale component or 3 color components
    Image_depth depth{};
    int npixels{};
    int row_stride{}; // for jpeg

public:
    Image_header();
    Image_header(const int m_ncols, const int m_nrows, const int m_ncomponents, const Image_depth m_depth);
    Image_header(const Image_header &image_header);

    void read(FILE *fp, Errors &errors);
    double to_x(int col) const;
    double to_y(int row) const;
    int to_col(double x) const;
    void to_pixel(Pixel &pixel, double x, double y);
    void to_pixel(Pixel &pixel, Point &point) const;
    void to_point(Point &point, int col, int row) const;
    void to_point(Point &point, Pixel &pixel) const;
    int to_row(double y) const;
    std::string to_string(const std::string &prefix = "") const;
    void write(FILE *fp, Errors &errors) const;
};

#endif // CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
