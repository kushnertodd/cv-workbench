#ifndef SRC__POLAR_TRIG_HPP_
#define SRC__POLAR_TRIG_HPP_

#include <cassert>

const int default_rho_inc = 1;
const int default_theta_inc = 3;
int rho_inc{};
int theta_inc{};
const int theta_max = 180;
const int rho_pad = 2;
/**
 * @brief
 */
class Polar_index {
    friend class Polar_trig;
    int rho_index{};
    int theta_index{};

public:
    Polar_index();
    Polar_index(int m_rho_index, int m_theta_index);
    void init(int m_rho_index, int m_theta_index);
};
/**
 * @brief
 */
class Polar_point {
    friend class Polar_trig;
    double rho{};
    double theta{};

public:
    Polar_point();
    Polar_point(double m_rho, double m_theta);
    void init(double m_rho, double m_theta);
};
/**
 * @brief
 */
class Polar_trig {
    static const double polar_cos[theta_max];
    static const double polar_sin[theta_max];
    const int rho_pad = 5;
    int nrhos{};
    int nthetas{};
    int rho_inc{};
    double rho_max{};
    double rho_min{};
    double rho_range{};
    int theta_inc{};
    double x_max{};
    double y_max{};
    double x_offset{};
    double y_offset{};

public:
    Polar_trig();
    void init(int m_x_max, int m_y_max, int m_rho_inc, int m_theta_inc);
    int get_nrhos();
    int get_nthetas() const;
    static double point_theta_index_to_rho(Point &point, int theta_index);
    static double point_theta_index_to_rho(double x, double y, int theta_index);
    static double point_theta_index_to_rho_index(Point &point, int theta_index);
    static double point_theta_index_to_rho_index(double x, double y, int theta_index);
    static double point_theta_to_rho(Point &point, int theta);
    static double point_theta_to_rho(double x, double y, int theta);
    static double point_theta_to_rho_index(Point &point, int theta);
    static double point_theta_to_rho_index(double x, double y, int theta);
    static double rho_theta_x_to_y(int rho_index, int theta_index, double x);
    static double rho_theta_y_to_x(int rho_index, int theta_index, double y);
    static bool singular_cos(int theta);
    static bool singular_cos_index(int theta_index);
    static bool singular_sin(int theta);
    static bool singular_sin_index(int theta_index);
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
