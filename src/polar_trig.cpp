#include "polar_trig.hpp"
#include "wb_utils.hpp"
#include "point.hpp"
#include "polar_trig_static.hpp"

int Polar_trig::theta_inc = 3;

int Polar_trig::get_nthetas() {
  return max_thetas / theta_inc;
}

double Polar_trig::to_cos(int theta_index) {
  int polar_trig_index = theta_index * theta_inc;
  assert(polar_trig_index < max_thetas);
  return polar_cos[polar_trig_index];
}

double Polar_trig::to_sin(int theta_index) {
  int polar_trig_index = theta_index * theta_inc;
  assert(polar_trig_index < max_thetas);
  return polar_sin[polar_trig_index];
}

double Polar_trig::rho_index_to_rho(int rho_index, int nrhos)  {
  double rho_offset = nrhos / 2.0;
  double rho = rho_index - rho_offset;
  return rho;
}

// can have a singularity if theta ~= , 180, sin ~= 0
int Polar_trig::rho_theta_col_to_row(int rho_index, int theta_index, int col, int rows, int cols, int nrhos)  {
  double x = Point::col_to_x(col, cols);
  double cos_t = Polar_trig::to_cos(theta_index);
  double rho = rho_index_to_rho(rho_index, nrhos);
  double sin_t = Polar_trig::to_sin(theta_index);
  double row_offset = rows / 2.0;
  double row = (x * cos_t - rho) / sin_t + row_offset;
  return wb_utils::double_to_int_round(row);
}

// can have a singularity if theta ~= 90, cos ~= 0
int Polar_trig::rho_theta_row_to_col(int rho_index, int theta_index, int row, int rows, int cols, int nrhos)  {
  double rho = rho_index_to_rho(rho_index, nrhos);
  double cos_t = Polar_trig::to_cos(theta_index);
  double y = Point::row_to_y(row, rows);
  double sin_t = Polar_trig::to_sin(theta_index);
  double col_offset = cols / 2.0;
  double col = (rho - y * sin_t) / cos_t + col_offset;
  return wb_utils::double_to_int_round(col);
}

int Polar_trig::rho_theta_to_index(int rho_index, int theta_index, int nrhos)  {
  assert(rho_index >= 0 && rho_index < nrhos && theta_index >= 0 && theta_index < Polar_trig::get_nthetas());
  return theta_index * nrhos + rho_index;
}

int Polar_trig::rho_to_index(double rho, int nrhos)  {
  double rho_offset = nrhos / 2.0;
  int rho_index = wb_utils::double_to_int_round(rho + rho_offset);
  return rho_index;
}

double Polar_trig::row_col_theta_to_rho(int row, int col, int theta_index, int rows, int cols)  {
  double x = Point::col_to_x(col, cols);
  double cos_t = Polar_trig::to_cos(theta_index);
  double y = Point::row_to_y(row, rows);
  double sin_t = Polar_trig::to_sin(theta_index);
  double rho = x * cos_t + y * sin_t;
  return rho;
}

int Polar_trig::row_col_theta_to_rho_index(int row, int col, int theta_index, int nrhos, int rows, int cols)  {
  double rho = row_col_theta_to_rho(row, col, theta_index, rows, cols);
  int rho_index = rho_to_index(rho, nrhos);
  return rho_index;
}

int Polar_trig::theta_index_to_theta(int theta_index)  {
  int theta = theta_index * theta_inc;
  return theta;
}
