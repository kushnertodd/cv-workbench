//
// Created by kushn on 6/24/2022.
//

#ifndef SRC__VARIANCE_STATS_HPP_
#define SRC__VARIANCE_STATS_HPP_

#include <string>
#include "errors.hpp"
#include "bounds.hpp"

//

/**
 * Welford's single pass online algorithm for calculating variance
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
 * https://dbs.ifi.uni-heidelberg.de/files/Team/eschubert/publications/SSDBM18-covariance-authorcopy.pdf
 */
class Variance_stats {
 public:
  int count;
  double mean;
  double M2;
  double variance;
  double sample_variance;
  Bounds bounds;

  Variance_stats();
  void update(double new_value);
  bool is_valid();
  void finalize();
  double get_mean();
  double get_variance();
  double get_sample_variance();
  double get_standard_deviation();
  std::string to_string();
  void write(FILE *fp, std::string path, Errors &errors);
};

#endif //SRC__VARIANCE_STATS_HPP_
