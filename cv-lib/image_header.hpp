//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_

#include <cstdio>
#include "image_depth.hpp"
#include "errors.hpp"

class Image_header {
    friend class Image;

private:
    int rows{};
    int cols{};
    int components{}; // we're only supported 1 grayscale component or 3 color components
    int row_stride{}; // for jpeg
    Image_depth depth{};
    int npixels{};

public:
    Image_header();

    Image_header(const int m_rows, const int m_cols, const int m_components,
                 const Image_depth m_depth);

    Image_header(const Image_header &image_header);

    void read(FILE *fp, Errors &errors);

    void write(FILE *fp, Errors &errors) const;

    std::string to_string(const std::string &prefix = "") const;
};

#endif //CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
