//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_

#include <cstdio>
#include "errors.hpp"
#include "wb_enums.hpp"

class Image_header {
 public:
  int rows;
  int cols;
  int components; // we're only supported 1 grayscale component now
  int row_stride; // for jpeg
  int npixels;
  Cv_image_depth_enum depth;
  Image_header(int m_rows, int m_cols, int m_components, Cv_image_depth_enum m_depth);
  static Image_header *read_header(FILE *fp, string path, Errors &errors);
  void write_header(FILE *fp, string path, Errors &errors);
  string toString();
};

#endif //CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
