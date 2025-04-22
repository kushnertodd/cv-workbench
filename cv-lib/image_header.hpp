//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_

#include <cstdio>
#include "errors.hpp"
#include "image_depth.hpp"

class Image_index {
    friend class Image_header;
    int col{};
    int row{};
    Image_index();
    Image_index(int m_col, int m_row);
    void init(int m_col, int m_row);
};

class Image_point {
    friend class Image_header;
    double x{};
    double y{};
    Image_point();
    Image_point(double m_x, double m_y);
    void init(double m_x, double m_y);
};

class Image_header {
    friend class Image;
    int ncomponents{}; // we're only supported 1 grayscale component or 3 color components
    Image_depth depth{};
    int ncols{};
    int npixels{};
    int nrows{};
    int row_stride{}; // for jpeg

public:
    Image_header();
    Image_header(const int m_nrows, const int m_ncols, const int m_ncomponents, const Image_depth m_depth);
    Image_header(const Image_header &image_header);

    void read(FILE *fp, Errors &errors);
    double to_x(int col);
    double to_y(int row);
    int to_col(double x);
    int to_row(double y);
    void to_index(Image_index &image_index, Image_point &image_point);
    void to_point(Image_point &image_point, Image_index &image_index);
    std::string to_string(const std::string &prefix = "") const;
    void write(FILE *fp, Errors &errors) const;
};

#endif // CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
