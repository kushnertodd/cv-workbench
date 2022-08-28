//
// Created by kushn on 6/14/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_

#include <cstdio>
#include "wb_data_format.hpp"
#include "wb_data_type.hpp"
#include "wb_image_depth.hpp"
#include "wb_repository_type.hpp"
#include "errors.hpp"
#include "wb_defs.hpp"

class Image_header {
 private:
  int rows{};
  int cols{};
  int components{}; // we're only supported 1 grayscale component now
  WB_image_depth::Image_depth depth{};
  int min_row{};
  int min_col{};
  int rows_offset{};
  int cols_offset{};
  int row_stride{};
  int npixels{};

 public:
  Image_header();
  Image_header(int m_rows,
               int m_cols,
               int m_components,
               WB_image_depth::Image_depth m_depth);
  Image_header(int m_rows,
               int m_cols,
               int m_components,
               WB_image_depth::Image_depth m_depth,
               int m_min_row,
               int m_min_col,
               int m_rows_offset,
               int m_cols_offset);
  Image_header(Image_header &image_header);
  inline int get_rows() const { return rows; }
  inline int get_cols() const { return cols; }
  inline int get_components() const { return components; }
  inline WB_image_depth::Image_depth get_depth() const { return depth; }
  inline int get_min_row() const { return min_row; }
  inline int get_min_col() const { return min_col; }
  inline int get_rows_offset() const { return rows_offset; }
  inline int get_cols_offset() const { return cols_offset; }
  inline int get_row_stride() const { return row_stride; }
  inline int get_npixels() const { return npixels; }
  void read(FILE *fp, Errors &errors);
  void set_min_row(int m_min_row);
  void set_min_col(int m_min_col);
  void set_rows_offset(int m_rows_offset);
  void set_cols_offset(int m_cols_offset);
  void write(FILE *fp, Errors &errors) const;
  std::string to_string(const std::string &prefix = "") const;
};

#endif //CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
