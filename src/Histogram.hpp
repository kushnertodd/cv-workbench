//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_HISTOGRAM_HPP_
#define CV_WORKBENCH_SRC_HISTOGRAM_HPP_

#include "errors.hpp"
#include "image.hpp"
#include "variance_stats.hpp"

class Histogram {
 public:
  Image *image;
  int *bins;
  int nbins;
  double lower_value;
  double upper_value;
  Variance_stats stats;

  ~Histogram();
  Histogram(Image *image,
            int m_nbins,
            double m_lower_value,
            double m_upper_value);
  int get_bin(double value) const;
  double get_lower_value() const;
  double get_max_value() const;
  double get_min_value() const;
  double get_upper_value() const;
  void initialize();
  void read(const std::string &path, Errors &errors);
  std::string to_string();
  void update(double new_value) const;
  void update_stats();
  void write(const std::string &path, Errors &errors);
  void write_text(const std::string &path, const std::string &delim, Errors &errors);
};

#endif //CV_WORKBENCH_SRC_HISTOGRAM_HPP_
