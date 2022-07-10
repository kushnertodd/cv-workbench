//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_HISTOGRAM_HPP_
#define CV_WORKBENCH_SRC_HISTOGRAM_HPP_

#include "variance_stats.hpp"
#include "errors.hpp"


class Histogram {
 public:
  int *bins;
  int nbins;
  float min_value;
  float max_value;
  Bounds* in_bounds;
  Variance_stats stats;

  ~Histogram();
  Histogram();
  Histogram(int m_nbins,
  float m_min_value,
  float m_max_value);
  void update(double new_value);
  void finalize();
  bool read(std::ifstream &ifs, Errors &errors);
  void write(std::string path, std::string delim, Errors &errors);
  std::string to_string();
  void write(std::string path, Errors &errors);
  void write_string(std::string path, std::string delim, Errors &errors);
};

#endif //CV_WORKBENCH_SRC_HISTOGRAM_HPP_
