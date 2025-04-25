//
// Created by kushn on 8/23/2022.
//

#ifndef SRC__ONE_PASS_MEAN_H_
#define SRC__ONE_PASS_MEAN_H_

#include "image.hpp"

/** Compute mean of image window in one pass. this is particularly used for
 * computing the Pearson's correlation coefficient for matching a template
 * against the image, where the mean is used in aggregating each pixel value
 * during a convolution. Computing the mean on the fly avoids making a second
 * pass to compute the mean first.
 *
 * The computation updates the window mean variables as the window is shifted
 * right and down during a convolution.
 *
 * Initialization:
 * - compute the initial window sum (row = col = 0)
 * - compute the top row sum
 * - compute the left column sum
 *
 *  @image html cv-workbench_one_pass_mean_init.jpg
 *
 * On shifting down:
 * - subtracts the top row sum and adds the next row sum from the running window sum
 * - creates a new top row sum from the next top row
 * - updates the left column sum for it shifting down
 *
 * @image html cv-workbench_one_pass_mean_row_down.jpg
 *
 * On shifting right:
 * - subtracts the left column sum and adds the next column sum from the running window sum
 * - creates a new left column sum from the next left column
 *
 * @image html cv-workbench_row_pass_mean_column_right.jpg
 *
 * At any time, get_mean() can give the current running mean.
 */
class One_pass_mean {
 public:
  Image *image{};
  int window_rows{};
  int window_cols{};
  int image_rows{};
  int image_cols{};
  int n_image_pixels{};
  int n_window_pixels{};
  int row_delta{};
  int col_delta{};
  double left_window_sum{};
  double window_sum{};
  int top_row{};
  int left_col{};
  double top_row_sum{};
  double left_col_sum{};
  double far_left_col_sum{};

  One_pass_mean(Image *m_image, int m_window_rows, int m_window_cols);

  void col_right();
  double get_mean();
  void init();
  void row_down();
  double sum_col(int col, int row);
  double sum_row(int col, int row);
  double sum_window(int col, int row);
};

#endif //SRC__ONE_PASS_MEAN_H_
