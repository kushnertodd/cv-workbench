#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include "errors.hpp"
#include "point.hpp"

const int theta_pi = 180;
const int theta_max_2pi = 360;

/**
 * @brief
 */
class Polar_line {
    friend class Polar_trig;
    double rho{};
    double theta{};
    double cos_t{};
    double sin_t{};
    static const double polar_cos[theta_max_2pi];
    static const double polar_sin[theta_max_2pi];

public:
    Polar_line();
    Polar_line(double m_rho, double m_theta);
    double get_rho() const;
    double get_theta() const;
    void init(double m_rho, double m_theta);
    bool singular_cos() const;
    static bool singular_cos(double theta);
    bool singular_sin() const;
    static bool singular_sin(double theta);
    static double to_cos(int theta);
    std::string to_string() const;
    static double to_sin(int theta);
    void write(FILE *fp, Errors &errors) const;
    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
    double x_to_y(double x) const;
    double y_to_x(double y) const;
};

#endif // SRC__POLAR_LINE_HPP_
