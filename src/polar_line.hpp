//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include <fstream>
#include <vector>
#include "theta.hpp"
/**
 * Polar line (rho, theta)
 *
 * @image html polar_line.jpg
 */
class Polar_line {
 private:
  double rho{};
  Theta theta;
 public:
  Polar_line();
  Polar_line(double m_rho,
             int theta_degrees);

  int col_to_row(int col, int rows, int cols) const;
  inline double get_rho() const { return rho; }
  inline Theta get_theta() const { return theta; }
  inline int get_theta_degrees() const { return theta.get_theta_degrees(); }
  inline double get_theta_radians() const { return theta.get_theta_radians(); }
  void read(FILE *fp, Errors &errors);
  void read_text(std::vector<std::string> &values, Errors &errors);
  int row_to_col(int row, int rows, int cols) const;
  void set(double m_rho, int theta_degrees);
  inline void set_rho(double m_rho) { rho = m_rho; }
  inline void set_theta(Theta m_theta) { theta = m_theta; }
  inline void set_theta_degrees(int theta_degrees) { theta.set_theta_degrees(theta_degrees); }
  inline void set_theta_radians(int theta_radians) { theta.set_theta_radians(theta_radians); }
  double to_atan(double delta_y, double delta_x) const;
  inline double to_cos() const { return theta.to_cos(); }
  inline double to_sin() const { return theta.to_sin(); }
  double to_tan() const;
  std::string to_string() const;
  void write(FILE *fp, Errors &errors);
  void write_text(std::ofstream &ofs, const std::string &delim) const;
};
#endif //SRC__POLAR_LINE_HPP_
