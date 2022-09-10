//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_
#define CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_

#include <string>
#include "variance_stats.hpp"

class Hough_peak {
 private:
  int theta_index{};
  int rho_index{};
  int count{};
  int total_difference{};
  double percent_difference{};
  Variance_stats count_stats;
  Variance_stats total_difference_stats;
  Variance_stats percent_difference_stats;
 public:
  ~Hough_peak();
  Hough_peak() = default;
  Hough_peak(int m_theta_index,
             int m_rho_index,
             int m_count,
             int m_total_difference,
             float m_percent_difference);

  inline int get_theta_index() const { return theta_index; }
  inline int get_rho_index() const { return rho_index; }
  inline int get_count() const { return count; }
  inline int get_total_difference() const { return total_difference; }
  inline double get_percent_difference() const { return percent_difference; }
  static Hough_peak *read(const std::string &path, Errors &errors);
  static Hough_peak *read(FILE *fp, Errors &errors);
  inline void set_theta_index(int m_theta_index) { theta_index = m_theta_index; }
  inline void set_rho_index(int m_rho_index) { rho_index = m_rho_index; }
  inline void set_count(int m_count) { count = m_count; }
  inline void set_total_difference(int m_total_difference) { total_difference = m_total_difference; }
  inline void set_percent_difference(double m_percent_difference) { percent_difference = m_percent_difference; }
  void write(const std::string &path, Errors &errors) const;
  void write(FILE *fp, Errors &errors) const;
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};

#endif //CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_
