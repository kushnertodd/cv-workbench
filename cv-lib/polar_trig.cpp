#include "polar_trig.hpp"
#include <cmath>
#include "pixel.hpp"
#include "polar_trig_static.hpp"
#include "wb_utils.hpp"

/**
 * @brief
 */
Polar_index::Polar_index() = default;
/**
 * @brief
 * @param m_rho_index
 * @param m_theta_index
 */
Polar_index::Polar_index(int m_rho_index, int m_theta_index) : rho_index(m_rho_index), theta_index(m_theta_index) {}
/**
 * @brief
 * @param m_rho_index
 * @param m_theta_index
 */
void Polar_index::init(int m_rho_index, int m_theta_index) {
    rho_index = m_rho_index;
    theta_index = m_theta_index;
}
/**
 * @brief
 */
Polar_point::Polar_point() = default;
/**
 * @brief
 * @param m_rho
 * @param m_theta
 */
Polar_point::Polar_point(double m_rho, double m_theta) : rho(m_rho), theta(m_theta) {}
/**
 * @brief
 * @param m_rho
 * @param m_theta
 */
void Polar_point::init(double m_rho, double m_theta) {
    rho = m_rho;
    theta = m_theta;
}
/**
 * @brief
 */
Polar_trig::Polar_trig() = default;
/**
 * @brief
 * @param m_x_max
 * @param m_y_max
 * @param m_rho_inc
 * @param m_theta_inc
 */
Polar_trig::Polar_trig(int m_x_max, int m_y_max, int m_rho_inc, int m_theta_inc) :
    x_max(m_x_max), y_max(m_y_max), rho_inc(m_rho_inc), theta_inc(m_theta_inc) {
    x_offset = x_max / 2.0;
    y_offset = y_max / 2.0;
    rho_max = sqrt(x_offset * x_offset + y_offset * y_offset);
    rho_min = -rho_max;
    rho_range = 2 * rho_max;
    nrhos = rho_range / rho_inc + rho_pad;
    nthetas = theta_max / theta_inc;
}
/**
 * @brief
 * @return
 */
int Polar_trig::get_nrhos() { return nrhos; }
/**
 * @brief
 * @return
 */
int Polar_trig::get_nthetas() { return nthetas }
/**
 * @brief
 * @param x
 * @param y
 * @param theta_index
 * @return
 */
double Polar_trig::point_theta_index_to_rho(double x, double y, int theta_index) {
    return point_theta_to_rho(x, y, to_theta(theta_index));
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta
 * @return
 */
double Polar_trig::point_theta_to_rho(double x, double y, int theta) {
    double cos_t = Polar_trig::to_cos(theta);
    double sin_t = Polar_trig::to_sin(theta);
    double rho = x * cos_t + y * sin_t;
    return rho;
}

/**
 * can have a singularity if theta ~= 180, sin ~= 0
 * @brief
 * @param rho_index
 * @param theta_index
 * @param x
 * @return
 */
double Polar_trig::rho_theta_x_to_y(int rho_index, int theta_index, double x) {
    assert(!singular_sin_index(theta_index));
    double cos_t = Polar_trig::to_cos_index(theta_index);
    double sin_t = Polar_trig::to_sin_index(theta_index);
    double rho = to_rho(rho_index);
    double y = (x * cos_t - rho) / sin_t;
    return y;
}

/**
 * can have a singularity if theta ~= 90, cos ~= 0
 * @brief
 * @param rho_index
 * @param theta_index
 * @param y
 * @return
 */
double Polar_trig::rho_theta_y_to_x(int rho_index, int theta_index, double y) {
    assert(!singular_cos_index(theta_index));
    double cos_t = Polar_trig::to_cos_index(theta_index);
    double sin_t = Polar_trig::to_sin_index(theta_index);
    double rho = to_rho(rho_index);
    double x = (rho - y * sin_t) / cos_t;
    return x;
}
/**
 * @brief
 * @param theta
 * @return
 */
bool Polar_trig::singular_cos(int theta) { return theta == theta_max / 2; }
/**
 * @brief
 * @param theta_index
 * @return
 */
bool Polar_trig::singular_cos_index(int theta_index) { return singular_cos(to_theta(theta_index)); }
/**
 * @brief
 * @param theta
 * @return
 */
bool Polar_trig::singular_sin(int theta) { return theta == 0; }
/**
 * @brief
 * @param theta_index
 * @return
 */
bool Polar_trig::singular_sin_index(int theta_index) { return singular_sin(to_theta(theta_index)); }
/**
 * @brief
 * @param theta
 * @return
 */
double Polar_trig::to_cos(int theta) { return polar_cos[theta]; }
/**
 * @brief
 * @param theta_index
 * @return
 */
double Polar_trig::to_cos_index(int theta_index) const { return to_cos(to_theta(theta_index)); }
/**
 * @brief
 * @param polar_index
 * @param polar_point
 */
void Polar_trig::to_index(Polar_index &polar_index, Polar_point &polar_point) const {
    polar_index.init(to_rho_index(polar_point.rho), to_theta_index(polar_point.theta));
}
/**
 * @brief
 * @param polar_point
 * @param polar_index
 */
void Polar_trig::to_point(Polar_point &polar_point, Polar_index &polar_index) const {
    polar_point.init(to_rho(polar_index.rho_index), to_theta(polar_index.theta_index));
}
/**
 * @brief
 * @param rho_index
 * @return
 */
double Polar_trig::to_rho(int rho_index) const {
    double rho = rho_index * rho_inc + rho_min;
    return rho;
}
/**
 * @brief
 * @param rho
 * @return
 */
int Polar_trig::to_rho_index(double rho) const {
    int rho_index = wb_utils::double_to_int_round((rho - rho_min) / rho_inc);
    return rho_index;
}
/**
 * @brief
 * @param theta
 * @return
 */
double Polar_trig::to_sin(int theta) { return polar_sin[theta]; }
/**
 * @brief
 * @param theta_index
 * @return
 */
double Polar_trig::to_sin_index(int theta_index) const { return to_sin(to_theta(theta_index)); }
/**
 * @brief
 * @param theta_index
 * @return
 */
int Polar_trig::to_theta(int theta_index) const {
    int theta = theta_index * theta_inc;
    return theta;
}
/**
 * @brief
 * @param theta
 * @return
 */
int Polar_trig::to_theta_index(int theta) const {
    int theta_index = theta / theta_inc;
    return theta_index;
}
