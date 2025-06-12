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
 * @param m_min_x
 * @param m_min_y
 * @param m_max_x
 * @param m_max_y
 * @param m_rho_inc
 * @param m_theta_inc
 * @param m_min_theta
 * @param m_max_theta
 */
Polar_trig::Polar_trig(double m_min_x, double m_min_y, double m_max_x, double m_max_y, int m_rho_inc, int m_theta_inc,
                       int m_min_theta, int m_max_theta) :
    min_x(m_min_x), max_x(m_max_x), min_y(m_min_y), max_y(m_max_y), rho_inc(m_rho_inc), theta_inc(m_theta_inc),
    min_theta(m_min_theta), max_theta(m_max_theta) {
    x_range = max_x - min_x;
    y_range = max_y - min_y;
    rho_range = sqrt(x_range * x_range + y_range * y_range) + rho_pad;
    max_rho = rho_range / 2.0;
    min_rho = -max_rho;
    nrhos = rho_range / rho_inc;
    if (max_theta >= min_theta) {
        theta_range = max_theta - min_theta;
        nthetas = theta_range / theta_inc + 1;
    } else {
        theta_range = theta_max - min_theta + max_theta + 1;
        nthetas = theta_range / theta_inc;
    }
    initialize_thetas();
}
int Polar_trig::get_max_theta() const { return max_theta; }
double Polar_trig::get_max_x() const { return max_x; }
double Polar_trig::get_max_y() const { return max_y; }
int Polar_trig::get_min_theta() const { return min_theta; }
double Polar_trig::get_min_x() const { return min_x; }
double Polar_trig::get_min_y() const { return min_y; }
int Polar_trig::get_nrhos() const { return nrhos; }
int Polar_trig::get_nthetas() const { return nthetas; }
int Polar_trig::get_rho_inc() const { return rho_inc; }
int Polar_trig::get_theta_inc() const { return theta_inc; }
/**
 * @brief
 */
void Polar_trig::initialize_thetas() {
    thetas = std::make_unique<int[]>(nthetas);
    int theta_index = 0;
    if (max_theta > min_theta) {
        for (int theta = min_theta; theta <= max_theta; theta += theta_inc, theta_index++) {
            theta_indexes[theta] = theta_index;
            thetas[theta_index] = theta;
        }
    } else {
        for (int theta = min_theta; theta < theta_max; theta += theta_inc, theta_index++) {
            theta_indexes[theta] = theta_index;
            thetas[theta_index] = theta;
        }
        for (int theta = 0; theta <= max_theta; theta += theta_inc, theta_index++) {
            theta_indexes[theta] = theta_index;
            thetas[theta_index] = theta;
        }
    }
    assert(theta_index == nthetas);
}
bool Polar_trig::is_rho_index_valid(int rho_index) const { return rho_index >= 0 && rho_index < nrhos; }
bool Polar_trig::is_theta_index_valid(int theta_index) const { return theta_index >= 0 && theta_index < nthetas; }

/**
 * @brief
 * @param point
 * @param theta_index
 * @return
 */
double Polar_trig::point_theta_index_to_rho(Point &point, int theta_index) const {
    return point_theta_index_to_rho(point.x, point.y, theta_index);
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta_index
 * @return
 */
double Polar_trig::point_theta_index_to_rho(double x, double y, int theta_index) const {
    double rho = point_theta_to_rho(x, y, to_theta(theta_index));
    return rho;
}
/**
 * @brief
 * @param point
 * @param theta_index
 * @return
 */
int Polar_trig::point_theta_index_to_rho_index(Point &point, int theta_index) const {
    return point_theta_index_to_rho_index(point.x, point.y, theta_index);
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta_index
 * @return
 */
int Polar_trig::point_theta_index_to_rho_index(double x, double y, int theta_index) const {
    int rho_index = to_rho_index(point_theta_to_rho(x, y, to_theta(theta_index)));
    assert(is_rho_index_valid(rho_index));
    return rho_index;
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta
 * @return
 */
double Polar_trig::point_theta_to_rho(Point &point, int theta) {
    double rho = point_theta_to_rho(point.x, point.y, theta);
    return rho;
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
 * @brief
 * @param point
 * @param theta
 * @return
 */
int Polar_trig::point_theta_to_rho_index(Point &point, int theta) const {
    int rho_index = point_theta_to_rho_index(point.x, point.y, theta);
    return rho_index;
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta
 * @return
 */
int Polar_trig::point_theta_to_rho_index(double x, double y, int theta) const {
    int rho_index = to_rho_index(point_theta_to_rho(x, y, theta));
    return rho_index;
}
/**
 * can have a singularity if theta ~= 180, sin ~= 0
 * @brief
 * @param rho
 * @param theta
 * @param x
 * @return
 */
double Polar_trig::rho_theta_x_to_y(double rho, int theta, double x) {
    assert(!singular_sin(theta));
    double cos_t = Polar_trig::to_cos(theta);
    double sin_t = Polar_trig::to_sin(theta);
    double y = (rho - x * cos_t) / sin_t;
    return y;
}

/**
 * can have a singularity if theta ~= 90, cos ~= 0
 * @brief
 * @param rho
 * @param theta
 * @param y
 * @return
 */
double Polar_trig::rho_theta_y_to_x(double rho, int theta, double y) {
    assert(!singular_cos(theta));
    double cos_t = Polar_trig::to_cos(theta);
    double sin_t = Polar_trig::to_sin(theta);
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
bool Polar_trig::singular_cos_index(int theta_index) const { return singular_cos(to_theta(theta_index)); }
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
bool Polar_trig::singular_sin_index(int theta_index) const { return singular_sin(to_theta(theta_index)); }
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
void Polar_trig::to_index(Polar_index &polar_index, Polar_point &polar_point) {
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
    double rho = rho_index * rho_inc + min_rho;
    return rho;
}
/**
 * @brief
 * @param rho
 * @return
 */
int Polar_trig::to_rho_index(double rho) const {
    int rho_index = wb_utils::double_to_int_round((rho - min_rho) / rho_inc);
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
    assert(is_theta_index_valid(theta_index));
    return thetas[theta_index];
}
/**
 * @brief
 * @param theta
 * @return
 */
int Polar_trig::to_theta_index(int theta) { return theta_indexes[theta]; }
