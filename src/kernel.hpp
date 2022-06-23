//
// Created by kushn on 6/16/2022.
//

#ifndef CV_WORKBENCH_SRC_KERNEL_HPP_
#define CV_WORKBENCH_SRC_KERNEL_HPP_

#include "image.hpp"
#include "wb_defs.hpp"

class Kernel {
 public:
  int kernel_rows;
  int kernel_cols;
  Cv_image_depth_enum depth;
  int size;

  // image stores one buffer per image_header->depth
  pixel_32S *buf_32S;
  pixel_32F *buf_32F;

  ~Kernel();
  Kernel(int m_kernel_rows, int m_kernel_cols, Cv_image_depth_enum m_depth);
  static Kernel *create_32S(int kernel_rows, int kernel_cols, pixel_32S *buf_32S);
  static Kernel *create_32F(int kernel_rows, int kernel_cols, pixel_32F *buf_32F);

  int row_col_to_index(int row, int col);

  pixel_32F get(int row, int col);
  pixel_32S get_32S(int row, int col);
  pixel_32S get_32F(int row, int col);

  void set(int row, int col, pixel_32F value);
  void set_32S(int row, int col, pixel_32S value);
  void set_32F(int row, int col, pixel_32F value);

  void add_32S(pixel_32S *src, int count);
  void add_32F(pixel_32F *src, int count);

  Image *convolve(Image *src);

  string toString();
};

#endif //CV_WORKBENCH_SRC_KERNEL_HPP_
