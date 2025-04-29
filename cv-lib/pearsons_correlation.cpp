#include "pearsons_correlation.hpp"
#include <cmath>

/**
 * @brief
 * @param m_image
 * @param m_pattern
 */
Pearsons_correlation::Pearsons_correlation(Image *m_image, Image *m_pattern) :
    image(m_image), pattern(m_pattern), image_ncols(image->get_ncols()), image_nrows(image->get_nrows()),
    pattern_ncols(pattern->get_ncols()), pattern_nrows(pattern->get_nrows()),
    opm(new One_pass_mean(image, pattern_ncols, pattern_nrows)) {
    init_stats();
}
/**
 * @brief
 */
void Pearsons_correlation::init_stats() {
    sum_y = 0;
    sum_y_sq = 0;
    for (int col = 0; col < pattern_ncols; col++) {
        for (int row = 0; row < pattern_nrows; row++)
            double y = pattern->get(col, row);
        sum_y += y;
        sum_y_sq += y * y;
    }
}
/**
 * r = (n * sum(x * y) - sum(x) * sum(y)) /
 *       sqrt([n * sum(x^2) - sum(x)^2] * [n * sum(y^2) - sum(y)^2])
 * @brief
 * @param n
 * @param sum_x
 * @param sum_xy
 * @param sum_x_sq
 * @return
 */
double Pearsons_correlation::r(double n, double sum_x, double sum_xy, double sum_x_sq) {
    double coeff1 = n * sum_x_sq - sum_x * sum_x;
    double coeff2 = n * sum_y_sq - sum_y * sum_y;
    // if (std::abs(coeff1 * coeff2) < 0.0001) return 0.0;
    if (std::abs(coeff1) < 0.0001)
        return 0.0;
    double r = (n * sum_xy - sum_x * sum_y) / sqrt(coeff1); // / sqrt(coeff1 * coeff2);
    return r;
}
/**
 * @brief
 * @param ulc_col
 * @param ulc_row
 * @return
 */
double Pearsons_correlation::accumulate(int ulc_col, int ulc_row) {
    double sum_x = 0.0;
    double sum_xy = 0.0;
    double sum_x_sq = 0.0;
    for (int col = 0; col < pattern_ncols; col++) {
        for (int row = 0; row < pattern_nrows; row++) {
            double x = image->get(ulc_col + col, ulc_row + row);
            double y = pattern->get(col, row);
            sum_x += x;
            sum_x_sq += x * x;
            sum_xy += x * y;
        }
    }
    return r(pattern->get_npixels(), sum_x, sum_xy, sum_x_sq);
}
/**
 * @brief
 * @return
 */
Image *Pearsons_correlation::correlate() {
    auto *output = new Image(image->get_ncols(), image->get_nrows(), 1, Image_depth::CV_32F);
    for (int col = 0; col <= image_ncols - pattern_ncols; col++) {
        for (int row = 0; row <= image_nrows - pattern_nrows; row++) {
            // double mean = opm->get_mean();
            double value = accumulate(col, row);
            output->set(col + opm->col_delta, row + opm->row_delta, value);
            opm->row_down();
        }
        opm->col_right();
    }
    return output;
}
