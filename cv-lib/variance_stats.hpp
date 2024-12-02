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
  int count{};
  double mean{};
  double M2{};
  double variance{};
  double sample_variance{};
  double standard_deviation{};
  Bounds bounds;

  Variance_stats();
  void finalize();
  int get_count() const;
  double get_max_value() const;
  double get_mean();
  double get_min_value() const;
  double get_sample_variance();
  double get_standard_deviation();
  double get_variance();
  bool is_valid() const;
  void read(FILE *fp, const std::string &path, Errors &errors);
  std::string to_string(const std::string &prefix = "");
  void update(double new_value);
  void write(FILE *fp, Errors &errors) const;
};

#endif //SRC__VARIANCE_STATS_HPP_
