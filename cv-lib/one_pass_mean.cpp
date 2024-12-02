//
// Created by kushn on 8/23/2022.
//

#include <cassert>
#include <cmath>
#include "one_pass_mean.hpp"

One_pass_mean::One_pass_mean(Image *m_image, int m_window_rows, int m_window_cols) :
    image(m_image),
    window_rows(m_window_rows),
    window_cols(m_window_cols),
    image_rows(image->get_rows()),
    image_cols(image->get_cols()),
    n_image_pixels(image->get_npixels()),
    n_window_pixels(window_rows * window_cols),
    row_delta(std::round((window_rows - 1) / 2.0)),
    col_delta(std::round((window_cols - 1) / 2.0)) {
  init();
}

void One_pass_mean::col_right() {
  int next_col = left_col + window_cols;
  if (next_col < image_cols) {
    double next_col_sum = sum_col(top_row, next_col);
    window_sum += next_col_sum - left_col_sum;
    left_col++;
    left_col_sum = sum_col(top_row, left_col);
  }
}

double One_pass_mean::get_mean() {
  return window_sum / n_window_pixels;
}

void One_pass_mean::init() {
  top_row = 0;
  left_col = 0;
  top_row_sum = sum_row(0, 0);
  far_left_col_sum = sum_col(0, 0);
  left_col_sum = far_left_col_sum;
  left_window_sum = sum_window(0, 0);
  window_sum = left_window_sum;
}

/**
 * shift window down one row
 * always occurs when window is at the first column.
 */
void One_pass_mean::row_down() {
  int next_row = top_row + window_rows;
  left_col = 0;
  if (next_row < image_rows) {
    double first_left_column_pixel = image->get(top_row, left_col);
    double next_left_column_pixel = image->get(next_row, left_col);
    far_left_col_sum = far_left_col_sum + next_left_column_pixel - first_left_column_pixel;
    left_col_sum = far_left_col_sum;
    double next_row_sum = sum_row(next_row, 0);
    left_window_sum += next_row_sum - top_row_sum;
    window_sum = left_window_sum;
    top_row++;
    top_row_sum = sum_row(top_row, 0);
  }
}

double One_pass_mean::sum_col(int row, int col) {
  double sum = 0.0;
  for (int i = 0; i < window_rows; i++)
    sum += image->get(row + i, col);
  return sum;
}

double One_pass_mean::sum_row(int row, int col) {
  double sum = 0.0;
  for (int j = 0; j < window_cols; j++)
    sum += image->get(row, col + j);
  return sum;
}

double One_pass_mean::sum_window(int row, int col) {
  double sum = 0.0;
  for (int i = 0; i < window_rows; i++)
    for (int j = 0; j < window_cols; j++)
      sum += image->get(row + i, col + j);
  return sum;
}


