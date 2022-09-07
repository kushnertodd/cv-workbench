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

/**
 * Contains metrics for image, including subimage.
 * Subimages only exist in memory. They make an image appear as if
 * it is only the subimage. They are used when processing or
 * copying data out of the image. The subimage use case is:
 * - read an image
 * - set a subimage
 * - copy the subimage data to an output image
 * - write the output image
 * The image with a subimage is not intended to be written out.
 * Writing it writes out the entire image.
 */
class Image_header {
 private:
  // image pixel height
  int rows{};
  // image pixel width
  int cols{};
  // number of colors; we're only supported 1 grayscale component now
  int components{};
  // pixel primitive type and bit count
  WB_image_depth::Image_depth depth{};
  // subimage start row
  int min_row{};
  // subimage start column
  int min_col{};
  // subimage end row
  int max_row{};
  // subimage end row
  int max_col{};
  // pixels are stored continuously in blocks; the number of pixels to skip for a row
  int row_stride{};
  // the number of float, int, or unsigned byte pixel values = rows * cols * components
  int npixels{};
  // the number of 1-3 channel elements = rows * cols
  int nelements{};

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
               int m_max_row,
               int m_max_col);
  Image_header(Image_header &image_header);
  inline int get_rows() const { return rows; }
  inline int get_cols() const { return cols; }
  inline int get_components() const { return components; }
  inline WB_image_depth::Image_depth get_depth() const { return depth; }
  inline int get_min_row() const { return min_row; }
  inline int get_min_col() const { return min_col; }
  inline int get_max_row() const { return max_row; }
  inline int get_max_col() const { return max_col; }
  inline int get_row_stride() const { return row_stride; }
  inline int get_npixels() const { return npixels; }
  inline int get_nelements() const { return nelements; }
  void read(FILE *fp, Errors &errors);
  void set_min_row(int m_min_row);
  void set_min_col(int m_min_col);
  void set_max_row(int m_max_row);
  void set_max_col(int m_max_col);
  void write(FILE *fp, Errors &errors) const;
  std::string to_string(const std::string &prefix = "") const;
};

#endif //CV_WORKBENCH_SRC_IMAGE_HEADER_HPP_
