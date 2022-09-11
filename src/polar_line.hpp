//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include <fstream>
#include "hough_peak.hpp"
#include "polar_trig.hpp"

class Polar_line {
 private:
  double rho{};
  int rho_index{};
  int theta_index{};
 public:
  Polar_line(
      double m_rho,
      int m_rho_index,
      int m_theta_index);
static  Polar_line *from_theta_index_rho(int theta_index,
                                   double rho);
  static  Polar_line *from_theta_index_rho_index(int theta_index,
                                         int rho_index,
                                         int nrhos);
  static  Polar_line *from_theta_rho(int theta,
                             int rho);
  static  Polar_line *from_theta_rho_index(int theta,
                                   int rho_index);

  inline double to_cos() const { return Polar_trig::to_cos(theta_index); }
  inline double to_sin() const { return Polar_trig::to_sin(theta_index); }
  inline double get_rho() const { return rho; }
  inline int get_rho_index() const { return rho_index; }
  inline int get_theta_index() const { return theta_index; }
  inline void set_rho(double m_rho) { rho = m_rho; }
  inline void set_rho_index(double m_rho_index) { rho_index = m_rho_index; }
  inline void set_theta_index(int m_theta_index) { theta_index = m_theta_index; }
  std::string to_string() const;
  void write(FILE *fp, Errors &errors);
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};
#endif //SRC__POLAR_LINE_HPP_
