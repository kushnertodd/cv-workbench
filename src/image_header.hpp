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
  int row_origin{};
  int col_origin{};
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
               int m_row_origin,
               int m_col_origin,
               int m_rows_offset,
               int m_cols_offset);
  Image_header(Image_header &image_header);
  inline int get_rows() const { return rows; }
  inline int get_cols() const { return cols; }
  inline int get_components() const { return components; }
  inline WB_image_depth::Image_depth get_depth() const { return depth; }
  inline int get_row_origin() const { return row_origin; }
  inline int get_col_origin() const { return col_origin; }
  inline int get_rows_offset() const { return rows_offset; }
  inline int get_cols_offset() const { return cols_offset; }
  inline int get_row_stride() const { return row_stride; }
  inline int get_npixels() const { return npixels; }
  void read(FILE *fp, Errors &errors);
  inline void set_row_origin(int m_row_origin) { row_origin = m_row_origin; }
  inline void set_col_origin(int m_col_origin) { col_origin = m_col_origin; }
  inline void set_rows_offset(int m_rows_offset) { rows_offset = m_rows_offset; }
  inline void set_cols_offset(int m_cols_offset) { cols_offset = m_cols_offset; }
  void write(FILE *fp, Errors &errors) const;
  std::string to_string(const std::string &prefix = "") const;
};

#endif //CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
