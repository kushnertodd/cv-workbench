//
// Created by kushn on 6/16/2022.
//

#ifndef CV_WORKBENCH_SRC_KERNEL_HPP_
#define CV_WORKBENCH_SRC_KERNEL_HPP_

#include "image.hpp"

class Kernel {
 public:
  int kernel_rows;
int kernel_cols;
int size;
float *kernel;
~Kernel();
Kernel(int m_rows, int m_cols);
int row_col_to_index(int row, int col);
void set(int row, int col, float value);
float get(int row, int col);
Image* convolve(Image* src);
};

#endif //CV_WORKBENCH_SRC_KERNEL_HPP_
