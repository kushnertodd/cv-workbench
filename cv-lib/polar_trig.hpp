#ifndef SRC__POLAR_TRIG_HPP_
#define SRC__POLAR_TRIG_HPP_

#include <cassert>
#include "point.hpp"

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

const int rho_pad = 10;
const int theta_max = 180;

/**
 * @brief
 */
class Polar_trig {
    friend class Hough;
    double x_min{};
    double x_max{};
    double y_min{};
    double y_max{};
    int rho_inc{};
    int theta_inc{};
    double x_range{};
    double y_range{};
    double rho_range{};
    double rho_max{};
    double rho_min{};
    int nrhos{};
    int nthetas{};
    static const double polar_cos[theta_max];
    static const double polar_sin[theta_max];

public:
    Polar_trig();
    Polar_trig(double m_x_min, double m_x_max, double m_y_min, double m_y_max, int m_rho_inc, int m_theta_inc);
    int get_nrhos() const;
    int get_nthetas() const;
    int get_rho_inc() const;
    int get_theta_inc() const;
    double point_theta_index_to_rho(Point &point, int theta_index);
    double point_theta_index_to_rho(double x, double y, int theta_index);
    int point_theta_index_to_rho_index(Point &point, int theta_index);
    int point_theta_index_to_rho_index(double x, double y, int theta_index);
    static double point_theta_to_rho(Point &point, int theta);
    static double point_theta_to_rho(double x, double y, int theta);
    int point_theta_to_rho_index(Point &point, int theta);
    int point_theta_to_rho_index(double x, double y, int theta);
    static double rho_theta_x_to_y(double rho, int theta, double x);
    static double rho_theta_y_to_x(double rho, int theta, double y);
    static bool singular_cos(int theta);
    bool singular_cos_index(int theta_index) const;
    static bool singular_sin(int theta);
    bool singular_sin_index(int theta_index) const;
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
