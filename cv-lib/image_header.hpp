#ifndef CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_

#include <cstdio>
#include "errors.hpp"
#include "image_depth.hpp"
#include "image_line_segment.hpp"
#include "pixel.hpp"
#include "point.hpp"

class Image_header {
    int ncomponents{}; // we're only supported 1 grayscale component or 3 color components
    Image_depth depth{};
    int ncols{};
    int nrows{};
    int row_stride{}; // for jpeg
    int npixels{};
    double col_offset{};
    double row_offset{};

public:
    Image_header();
    Image_header(const int m_ncols, const int m_nrows, const int m_ncomponents, const Image_depth m_depth);
    Image_header(const Image_header &image_header);
    Image_depth get_depth() const;
    int get_ncols() const;
    int get_ncomponents() const;
    int get_npixels() const;
    int get_nrows() const;
    int get_row_stride() const;
    void plot_line_low(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2);
    void plot_line_high(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2);
    void plot_line(Image_line_segment &image_line_segment);
    void read(FILE *fp, Errors &errors);
    void to_point(Point &point, int col, int row) const;
    void to_point(Point &point, Pixel &pixel) const;
    std::string to_string(const std::string &prefix = "") const;
    double to_x(int col) const;
    static double to_x(int col, int ncols);
    double to_y(int row) const;
    static double to_y(int row, int nrows);
    void write(FILE *fp, Errors &errors) const;
};

#endif // CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
