#ifndef CV_WORKBENCH_SRC_VIEW_HPP_
#define CV_WORKBENCH_SRC_VIEW_HPP_

#include "errors.hpp"
#include "line_segment.hpp"
#include "pixel.hpp"

class View {
public:
    virtual ~View() = 0;
    View();
    virtual bool check_grayscale(const std::string &module, Errors &errors) const = 0;
    virtual double get(int col, int row, int component = 0) const = 0;
    virtual double get(const Pixel &pixel, int component = 0) const = 0;
    virtual int get_ncols() const = 0;
    virtual int get_nrows() const = 0;
    virtual void to_point(Point &point, int col, int row) const = 0;
    virtual void to_point(Point &point, Pixel &pixel) const = 0;
};

#endif // CV_WORKBENCH_SRC_VIEW_HPP_
