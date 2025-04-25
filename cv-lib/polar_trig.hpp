//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_TRIG_HPP_
#define SRC__POLAR_TRIG_HPP_

#include <cassert>

const int default_rho_inc = 1;
const int default_theta_inc = 3;
int rho_inc{};
int theta_inc{};
const int theta_max = 180;
const int rho_pad = 2;

class Polar_index {
    friend class Polar_trig;
    int rho_index{};
    int theta_index{};

public:
    Polar_index();
    Polar_index(int m_rho_index, int m_theta_index);
    void init(int m_rho_index, int m_theta_index);
};

class Polar_point {
    friend class Polar_trig;
    double rho{};
    double theta{};

public:
    Polar_point();
    Polar_point(double m_rho, double m_theta);
    void init(double m_rho, double m_theta);
};

class Polar_trig {
    static const double polar_cos[theta_max];
    static const double polar_sin[theta_max];
    int ncols{};
    int nrhos{};
    int nrows{};
    int nthetas{};
    int rho_inc{};
    double rho_max{};
    int theta_inc{};

public:
    Polar_trig();
    Polar_trig(int n_nrows, int m_ncols);
    Polar_trig(int m_ncols, int m_nrows, int m_rho_inc, int m_theta_inc);
    int get_ncols() const;
    int get_nrhos() const;
    int get_nrows() const;
    int get_nthetas() const;
    int get_rho_inc() const;
    int get_theta_inc() const;
    int rho_theta_col_to_row(int rho_index, int theta_index, int col) const;
    int rho_theta_row_to_col(int rho_index, int theta_index, int row) const;
    int col_row_theta_to_rho(int col, int row, int theta_index) const;
    double to_cos_index(int theta_index) const;
    static double to_cos(int theta);
    void to_index(Polar_index &polar_index, Polar_point &polar_point) const;
    void to_point(Polar_point &polar_point, Polar_index &polar_index) const;
    double to_rho(int rho_index) const;
    int to_rho_index(double rho) const;
    static double to_sin(int theta);
    double to_sin_index(int theta_index) const;
    int to_theta(int theta_index) const;
    int to_theta_index(int theta) const;
};
#endif // SRC__POLAR_TRIG_HPP_
