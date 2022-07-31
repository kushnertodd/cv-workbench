//
// Created by kushn on 6/16/2022.
//

#include <iostream>
#include <sstream>
#include "wb_utils.hpp"
#include "kernel.hpp"

extern bool debug;

Kernel::~Kernel() {
  delete[] buf_32S;
  delete[] buf_32F;
}

Kernel::Kernel(int m_kernel_rows, int m_kernel_cols, WB_image_depth::Image_depth m_depth) :
    kernel_rows(m_kernel_rows),
    kernel_cols(m_kernel_cols),
    depth(m_depth),
    size(kernel_rows * kernel_cols) {
  switch (depth) {
    case WB_image_depth::Image_depth::CV_32S:
      buf_32S = new pixel_32S[size];
      for (int i = 0; i < size; i++)
        buf_32S[i] = 0;
      break;

    case WB_image_depth::Image_depth::CV_32F:
      buf_32F = new pixel_32F[size];
      for (int i = 0; i < size; i++)
        buf_32F[i] = 0.0;
      break;

    default:
      break;
  }
}

void Kernel::add_32S(const pixel_32S *src, int count) const {
  for (int i = 0; i < count; i++) {
    buf_32S[i] = src[i];
  }
}

void Kernel::add_32F(const pixel_32F *src, int count) const {
  for (int i = 0; i < count; i++) {
    buf_32F[i] = src[i];
  }
}

Image *Kernel::convolve(Image *src) const {
  int src_rows = src->get_rows();
  int src_cols = src->get_cols();
  WB_image_depth::Image_depth src_depth = src->get_depth();
  int src_components = src->get_components();

  // output image is WB_image_depth::Image_depth::CV_32F if either the image and kernel are WB_image_depth::Image_depth::CV_32F, else it is WB_image_depth::Image_depth::CV_32S
  WB_image_depth::Image_depth out_depth =
      (src_depth == WB_image_depth::Image_depth::CV_32F || this->depth == WB_image_depth::Image_depth::CV_32F
       ? WB_image_depth::Image_depth::CV_32F : WB_image_depth::Image_depth::CV_32S);
  auto *out = new Image(src_rows, src_cols, src_components, out_depth);
  int rows_half = (kernel_rows + 1) / 2;
  int cols_half = (kernel_cols + 1) / 2;
  int row_lower = 0;
  int row_upper = src_rows - kernel_rows;
  int col_lower = 0;
  int col_upper = src_cols - kernel_cols;
  if (debug)
    std::cout << "rows_half " << rows_half
              << " cols_half " << cols_half
              << "row_lower " << row_lower
              << ", row_upper " << row_upper
              << ", col_lower " << col_lower
              << ", col_upper " << col_upper << std::endl;
  int kernel_row_lower = 0;
  int kernel_row_upper = kernel_rows - 1;
  int kernel_col_lower = 0;
  int kernel_col_upper = kernel_cols - 1;
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
          sum += kernel_val * image_val;
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

Kernel *Kernel::create_32S(int kernel_rows, int kernel_cols, pixel_32S *buf_32S) {
  auto *kernel = new Kernel(kernel_rows, kernel_cols, WB_image_depth::Image_depth::CV_32S);
  kernel->add_32S(buf_32S, kernel->size);
  return kernel;
}

Kernel *Kernel::create_32F(int kernel_rows, int kernel_cols, pixel_32F *buf_32F) {
  auto *kernel = new Kernel(kernel_rows, kernel_cols, WB_image_depth::Image_depth::CV_32F);
  kernel->add_32F(buf_32F, kernel->size);
  return kernel;
}

double Kernel::get(int row, int col) const {
  switch (depth) {
    case WB_image_depth::Image_depth::CV_32S:
      return buf_32S[row_col_to_index(row, col)];

    case WB_image_depth::Image_depth::CV_32F:
      return buf_32F[row_col_to_index(row, col)];

    default:
      return 0.0;
  }
}

pixel_32S Kernel::get_32S(int row, int col) const {
  return wb_utils::round_float_to_int(buf_32F[row_col_to_index(row, col)]);
}

pixel_32F Kernel::get_32F(int row, int col) const {
  return buf_32F[row_col_to_index(row, col)];
}

int Kernel::get_kernel_rows() const {
  return kernel_rows;
}

int Kernel::get_kernel_cols() const {
  return kernel_cols;
}

int Kernel::row_col_to_index(int row, int col) const {
  return row * kernel_rows + col;
}

void Kernel::set(int row, int col, double value) const {
  switch (depth) {

    case WB_image_depth::Image_depth::CV_32S:
      buf_32S[row_col_to_index(row, col)] = wb_utils::round_double_to_int(value);
      break;

    case WB_image_depth::Image_depth::CV_32F:
      buf_32F[row_col_to_index(row, col)] = wb_utils::double_to_float(value);
      break;

    default:
      break;
  }
}

void Kernel::set_32S(int row, int col, pixel_32S value) const {
  buf_32F[row_col_to_index(row, col)] = wb_utils::int_to_float(value);
}

void Kernel::set_32F(int row, int col, pixel_32F value) const {
  buf_32F[row_col_to_index(row, col)] = value;
}

std::string Kernel::to_string() const {
  std::ostringstream os;
  os << "kernel_rows " << kernel_rows
     << " kernel_cols " << kernel_cols
     << " depth " << " " << WB_image_depth::to_string(depth)
     << " size " << size;
  return os.str();
}