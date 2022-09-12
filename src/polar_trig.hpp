//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_TRIG_HPP_
#define SRC__POLAR_TRIG_HPP_

#include <cassert>

const int max_thetas = 180;
const int rho_pad = 2;

class Polar_trig {
 private:
  static int theta_inc;
  static const double polar_cos[max_thetas];
  static const double polar_sin[max_thetas];
 private:
  Polar_trig();
 public:
  inline static int get_nthetas() { return max_thetas / theta_inc; }
  inline static int get_theta_inc() { return theta_inc; }
  inline static double rho_index_to_rho(int rho_index, int nrhos) { return rho_index - nrhos / 2.0; }
  static int rho_theta_col_to_row(int rho_index, int theta_index, int col, int rows, int cols, int nrhos);
  static int rho_theta_row_to_col(int rho_index, int theta_index, int row, int rows, int cols, int nrhos);
  static int rho_theta_to_index(int rho_index, int theta_index, int nrhos);
  static int rho_to_rho_index(double rho, int nrhos);
  static double row_col_theta_to_rho(int row, int col, int theta_index, int rows, int cols);
  static int row_col_theta_to_rho_index(int row, int col, int theta_index, int nrhos, int rows, int cols);
  static int row_col_to_nrhos(int rows, int cols);
  inline static void set_nthetas(int m_nthetas);
  inline static void set_theta_inc(int m_theta_inc) { theta_inc = m_theta_inc; };
  inline static int theta_index_to_theta(int theta_index) { return theta_index * theta_inc; }
  inline static int theta_to_theta_index(int theta) { return theta / theta_inc; }
  inline static double to_cos(int theta_index) { return polar_cos[theta_index]; }
  inline static double to_sin(int theta_index) { return polar_sin[theta_index]; }

};
#endif //SRC__POLAR_TRIG_HPP_
