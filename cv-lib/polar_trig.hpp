#ifndef SRC__POLAR_TRIG_HPP_
#define SRC__POLAR_TRIG_HPP_

#include <cassert>
#include <map>
#include <memory>
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
const int theta_pi = 180;
const int theta_max_2pi = 360;

/**
 * @brief
 */
class Polar_trig {
    friend class Hough;
    double min_x{};
    double max_x{};
    double min_y{};
    double max_y{};
    int rho_inc{};
    int theta_inc{};
    int max_theta{};
    int min_theta{};
    double x_range{};
    double y_range{};
    double rho_range{};
    double max_rho{};
    double min_rho{};
    double theta_range{};
    int nrhos{};
    int nthetas{};
    std::unique_ptr<int[]> thetas;
    std::map<int, int> theta_indexes;
    static const double polar_cos[theta_max_2pi];
    static const double polar_sin[theta_max_2pi];

public:
    Polar_trig();
    Polar_trig(double m_min_x, double m_max_x, double m_min_y, double m_max_y, int m_rho_inc, int m_theta_inc,
               int m_min_theta, int m_max_theta);
    int get_max_theta() const;
    double get_max_x() const;
    double get_max_y() const;
    int get_min_theta() const;
    double get_min_x() const;
    double get_min_y() const;
    int get_nrhos() const;
    int get_nthetas() const;
    int get_rho_inc() const;
    int get_theta_inc() const;
    void initialize_thetas();
    bool is_rho_index_valid(int rho_index) const;
    bool is_theta_index_valid(int theta_index) const;
    double point_theta_index_to_rho(Point &point, int theta_index) const;
    double point_theta_index_to_rho(double x, double y, int theta_index) const;
    int point_theta_index_to_rho_index(Point &point, int theta_index) const;
    int point_theta_index_to_rho_index(double x, double y, int theta_index) const;
    static double point_theta_to_rho(Point &point, int theta);
    static double point_theta_to_rho(double x, double y, int theta);
    int point_theta_to_rho_index(Point &point, int theta) const;
    int point_theta_to_rho_index(double x, double y, int theta) const;
    static double rho_theta_x_to_y(double rho, int theta, double x);
    static double rho_theta_y_to_x(double rho, int theta, double y);
    static bool singular_cos(int theta);
    bool singular_cos_index(int theta_index) const;
    static bool singular_sin(int theta);
    bool singular_sin_index(int theta_index) const;
    double to_cos_index(int theta_index) const;
    static double to_cos(int theta);
    void to_index(Polar_index &polar_index, Polar_point &polar_point);
    void to_point(Polar_point &polar_point, Polar_index &polar_index) const;
    double to_rho(int rho_index) const;
    int to_rho_index(double rho) const;
    static double to_sin(int theta);
    double to_sin_index(int theta_index) const;
    int to_theta(int theta_index) const;
    int to_theta_index(int theta);
};
#endif // SRC__POLAR_TRIG_HPP_
