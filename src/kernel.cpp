//
// Created by kushn on 6/16/2022.
//

#include <iostream>
#include "wb_morphology_types.hpp"
#include "kernel.hpp"

extern bool debug;

Kernel::~Kernel() = default;

Kernel::Kernel() = default;

Kernel::Kernel(int rows, int cols, WB_image_depth::Image_depth depth) :
  Image(rows, cols, 1, depth) {
  init();
}

Image *Kernel::convolve(Image *src, WB_morphology_types::Convolution_type convolution_type) const {
  int src_rows = src->get_rows();
  int src_cols = src->get_cols();
  WB_image_depth::Image_depth src_depth = src->get_depth();
  int src_components = src->get_components();
  int rows = get_rows();
  int cols = get_cols();
  WB_image_depth::Image_depth depth = get_depth();

  // output image is WB_image_depth::Image_depth::CV_32F if either the image and kernel are WB_image_depth::Image_depth::CV_32F, else it is WB_image_depth::Image_depth::CV_32S
  WB_image_depth::Image_depth out_depth =
    (src_depth == WB_image_depth::Image_depth::CV_32F || depth == WB_image_depth::Image_depth::CV_32F
     ? WB_image_depth::Image_depth::CV_32F : WB_image_depth::Image_depth::CV_32S);
  auto *out = new Image(src_rows, src_cols, src_components, out_depth);
  int rows_half = (rows + 1) / 2;
  int cols_half = (cols + 1) / 2;
  int row_lower = 0;
  int row_upper = src_rows - rows;
  int col_lower = 0;
  int col_upper = src_cols - cols;
  if (debug)
    std::cout << "rows_half " << rows_half
              << " cols_half " << cols_half
              << " row_lower " << row_lower
              << ", row_upper " << row_upper
              << ", col_lower " << col_lower
              << ", col_upper " << col_upper << std::endl;
  int kernel_row_lower = 0;
  int kernel_row_upper = rows - 1;
  int kernel_col_lower = 0;
  int kernel_col_upper = cols - 1;
  if (debug)
    std::cout << " kernel_row_lower " << kernel_row_lower
              << " kernel_row_upper " << kernel_row_upper
              << " kernel_col_lower " << kernel_col_lower
              << " kernel_col_upper " << kernel_col_upper << std::endl;
  for (int row = row_lower; row <= row_upper; row++) {
    int row_center = row + rows_half - 1;
    if (debug)
      std::cout << "row " << row
                << " row_center " << row_center << std::endl;
    for (int col = col_lower; col <= col_upper; col++) {
      int col_center = col + cols_half - 1;
      if (debug)
        std::cout << "col " << col
                  << " col_center " << col_center
                  << std::endl;
      double sum = 0.0;
      for (int i = kernel_row_lower; i <= kernel_row_upper; i++) {
        for (int j = kernel_col_lower; j <= kernel_col_upper; j++) {
          double kernel_val = get(i, j);
          double image_val = src->get(row + i, col + j);
          switch (convolution_type) {
          case WB_morphology_types::Convolution_type::NUMERIC:
            sum += kernel_val * image_val;
            break;
          case WB_morphology_types::Convolution_type::ERODE:
            if (kernel_val > 0)
              sum = std::min(sum, image_val);
            break;
          case WB_morphology_types::Convolution_type::DILATE:
            if (kernel_val > 0)
              sum = std::max(sum, image_val);
            break;
          default:
            break;
          }
          if (debug)
            std::cout << "sum += kernel[" << i << "," << j << "] " << kernel_val
                      << " * image[" << row + i << "," << col + j
                      << "] " << image_val << " = " << sum << std::endl;
        }
        if (debug)
          std::cout << std::endl;
      }
      if (debug)
        std::cout << "buf[" << row_center << "," << col_center << "] = " << sum << std::endl;
      out->set(row_center, col_center, sum);
    }
  }
  return out;
}

Kernel *Kernel::create_32S(int rows, int cols, const pixel_32S *buf_32S) {
  auto *kernel = new Kernel(rows, cols, WB_image_depth::Image_depth::CV_32S);
  for (int i = 0; i < kernel->get_npixels(); i++) {
    kernel->buf_32S[i] = buf_32S[i];
  }
  return kernel;
}

Kernel *Kernel::create_32F(int rows, int cols, const pixel_32F *buf_32F) {
  auto *kernel = new Kernel(rows, cols, WB_image_depth::Image_depth::CV_32F);
  for (int i = 0; i < kernel->get_npixels(); i++) {
    kernel->buf_32F[i] = buf_32F[i];
  }
  return kernel;
}

Kernel *Kernel::create_structuring_element(WB_morphology_types::Structuring_element_type structuring_element_type,
    int rows, int cols, int thickness) {
  auto *kernel = new Kernel(rows, cols, WB_image_depth::Image_depth::CV_8U);
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      switch (structuring_element_type) {
      case WB_morphology_types::Structuring_element_type::RECTANGLE:
        kernel->set_8U(row, col, 1);
        break;
      case WB_morphology_types::Structuring_element_type::CROSS: {
        double x = Point::col_to_x(col, cols);
        double y = Point::row_to_y(row, rows);
        if (std::abs(x) <= thickness / 2.0 || std::abs(y) <= thickness / 2.0)
          kernel->set_8U(row, col, 1);
        break;
      }
      case WB_morphology_types::Structuring_element_type::ELLIPSE:
        if (Point::in_ellipse(row, col, rows, cols))
          kernel->set_8U(row, col, 1);
        break;
      default:
        break;
      }
    }
  }
  return kernel;
}
