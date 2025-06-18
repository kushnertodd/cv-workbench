#ifndef CV_WORKBENCH_SRC_SUBIMAGE_HPP_
#define CV_WORKBENCH_SRC_SUBIMAGE_HPP_

// #include <memory>
// #include <string>
#include "errors.hpp"
#include "image.hpp"
#include "image_line_segment.hpp"
#include "line_segment.hpp"
// #include "pixel.hpp"
// #include "variance_stats.hpp"
// #include "wb_convert_types.hpp"
// #include "wb_defs.hpp"
// #include "wb_log.hpp"
// #include "wb_resize_types.hpp"
#include "view.hpp"

class Sub_image : View {
    Image *image;
    int min_col;
    int min_row;
    int max_col;
    int max_row;

public:
    virtual ~Sub_image();
    Sub_image();
    Sub_image(Image *m_image, int m_min_col, int m_min_row, int m_max_col, int m_max_row);
    bool check_grayscale(const std::string &module, Errors &errors) const;
    void draw_line_segment(const Image_line_segment &image_line_segment, double value, int component = 0) const;
    void draw_line_segment(int col1, int row1, int col2, int row2, double value, int component = 0) const;
    double get(int col, int row, int component = 0) const;
    double get(const Pixel &pixel, int component = 0) const;
    int get_max_col() const;
    int get_max_row() const;
    int get_min_col() const;
    int get_min_row() const;
    int get_ncols() const;
    int get_nrows() const;
    void set(int col, int row, double value, int component = 0) const;
    void set(const Pixel &pixel, double value, int component = 0) const;
    void to_point(Point &point, int col, int row);
    void to_point(Point &point, Pixel &pixel);
    void to_image_line_segment(Image_line_segment &image_line_segment, Line_segment &line_segment);
    double to_x(int col) const;
    double to_x(int col, int ncols);
    double to_y(int row) const;
    double to_y(int row, int nrows);
};

#endif // CV_WORKBENCH_SRC_SUBIMAGE_HPP_
