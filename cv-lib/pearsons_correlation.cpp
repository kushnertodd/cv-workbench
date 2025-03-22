//
// Created by kushn on 8/23/2022.
//

#include <cmath>
#include "pearsons_correlation.hpp"

Pearsons_correlation::Pearsons_correlation(Image *m_image, Image *m_pattern) : image(m_image),
                                                                               pattern(m_pattern),
                                                                               image_rows(image->get_rows()),
                                                                               image_cols(image->get_cols()),
                                                                               pattern_rows(pattern->get_rows()),
                                                                               pattern_cols(pattern->get_cols()),
                                                                               opm(new One_pass_mean(
                                                                                   image, pattern_rows, pattern_cols)) {
    init_stats();
}

void Pearsons_correlation::init_stats() {
    sum_y = 0;
    sum_y_sq = 0;
    for (int row = 0; row < pattern_rows; row++)
        for (int col = 0; col < pattern_cols; col++) {
            double y = pattern->get(row, col);
            sum_y += y;
            sum_y_sq += y * y;
        }
}

/*
 * r = (n * sum(x * y) - sum(x) * sum(y)) /
 *       sqrt([n * sum(x^2) - sum(x)^2] * [n * sum(y^2) - sum(y)^2])
 */
double Pearsons_correlation::r(double n, double sum_x, double sum_xy, double sum_x_sq) {
    double coeff1 = n * sum_x_sq - sum_x * sum_x;
    double coeff2 = n * sum_y_sq - sum_y * sum_y;
    //if (std::abs(coeff1 * coeff2) < 0.0001) return 0.0;
    if (std::abs(coeff1) < 0.0001)
        return 0.0;
    double r = (n * sum_xy - sum_x * sum_y) / sqrt(coeff1); // / sqrt(coeff1 * coeff2);
    return r;
}

double Pearsons_correlation::accumulate(int ulc_row, int ulc_col) {
    double sum_x = 0.0;
    double sum_xy = 0.0;
    double sum_x_sq = 0.0;
    for (int row = 0; row < pattern_rows; row++) {
        for (int col = 0; col < pattern_cols; col++) {
            double x = image->get(ulc_row + row, ulc_col + col);
            double y = pattern->get(row, col);
            sum_x += x;
            sum_x_sq += x * x;
            sum_xy += x * y;
        }
    }
    return r(pattern->get_npixels(), sum_x, sum_xy, sum_x_sq);
}

Image *Pearsons_correlation::correlate() {
    auto *output = new Image(image->get_rows(), image->get_rows(), 1, Image_depth::CV_32F);
    for (int row = 0; row <= image_rows - pattern_rows; row++) {
        for (int col = 0; col <= image_cols - pattern_cols; col++) {
            //double mean = opm->get_mean();
            double value = accumulate(row, col);
            output->set(row + opm->row_delta, col + opm->col_delta, value);
            opm->col_right();
        }
        opm->row_down();
    }
    return output;
}
