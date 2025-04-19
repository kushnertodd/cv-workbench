#include "polar_trig.hpp"
#include <cmath>
#include "point.hpp"
#include "polar_trig_static.hpp"
#include "wb_utils.hpp"

Polar_trig::Polar_trig() = default;
Polar_trig::Polar_trig(int m_ncols, int m_nrows) : Polar_trig(m_ncols, m_nrows, default_rho_inc, default_theta_inc) {}
Polar_trig::Polar_trig(int m_ncols, int m_nrows, int m_rho_inc, int m_theta_inc) :
    ncols(m_ncols), nrows(m_nrows), rho_inc(m_rho_inc), theta_inc(m_theta_inc) {
    rho_max = wb_utils::double_to_int_round((sqrt(nrows * nrows + ncols * ncols)) + rho_pad)/2.0);
    nrhos = rho_max / rho_inc;
    nthetas = theta_max / theta_inc;
}
int Polar_trig::get_ncols() const { return ncols; }
int Polar_trig::get_nrhos() const { return nrhos; }
int Polar_trig::get_nrows() const { return nrows; }
int Polar_trig::get_nthetas() const { return nthetas; }
int Polar_trig::get_rho_inc() const { return rho_inc; }
int Polar_trig::get_theta_inc() const { return theta_inc; }
// can have a singularity if theta ~= 180, sin ~= 0
int Polar_trig::rho_theta_col_to_row(int rho_index, int theta_index, int col) const {
    double x = Point::col_to_x(col, ncols);
    double cos_t = Polar_trig::to_cos_index(theta_index);
    double rho = to_rho(rho_index);
    double sin_t = Polar_trig::to_sin_index(theta_index);
    double row_offset = nrows / 2.0;
    double row = (x * cos_t - rho) / sin_t + row_offset;
    return wb_utils::double_to_int_round(row);
}
// can have a singularity if theta ~= 90, cos ~= 0
int Polar_trig::rho_theta_row_to_col(int rho_index, int theta_index, int row) const {
    double rho = to_rho(rho_index);
    double cos_t = Polar_trig::to_cos_index(theta_index);
    double y = Point::row_to_y(row, nrows);
    double sin_t = Polar_trig::to_sin_index(theta_index);
    double col_offset = ncols / 2.0;
    double col = (rho - y * sin_t) / cos_t + col_offset;
    return wb_utils::double_to_int_round(col);
}
double Polar_trig::row_col_theta_index_to_rho(int row, int col, int theta_index) const {
    double x = Point::col_to_x(col, ncols);
    double cos_t = Polar_trig::to_cos_index(theta_index);
    double y = Point::row_to_y(row, nrows);
    double sin_t = Polar_trig::to_sin_index(theta_index);
    double rho = x * cos_t + y * sin_t;
    return rho;
}
double Polar_trig::to_cos(int theta) const { return to_cos_index(to_theta_index(theta)); }
double Polar_trig::to_cos_index(int theta_index) const { return to_cos(theta_index); }
double Polar_trig::to_rho(int rho_index) const {
    double rho = rho_index * rho_inc - rho_max;
    return rho;
}
int Polar_trig::to_rho_index(double rho) const {
    int rho_index = wb_utils::double_to_int_round(rho + rho_max);
    return rho_index;
}
double Polar_trig::to_sin(int theta) const { return to_sin_index(to_theta_index(theta)); }
double Polar_trig::to_sin_index(int theta_index) const { return to_sin(theta_index); }
int Polar_trig::to_theta(int theta_index) const {
    int theta = theta_index * theta_inc;
    return theta;
}
int Polar_trig::to_theta_index(int theta) const {
    int theta_index = theta / theta_inc;
    return theta_index;
}
