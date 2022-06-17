//
// Created by kushn on 6/16/2022.
//

#include <cstdio>
#include <cstdlib>
#include "image_header.hpp"
#include "kernel.hpp"

Kernel::~Kernel() {
  if (kernel != nullptr)
    delete kernel;
}

Kernel::Kernel(int m_kernel_rows, int m_kernel_cols) :
    kernel_rows(m_kernel_rows),
    kernel_cols(m_kernel_cols),
    size(kernel_rows * kernel_cols) {
  kernel = new float[size];
}

int Kernel::row_col_to_index(int row, int col) {
  return row * kernel_rows + col;
}

void Kernel::set(int row, int col, float value) {
  kernel[row_col_to_index(row, col)] = value;
}

float Kernel::get(int row, int col) {
  return kernel[row_col_to_index(row, col)];
}

Image *Kernel::convolve(Image *src) {
  Image_header *header = src->image_header;
  int rows = header->rows;
  int cols = header->cols;
  int components = header->components;
  Cv_image_depth_enum depth = header->depth;
  Image *out = new Image(header->rows, header->cols,
                         header->components, CV_32S);

  int rows_half = (kernel_rows + 1) / 2;
  int cols_half = (kernel_cols + 1) / 2;
  int row_lower = 0;
  int row_upper = rows - kernel_rows;
  int col_lower = 0;
  int col_upper = cols - kernel_cols;
  printf("row_lower %d, row_upper %d, col_lower %d, col_upper %d\n", row_lower, row_upper, col_lower, col_upper);
  for (int row = row_lower; row <= row_upper; row++) {
    int row_center = row + rows_half - 1;
    printf("row %d row_center %d\n", row, row_center);
    for (int col = col_lower; col <= col_upper; col++) {
      int col_center = col + cols_half - 1;
      printf("  col %d, col_center %d\n", col, col_center);
      int kernel_row_lower = row;
      int kernel_row_upper = row + kernel_rows - 1;
      float sum = 0.0;
      for (int i = kernel_row_lower; i <= kernel_row_upper; i++) {
        int kernel_col_lower = col;
        int kernel_col_upper = col + kernel_cols - 1;
        printf("     ");
        for (int j = kernel_col_lower; j <= kernel_col_upper; j++) {
          printf("(%d,%d) ", i, j);
          sum += get(i, j) * src->get_32F(row + i, col + j);
        }
        out->set_32F(row, col, sum);
        printf("\n");
      }
    }
  }
  return out;
}
