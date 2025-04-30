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
    int get_ncols() const;
    int get_nrows() const;
    void init(const int m_ncols, const int m_nrows);
    bool is_pixel_valid(int col, int row) const;
    void plot_line_low(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2);
    void plot_line_high(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2);
    void plot_line(Image_line_segment &image_line_segment);
    void to_point(Point &point, int col, int row) const;
    void to_point(Point &point, Pixel &pixel) const;
    std::string to_string(const std::string &prefix = "") const;
    double to_x(int col) const;
    double to_y(int row) const;
};

#endif // CV_WORKBENCH_SRC_IMAGE_FRAME_HPP_
