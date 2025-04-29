#ifndef SRC__PEARSONS_CORRELATION_H_
#define SRC__PEARSONS_CORRELATION_H_

#include "image.hpp"
#include "kernel.hpp"
#include "one_pass_mean.hpp"

/**
 * Computes a one-pass Pearson's correlation coefficient for matching a template against an image
 *
 * https://www.statisticshowto.com/probability-and-statistics/correlation-coefficient-formula/
 * pearson's correlation coefficient r formula:
 *
 * r = (n * sum(x * y) - sum(x) * sum(y)) /
 *       sqrt([n * sum(x^2) - sum(x)^2] * [n * sum(y^2) - sum(y)^2])
 */
class Pearsons_correlation {
    Image *image{};
    Image *pattern{};
    int image_ncols{};
    int image_nrows{};
    void init_stats();
    int pattern_ncols{};
    int pattern_nrows{};
    double sum_y{};
    double sum_y_sq{};
    One_pass_mean *opm{};

public:
    Pearsons_correlation(Image *m_image, Image *m_pattern);
    double accumulate(int ulc_col, int ulc_row);
    Image *correlate();
    double r(double n, double sum_x, double sum_xy, double sum_x_sq);
};

#endif // SRC__PEARSONS_CORRELATION_H_
