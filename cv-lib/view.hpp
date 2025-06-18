#ifndef CV_WORKBENCH_SRC_VIEW_HPP_
#define CV_WORKBENCH_SRC_VIEW_HPP_

#include "errors.hpp"
#include "image_line_segment.hpp"
#include "line_segment.hpp"

class View {
    int ncols;
    int nrows;

public:
    virtual ~View() = 0;
    View();
    View(int ncols, int nrows);
    virtual bool check_grayscale(const std::string &module, Errors &errors) const = 0;
    virtual void draw_line_segment(const Image_line_segment &image_line_segment, double value,
                                   int component = 0) const = 0;
    virtual void draw_line_segment(int col1, int row1, int col2, int row2, double value, int component = 0) const = 0;
    virtual double get(int col, int row, int component = 0) const = 0;
    virtual double get(const Pixel &pixel, int component = 0) const = 0;
    virtual int get_ncols() const = 0;
    virtual int get_nrows() const = 0;
    virtual void to_image_line_segment(Image_line_segment &image_line_segment, Line_segment &line_segment) = 0;
    virtual void to_point(Point &point, int col, int row) = 0;
    virtual void to_point(Point &point, Pixel &pixel) = 0;
    virtual double to_x(int col) const = 0;
    // virtual      double to_x(int col, int ncols) = 0;
    virtual double to_y(int row) const = 0;
    // virtual      double to_y(int row, int nrows) = 0;
};

#endif // CV_WORKBENCH_SRC_VIEW_HPP_
