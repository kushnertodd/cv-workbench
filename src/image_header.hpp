//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_

#include <cstdio>
#include "errors.hpp"
#include "wb_defs.hpp"

class Image_header {
 public:
  int rows{};
  int cols{};
  int components{}; // we're only supported 1 grayscale component now
  int row_stride{}; // for jpeg
  int npixels{};
  cv_enums::CV_image_depth depth;
  Image_header();
  Image_header(int m_rows, int m_cols, int m_components,
               cv_enums::CV_image_depth m_depth);
  Image_header(Image_header &image_header);
  void read(FILE *fp, const std::string &path, Errors &errors);
  void write(FILE *fp, const std::string &path, Errors &errors) const;
  std::string to_string() const;
};

#endif //CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
