//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include <fstream>
#include <vector>
#include "hough_peak.hpp"
#include "polar_trig.hpp"

class Polar_line {
 private:
  double rho{};
  int theta{};
  int nrhos{};
 public:
  Polar_line() = default;
  Polar_line(double m_rho,
             int m_theta,
             int m_nrhos);
  static Polar_line *from_rho_index_theta_index(int rho_index,
                                                int theta_index,
                                                int nrhos);
  static Polar_line *from_rho_theta_index(double rho,
                                          int theta_index,
                                          int nrhos);
  static Polar_line *from_rho_index_theta(int rho_index,
                                          int theta,
                                          int nrhos);
  static Polar_line *from_rho_theta(int rho,
                                    int theta,
                                    int nrhos);
  inline double get_nrhos() const { return nrhos; }
  inline double get_rho() const { return rho; }
  inline int get_rho_index() const { return Polar_trig::rho_to_rho_index(rho, nrhos); }
  inline double get_theta() const { return theta; }
  inline int get_theta_index() const { return Polar_trig::theta_to_theta_index(theta); }
  void read(FILE *fp, Errors &errors);
  void read_text(std::vector<std::string> &values, Errors &errors);
  inline void set_nrhos(int m_nrhos) { nrhos = m_nrhos; }
  inline void set_rho(double m_rho) { rho = m_rho; }
  inline void set_rho_index(double rho_index) { rho = Polar_trig::rho_index_to_rho(rho_index, nrhos); }
  inline void set_theta(int m_theta) { theta = m_theta; }
  inline void set_theta_index(int theta_index) { theta = Polar_trig::theta_index_to_theta(theta_index); }
  inline double to_cos() const { return Polar_trig::to_cos(get_theta_index()); }
  inline double to_sin() const { return Polar_trig::to_sin(get_theta_index()); }
  std::string to_string() const;
  void write(FILE *fp, Errors &errors);
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};
#endif //SRC__POLAR_LINE_HPP_
