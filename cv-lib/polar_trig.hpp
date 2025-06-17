#ifndef SRC__POLAR_TRIG_HPP_
#define SRC__POLAR_TRIG_HPP_

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include "errors.hpp"
#include "point.hpp"
#include "polar_line.hpp"

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

const int rho_pad = 10;

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
    double to_cos_index(int theta_index) const;
    void to_index(Polar_index &polar_index, Polar_line &polar_line);
    void to_point(Polar_line &polar_line, Polar_index &polar_index) const;
    double to_rho(int rho_index) const;
    int to_rho_index(double rho) const;
    double to_sin_index(int theta_index) const;
    int to_theta(int theta_index) const;
    int to_theta_index(int theta);
};
#endif // SRC__POLAR_TRIG_HPP_
