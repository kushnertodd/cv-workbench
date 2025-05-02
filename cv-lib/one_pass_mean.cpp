#include "one_pass_mean.hpp"
#include <cassert>
#include <cmath>

/**
 * @brief
 * @param m_image
 * @param m_window_ncols
 * @param m_window_nrows
 */
One_pass_mean::One_pass_mean(Image *m_image, int m_window_ncols, int m_window_nrows) :
    image(m_image), window_ncols(m_window_ncols), window_nrows(m_window_nrows), image_ncols(image->get_ncols()),
    image_nrows(image->get_nrows()), n_image_pixels(image->get_npixels()), n_window_pixels(window_ncols * window_nrows),
    col_delta(std::round((window_ncols - 1) / 2.0)), row_delta(std::round((window_nrows - 1) / 2.0)) {
    init();
}
/**
 * @brief
 */
void One_pass_mean::col_right() {
    int next_col = left_col + window_ncols;
    if (next_col < image_ncols) {
        double next_col_sum = sum_col(next_col, top_row);
        window_sum += next_col_sum - left_col_sum;
        left_col++;
        left_col_sum = sum_col(left_col, top_row);
    }
}
/**
 * @brief
 * @return
 */
int One_pass_mean::get_col_delta() { return col_delta; }
/**
 * @brief
 * @return
 */
double One_pass_mean::get_mean() const { return window_sum / n_window_pixels; }
/**
 * @brief
 * @return
 */
int One_pass_mean::get_row_delta() { return row_delta; }
/**
 * @brief
 */
void One_pass_mean::init() {
    left_col = 0;
    top_row = 0;
    far_left_col_sum = sum_col(0, 0);
    left_col_sum = far_left_col_sum;
    top_row_sum = sum_row(0, 0);
    left_window_sum = sum_window(0, 0);
    window_sum = left_window_sum;
}
/**
 * shift window down one row
 * always occurs when window is at the first column.
 */

/**
 * @brief
 */
void One_pass_mean::row_down() {
    int next_row = top_row + window_nrows;
    left_col = 0;
    if (next_row < image_nrows) {
        double first_left_column_pixel = image->get(left_col, top_row);
        double next_left_column_pixel = image->get(left_col, next_row);
        far_left_col_sum = far_left_col_sum + next_left_column_pixel - first_left_column_pixel;
        left_col_sum = far_left_col_sum;
        double next_row_sum = sum_row(next_row, 0);
        left_window_sum += next_row_sum - top_row_sum;
        window_sum = left_window_sum;
        top_row++;
        top_row_sum = sum_row(top_row, 0);
    }
}
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
double One_pass_mean::sum_col(int col, int row) const {
    double sum = 0.0;
    for (int i = 0; i < window_nrows; i++)
        sum += image->get(col, row + i);
    return sum;
}
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
double One_pass_mean::sum_row(int col, int row) const {
    double sum = 0.0;
    for (int j = 0; j < window_ncols; j++)
        sum += image->get(col, row + j);
    return sum;
}
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
double One_pass_mean::sum_window(int col, int row) const {
    double sum = 0.0;
    for (int j = 0; j < window_ncols; j++)
        for (int i = 0; i < window_nrows; i++)
            sum += image->get(col + j, row + i);
    return sum;
}
