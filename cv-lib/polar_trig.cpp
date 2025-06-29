#include "polar_trig.hpp"
#include <cmath>
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
    initialize_thetas();
    initialize_rhos();
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
void Polar_trig::check_rho(double rho) {
    min_rho = std::min(rho, rho);
    max_rho = std::max(rho, rho);
}
void Polar_trig::initialize_rhos() {
    Point ulc(min_x, min_y);
    Point urc(max_x, min_y);
    Point llc(min_x, max_y);
    Point lrc(max_x, max_y);
    min_rho = DBL_MAX;
    max_rho = DBL_MIN;
    for (int theta_index = 0; theta_index < nthetas; theta_index++) {
        double rho_ulc = point_theta_index_to_rho(ulc, theta_index);
        check_rho(rho_ulc);
        double rho_urc = point_theta_index_to_rho(urc, theta_index);
        check_rho(rho_urc);
        double rho_llc = point_theta_index_to_rho(llc, theta_index);
        check_rho(rho_llc);
        double rho_lrc = point_theta_index_to_rho(lrc, theta_index);
        check_rho(rho_lrc);
    }
    nrhos = (max_rho - min_rho) / rho_inc;
}
/**
 * @brief
 */
void Polar_trig::initialize_thetas() {
    int theta_index = 0;
    bool done = false;
    int theta = min_theta;
    while (!done) {
        if ((theta % theta_inc) == 0) {
            theta_to_index[theta] = theta_index;
            index_to_theta[theta_index] = theta;
        }
        theta_index++;
        theta = (theta == theta_pi ? -(theta_pi - 1) : theta++);
        done = (theta == max_theta);
    }
    nthetas = theta_index;
}
bool Polar_trig::is_rho_index_valid(int rho_index) const { return rho_index >= 0 && rho_index < nrhos; }
bool Polar_trig::is_theta_index_valid(int theta_index) const { return theta_index >= 0 && theta_index < nthetas; }
bool Polar_trig::is_theta_valid(int theta) const { return theta>= 0 && theta< theta_pi; }
/**
 * @brief
 * @param point
 * @param theta_index
 * @return
 */
double Polar_trig::point_theta_index_to_rho(Point &point, int theta_index)  {
    return point_theta_index_to_rho(point.x, point.y, theta_index);
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta_index
 * @return
 */
double Polar_trig::point_theta_index_to_rho(double x, double y, int theta_index)  {
    double rho = point_theta_to_rho(x, y, to_theta(theta_index));
    return rho;
}
/**
 * @brief
 * @param point
 * @param theta_index
 * @return
 */
int Polar_trig::point_theta_index_to_rho_index(Point &point, int theta_index)  {
    return point_theta_index_to_rho_index(point.x, point.y, theta_index);
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta_index
 * @return
 */
int Polar_trig::point_theta_index_to_rho_index(double x, double y, int theta_index)  {
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
    assert(is_theta_valid(theta));
    double cos_t = Polar_line::to_cos(theta);
    double sin_t = Polar_line::to_sin(theta);
    double rho = x * cos_t + y * sin_t;
    return rho;
}
/**
 * @brief
 * @param point
 * @param theta
 * @return
 */
int Polar_trig::point_theta_to_rho_index(Point &point, int theta)  {
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
int Polar_trig::point_theta_to_rho_index(double x, double y, int theta)  {
    int rho_index = to_rho_index(point_theta_to_rho(x, y, theta));
    return rho_index;
}
/**
 * @brief
 * @param theta_index
 * @return
 */
double Polar_trig::to_cos_index(int theta_index)  { return Polar_line::to_cos(to_theta(theta_index)); }
/**
 * @brief
 * @param rho_index
 * @return
 */
double Polar_trig::to_rho(int rho_index)  {
    assert(is_rho_index_valid(rho_index));
    double rho = rho_index * rho_inc + min_rho;
    return rho;
}
/**
 * @brief
 * @param rho
 * @return
 */
int Polar_trig::to_rho_index(double rho)  {
    int rho_index = wb_utils::double_to_int_round((rho - min_rho) / rho_inc);
    return rho_index;
}
/**
 * @brief
 * @param theta_index
 * @return
 */
double Polar_trig::to_sin_index(int theta_index)  { return Polar_line::to_sin(to_theta(theta_index)); }
/**
 * @brief
 * @param theta_index
 * @return
 */
int Polar_trig::to_theta(int theta_index)  {
    assert(is_theta_index_valid(theta_index));
    return index_to_theta[theta_index];
}
/**
 * @brief
 * @param theta
 * @return
 */
int Polar_trig::to_theta_index(int theta) {
    assert(is_theta_valid(theta));
    return theta_to_index[theta];
}
