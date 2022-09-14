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
  int count{};
  int total_difference{};
  double percent_difference{};
  Variance_stats count_stats;
  Variance_stats total_difference_stats;
  Variance_stats percent_difference_stats;
 public:
  Polar_line polar_line;
  ~Hough_peak();
  Hough_peak() = default;
  Hough_peak(Polar_line &m_polar_line,
             int m_count,
             int m_total_difference,
             float m_percent_difference);
  explicit Hough_peak(Polar_line &m_polar_line);

  inline int get_count() const { return count; }
  inline double get_percent_difference() const { return percent_difference; }
  inline double get_rho() const { return polar_line.get_rho(); }
  inline Theta get_theta() const { return polar_line.get_theta(); }
  inline int get_theta_degrees() const { return polar_line.get_theta_degrees(); }
  inline double get_theta_radians() const { return polar_line.get_theta_radians(); }
  inline int get_total_difference() const { return total_difference; }

  static void read(const std::string &path, std::list<Hough_peak> &hough_peaks, Errors &errors);
  static void read(FILE *fp, std::list<Hough_peak> &hough_peaks, Errors &errors);
  void read(FILE *fp, Errors &errors);
  static void read_text(const std::string &path, std::list<Hough_peak> &hough_peaks, Errors &errors);
  static void read_text(std::ifstream &ifs, std::list<Hough_peak> &hough_peaks, Errors &errors);

  inline void set_count(int m_count) { count = m_count; }
  inline void set_percent_difference(double m_percent_difference) { percent_difference = m_percent_difference; }
  inline void set_rho(double m_rho) { polar_line.set_rho(m_rho); }
  inline void set_theta(Theta theta) { polar_line.set_theta(theta); }
  inline void set_theta_degrees(int theta_degrees) { polar_line.set_theta_degrees(theta_degrees); }
  inline void set_theta_radians(int theta_radians) { polar_line.set_theta_radians(theta_radians); }
  inline void set_total_difference(int m_total_difference) { total_difference = m_total_difference; }

  static void write(const std::string &path, std::list<Hough_peak> &hough_peaks, Errors &errors);
  static void write(FILE *fp, std::list<Hough_peak> &hough_peaks, Errors &errors);
  void write(FILE *fp, Errors &errors);

  static void write_text(const std::string &path, std::list<Hough_peak> &hough_peaks, Errors &errors);
  static void write_text(std::ofstream &ofs, std::list<Hough_peak> &hough_peaks, const std::string &delim);
  void write_text(std::ofstream &ofs, const std::string &delim) const;
};

#endif //CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_
