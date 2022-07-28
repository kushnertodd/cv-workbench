//
// Created by kushn on 6/16/2022.
//

#ifndef CV_WORKBENCH_SRC_KERNEL_HPP_
#define CV_WORKBENCH_SRC_KERNEL_HPP_

#include "image.hpp"
#include "wb_defs.hpp"

/**
 * Kernel class
 * Supports convolution of rectangular image filters
 * Some convolution kernels are separable, e.g., Sobel (http://www.k-zone.nl/Kroon_DerivativePaper.pdf),
 * Gaussian (http://www-edlab.cs.umass.edu/~smaji/cmpsci370/slides/hh/lec02_hh_advanced_edges.pdf),
 * but few enough that specially implementing them is not necessarily useful.
 */
class Kernel {
 public:
  int kernel_rows;
  int kernel_cols;
  CV_image_depth::Image_depth depth;
  int size;

  // image stores one buffer per image_header->depth
  pixel_32S *buf_32S;
  pixel_32F *buf_32F;

  ~Kernel();
  Kernel(int m_kernel_rows, int m_kernel_cols, CV_image_depth::Image_depth m_depth);

  void add_32S(const pixel_32S *src, int count) const;
  void add_32F(const pixel_32F *src, int count) const;

  Image *convolve(Image *src) const;

  static Kernel *create_32S(int kernel_rows, int kernel_cols, pixel_32S *buf_32S);
  static Kernel *create_32F(int kernel_rows, int kernel_cols, pixel_32F *buf_32F);

  double get(int row, int col) const;
  pixel_32F get_32F(int row, int col) const;
  pixel_32S get_32S(int row, int col) const;
  int get_kernel_rows();
  int get_kernel_cols();

  int row_col_to_index(int row, int col) const;

  void set(int row, int col, double value) const;
  void set_32F(int row, int col, pixel_32F value) const;
  void set_32S(int row, int col, pixel_32S value) const;

  std::string to_string() const;
};

#endif //CV_WORKBENCH_SRC_KERNEL_HPP_
