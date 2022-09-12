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
  Polar_line polar_line;
  int count{};
  int total_difference{};
  double percent_difference{};
  Variance_stats count_stats;
  Variance_stats total_difference_stats;
  Variance_stats percent_difference_stats;
 public:
  ~Hough_peak();
  Hough_peak() = default;
  Hough_peak(double m_rho,
             int m_theta,
             int m_nrhos,
             int m_count,
             int m_total_difference,
             float m_percent_difference);
  Hough_peak(Polar_line &m_polar_line,
             int m_count,
             int m_total_difference,
             float m_percent_difference);
  Hough_peak(Polar_line &m_polar_line);

  static Hough_peak *from_rho_theta_index(double rho,
                                          int theta_index,
                                          int count,
                                          int total_difference,
                                          float percent_difference);
  static Hough_peak *from_rho_index_theta_index(int rho_index,
                                                int theta_index,
                                                int nrhos,
                                                int count,
                                                int total_difference,
                                                float percent_difference);
  static Hough_peak *from_rho_theta(int rho,
                                    int theta,
                                    int count,
                                    int total_difference,
                                    float percent_difference);
  static Hough_peak *from_rho_index_theta(int rho_index,
                                          int theta,
                                          int nrhos,
                                          int count,
                                          int total_difference,
                                          float percent_difference);

  inline int get_count() const { return count; }
  inline double get_nrhos() const { return polar_line.get_nrhos(); }
  inline double get_percent_difference() const { return percent_difference; }
  inline int get_rho() const { return polar_line.get_rho(); }
  inline int get_rho_index() const { return polar_line.get_rho_index(); }
  inline int get_theta() const { return polar_line.get_theta(); }
  inline int get_theta_index() const { return polar_line.get_theta_index(); }
  inline int get_total_difference() const { return total_difference; }

  static void read(const std::string &path, std::vector<Hough_peak> &peaks, Errors &errors);
  static void read(FILE *fp, std::vector<Hough_peak> &peaks, Errors &errors);
  void read(FILE *fp, Errors &errors);
  static void read_text(const std::string &path, std::vector<Hough_peak> &peaks, Errors &errors);
  static void read_text(std::ifstream &ifs, std::vector<Hough_peak> &peaks, Errors &errors);

  inline void set_count(int m_count) { count = m_count; }
  inline void set_nrhos(int m_nrhos) { polar_line.set_nrhos(m_nrhos); }
  inline void set_percent_difference(double m_percent_difference) { percent_difference = m_percent_difference; }
  inline void set_rho(double m_rho) { polar_line.set_rho(m_rho); }
  inline void set_rho_index(double rho_index) { polar_line.set_rho_index(rho_index); }
  inline void set_theta(int m_theta) { polar_line.set_theta(m_theta); }
  inline void set_theta_index(int theta_index) { polar_line.set_theta_index(theta_index); }
  inline void set_total_difference(int m_total_difference) { total_difference = m_total_difference; }

  static void write(const std::string &path, std::vector<Hough_peak> &peaks, Errors &errors);
  static void write(FILE *fp, std::vector<Hough_peak> &peaks, Errors &errors);

  void write(const std::string &path, Errors &errors);
  void write(FILE *fp, Errors &errors);

  static void write_text(const std::string &path, std::vector<Hough_peak> &peaks, Errors &errors);
  static void write_text(std::ofstream &ofs, std::vector<Hough_peak> &peaks, Errors &errors);
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;

};

#endif //CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_
