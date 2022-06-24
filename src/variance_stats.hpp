//
// Created by kushn on 6/24/2022.
//

#ifndef SRC__VARIANCE_STATS_HPP_
#define SRC__VARIANCE_STATS_HPP_

#include <string>

using namespace std;

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
  double min_value;
  double max_value;

  Variance_stats();
  void update(double new_value);
  bool is_valid();
  void finalize();
  int get_count();
  double get_mean();
  double get_variance();
  double get_sample_variance();
  double get_standard_deviation();
  double get_min_value();
  double get_max_value();
  string to_string();
};

#endif //SRC__VARIANCE_STATS_HPP_
