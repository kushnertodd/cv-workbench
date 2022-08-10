//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_TRIG_HPP_
#define SRC__POLAR_TRIG_HPP_

#include <cassert>

class Polar_trig {
public:
  static const int max_thetas = 180;
  static int theta_inc;
  static const double polar_cos[max_thetas];
  static const double polar_sin[max_thetas];

  static int get_nthetas();
  static double to_cos(int theta_index);
  static double to_sin(int theta_index);

  static double rho_index_to_rho(int rho_index, int nrhos) ;
  static int rho_theta_col_to_row(int rho_index, int theta_index, int col, int rows, int cols, int nrhos) ;
  static int rho_theta_row_to_col(int rho_index, int theta_index, int row, int rows, int cols, int nrhos) ;
  static int rho_theta_to_index(int rho_index, int theta_index, int nrhos) ;
  static int rho_to_index(double rho, int nrhos) ;
  static double row_col_theta_to_rho(int row, int col, int theta_index, int rows, int cols) ;
  static int row_col_theta_to_rho_index(int row, int col, int theta_index, int nrhos, int rows, int cols) ;
  static int theta_index_to_theta(int index) ;

};
#endif //SRC__POLAR_TRIG_HPP_
