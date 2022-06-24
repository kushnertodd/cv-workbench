//
// Created by kushn on 6/16/2022.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "wb_utils.hpp"
#include "kernel.hpp"

extern bool debug;

Kernel::~Kernel() {
  if (buf_32S = nullptr) {
    delete[] buf_32S;
  }
  if (buf_32F = nullptr) {
    delete[] buf_32F;
  }
}

Kernel::Kernel(int m_kernel_rows, int m_kernel_cols, Cv_image_depth_enum m_depth) :
    kernel_rows(m_kernel_rows),
    kernel_cols(m_kernel_cols),
    depth(m_depth),
    size(kernel_rows * kernel_cols) {
  switch (depth) {
    case CV_32S:
      buf_32S = new pixel_32S[size];
      for (int i = 0; i < size; i++)
        buf_32S[i] = 0;
      break;

    case CV_32F:
      buf_32F = new pixel_32F[size];
      for (int i = 0; i < size; i++)
        buf_32F[i] = 0.0;
      break;

    default:
      break;
  }
}

Kernel *Kernel::create_32S(int kernel_rows, int kernel_cols, pixel_32S *buf_32S) {
  Kernel *kernel = new Kernel(kernel_rows, kernel_cols, CV_32S);
  kernel->add_32S(buf_32S, kernel->size);
  return kernel;
}

Kernel *Kernel::create_32F(int kernel_rows, int kernel_cols, pixel_32F *buf_32F) {
  Kernel *kernel = new Kernel(kernel_rows, kernel_cols, CV_32F);
  kernel->add_32F(buf_32F, kernel->size);
  return kernel;
}

int Kernel::row_col_to_index(int row, int col) {
  return row * kernel_rows + col;
}

pixel_32F Kernel::get(int row, int col) {
  switch (depth) {
    case CV_32S:
      return buf_32S[row_col_to_index(row, col)];

    case CV_32F:
      return buf_32F[row_col_to_index(row, col)];

    default:
      return 0.0;
  }
}

pixel_32S Kernel::get_32S(int row, int col) {
  return buf_32F[row_col_to_index(row, col)];
}

pixel_32S Kernel::get_32F(int row, int col) {
  return buf_32F[row_col_to_index(row, col)];
}

void Kernel::set(int row, int col, pixel_32F value) {
  switch (depth) {

    case CV_32S:
      buf_32S[row_col_to_index(row, col)] = value;
      break;

    case CV_32F:
      buf_32F[row_col_to_index(row, col)] = value;
      break;

    default:
      break;
  }
}

void Kernel::set_32S(int row, int col, pixel_32S value) {
  buf_32F[row_col_to_index(row, col)] = value;
}

void Kernel::set_32F(int row, int col, pixel_32F value) {
  buf_32F[row_col_to_index(row, col)] = value;
}

void Kernel::add_32S(pixel_32S *src, int count) {
  for (int i = 0; i < count; i++) {
    buf_32S[i] = src[i];
  }
}

void Kernel::add_32F(pixel_32F *src, int count) {
  for (int i = 0; i < count; i++) {
    buf_32F[i] = src[i];
  }
}

Image *Kernel::convolve(Image *src) {
  Image_header *header = src->image_header;
  int rows = header->rows;
  int cols = header->cols;

  // output image is CV_32F if either the image and kernel are CV_32F, else it is CV_32S
  Cv_image_depth_enum out_depth = (header->depth == CV_32F || depth == CV_32F ? CV_32F : CV_32S);
  Image *out = new Image(header->rows, header->cols,
                         header->components, out_depth);
  int rows_half = (kernel_rows + 1) / 2;
  int cols_half = (kernel_cols + 1) / 2;
  int row_lower = 0;
  int row_upper = rows - kernel_rows;
  int col_lower = 0;
  int col_upper = cols - kernel_cols;
  //printf("row_lower %d, row_upper %d, col_lower %d, col_upper %d\n", row_lower, row_upper, col_lower, col_upper);
  if (debug)
    cout << "rows_half " << rows_half
         << " cols_half " << cols_half
         << "row_lower " << row_lower
         << ", row_upper " << row_upper
         << ", col_lower " << col_lower
         << ", col_upper " << col_upper << endl;
  int kernel_row_lower = 0;
  int kernel_row_upper = kernel_rows - 1;
  int kernel_col_lower = 0;
  int kernel_col_upper = kernel_cols - 1;
  if (debug)
    cout << " kernel_row_lower " << kernel_row_lower
         << " kernel_row_upper " << kernel_row_upper
         << " kernel_col_lower " << kernel_col_lower
         << " kernel_col_upper " << kernel_col_upper << endl;
  for (int row = row_lower; row <= row_upper; row++) {
    int row_center = row + rows_half - 1;
    //printf("row %d row_center %d\n", row, row_center);
    if (debug)
      cout << "row " << row
           << " row_center " << row_center << endl;
    for (int col = col_lower; col <= col_upper; col++) {
      int col_center = col + cols_half - 1;
      //printf("  col %d, col_center %d\n", col, col_center);
//      int kernel_row_lower = row;
//      int kernel_row_upper = row + kernel_rows - 1;
      if (debug)
        cout << "col " << col
             << " col_center " << col_center
             //             << " kernel_row_lower " << kernel_row_lower
             //             << " kernel_row_upper " << kernel_row_upper
             << endl;
      float sum = 0.0;
      for (int i = kernel_row_lower; i <= kernel_row_upper; i++) {
//        int kernel_col_lower = col;
//        int kernel_col_upper = col + kernel_cols - 1;
        //printf("     ");
        for (int j = kernel_col_lower; j <= kernel_col_upper; j++) {
          float kernel_val = get(i, j);
          float image_val = src->get(row + i, col + j);
          sum += kernel_val * image_val;
          //printf("sum += kernel[%d,%d] %7.2f * image[%d,%d] %7.2f = %7.2f\n", i, j, kernel_val, row+i, col+j, image_val, sum);
          if (debug)
            cout << "sum += kernel[" << i << "," << j << "] " << kernel_val
                 << " * image[" << row + i << "," << col + j
                 << "] " << image_val << " = " << sum << endl;
        }
        if (debug)
          cout << endl;
      }
      //printf("buf[%d,%d] = %7.2f\n", row_center, col_center, sum);
      if (debug)
        cout << "buf[" << row_center << "," << col_center << "] = " << sum << endl;
      out->set(row_center, col_center, sum);
    }
  }
  return out;
}

string Kernel::to_string() {
  ostringstream os;
  os << "kernel_rows " << kernel_rows
     << " kernel_cols " << kernel_cols
     << " depth " << depth << " " << Workbench_utils::image_depth_enum_to_string(depth)
     << " size " << size;
  return os.str();
}