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
  Bounds bounds;
  Variance_stats stats;

  ~Histogram();
  Histogram(int m_nbins,
            float m_min_value,
            float m_max_value);
  int get_bin(float value) const;
  float get_max_value() const;
  float get_min_value() const;
  static bool read(std::ifstream &ifs, Errors &errors);
  std::string to_string();
  void update(float new_value);
  void write(const std::string& path, Errors &errors);
  void write_text(const std::string& path, const std::string& delim, Errors &errors);
};

#endif //CV_WORKBENCH_SRC_HISTOGRAM_HPP_
