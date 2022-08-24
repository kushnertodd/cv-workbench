//
// Created by kushn on 8/23/2022.
//

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
 public:
  Image *image{};
  Kernel *pattern{};
  int image_rows{};
  int image_cols{};
  int pattern_rows{};
  int pattern_cols{};
  One_pass_mean *opm;
  Pearsons_correlation(Image *m_image, Kernel *m_pattern);
  Image *correlate();
};

#endif //SRC__PEARSONS_CORRELATION_H_
