//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_
#define CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_

#include <string>
#include "polar_line.hpp"
#include "variance_stats.hpp"

class Hough_peak {
 private:
  //int theta{};
  //double rho{};
  int count{};
  Polar_line *polar_line{};
  int total_difference{};
  double percent_difference{};
  Variance_stats count_stats;
  Variance_stats total_difference_stats;
  Variance_stats percent_difference_stats;
 public:
  ~Hough_peak();
  Hough_peak() = default;
  Hough_peak(int m_theta,
             double m_rho,
             int m_count,
             int m_total_difference,
             float m_percent_difference);
  Hough_peak(int m_theta,
             double m_rho);
  static  Hough_peak *from_theta_index_rho(int theta_index,
                                                  double rho,
                                                  int count,
                                                  int total_difference,
                                                  float percent_difference);
  static  Hough_peak *from_theta_index_rho_index(int theta_index,
                                         int rho_index,
                                         int nrhos,
                                         int count,
                                         int total_difference,
                                         float percent_difference);
  static  Hough_peak *from_theta_rho(int theta,
                                                  int rho,
                                                  int count,
                                                  int total_difference,
                                                  float percent_difference);
  static  Hough_peak *from_theta_rho_index(int theta,
                                                  int rho_index,
                                                  int nrhos,
                                                  int count,
                                                  int total_difference,
                                                  float percent_difference);

  inline int get_count() const { return count; }
  inline double get_percent_difference() const { return percent_difference; }
  inline int get_rho() const { return rho; }
  int get_rho_index(int nrhos) const;
   int get_theta_index() const;
   inline
  inline int get_total_difference() const { return total_difference; }
  static Hough_peak *read(const std::string &path, Errors &errors);
  static Hough_peak *read(FILE *fp, Errors &errors);
  inline void set_count(int m_count) { count = m_count; }
  inline void set_percent_difference(double m_percent_difference) { percent_difference = m_percent_difference; }
  inline void set_rho(double m_rho) { rho = m_rho; }
  void set_rho(int rho_index, int nrhos);
  inline void set_theta(int m_theta) { theta = m_theta; }
  inline void set_total_difference(int m_total_difference) { total_difference = m_total_difference; }
  void write(const std::string &path, Errors &errors) const;
  void write(FILE *fp, Errors &errors) const;
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};

#endif //CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_
