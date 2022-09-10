//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include <fstream>
#include "hough_peak.hpp"

class Polar_line {
 private:
  int rho_index{};
  double rho{};
  int theta_index{};
  int count{};
  double cos_theta{};
  double sin_theta{};
 public:
  Polar_line(int m_rho_index, double m_rho, int m_theta_index,
             double m_cos_theta, double m_sin_theta, int m_count);
  Polar_line(Hough_peak &hough_peak, int nrhos);

  inline double get_cos_theta() const { return cos_theta; }
  inline int get_count() const { return count; }
  inline double get_rho() const { return rho; }
  inline int get_rho_index() const { return rho_index; }
  inline double get_sin_theta() const { return sin_theta; }
  inline int get_theta_index() const { return theta_index; }
  void set(int m_rho_index, double m_rho, int m_theta_index,
           double m_cos_theta, double m_sin_theta, int m_count);
  inline void set_cos_theta(double m_cos_theta) { cos_theta = m_cos_theta; }
  inline void set_count(int m_count) { count = m_count; }
  inline void set_rho(double m_rho) { rho = m_rho; }
  inline void set_rho_index(int m_rho_index) { rho_index = m_rho_index; }
  inline void set_sin_theta(double m_sin_theta) { sin_theta = m_sin_theta; }
  inline void set_theta_index(int m_theta_index) { theta_index = m_theta_index; }
  std::string to_string() const;
  void write(FILE *fp, Errors &errors);
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};
#endif //SRC__POLAR_LINE_HPP_
