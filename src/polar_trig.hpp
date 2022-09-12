//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_TRIG_HPP_
#define SRC__POLAR_TRIG_HPP_

#include <cassert>



class Polar_trig {

 private:
  Polar_trig();
 public:
  inline static double rho_index_to_rho(int rho_index, int nrhos) { return rho_index - nrhos / 2.0; }
  static int rho_theta_col_to_row(int rho_index, int theta_index, int col, int rows, int cols, int nrhos);
  static int rho_theta_row_to_col(int rho_index, int theta_index, int row, int rows, int cols, int nrhos);
  static int rho_theta_to_index(int rho_index, int theta_index, int nrhos);
  static int rho_to_rho_index(double rho, int nrhos);
  static double row_col_theta_to_rho(int row, int col, int theta_index, int rows, int cols);
  static int row_col_theta_to_rho_index(int row, int col, int theta_index, int nrhos, int rows, int cols);

};
#endif //SRC__POLAR_TRIG_HPP_
