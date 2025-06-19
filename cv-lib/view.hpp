#ifndef CV_WORKBENCH_SRC_VIEW_HPP_
#define CV_WORKBENCH_SRC_VIEW_HPP_

#include "errors.hpp"
#include "pixel.hpp"
#include "line_segment.hpp"

class View {
    int ncols;
    int nrows;

public:
    virtual ~View() = 0;
    View();
    View(int ncols, int nrows);
    virtual bool check_grayscale(const std::string &module, Errors &errors) const = 0;
    virtual double get(int col, int row, int component = 0) const = 0;
    virtual double get(const Pixel &pixel, int component = 0) const = 0;
    virtual int get_ncols() const = 0;
    virtual int get_nrows() const = 0;
    virtual void to_point(Point &point, int col, int row) = 0;
    virtual void to_point(Point &point, Pixel &pixel) = 0;
    virtual double to_x(int col) const = 0;
    virtual double to_y(int row) const = 0;
};

#endif // CV_WORKBENCH_SRC_VIEW_HPP_
