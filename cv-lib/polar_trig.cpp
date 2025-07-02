#include "polar_trig.hpp"
#include <cmath>
#include "wb_utils.hpp"

/**
 * @brief
 */
Polar_trig::Polar_trig() = default;
/**
 * @brief
 * @param m_min_x
 * @param m_max_x
 * @param m_min_y
 * @param m_max_y
 * @param m_theta_inc
 * @param m_min_theta
 * @param m_max_theta
 */
Polar_trig::Polar_trig(double m_min_x, double m_max_x, double m_min_y, double m_max_y, int m_theta_inc, int m_min_theta,
                       int m_max_theta) :
    min_x(m_min_x), max_x(m_max_x), min_y(m_min_y), max_y(m_max_y), theta_inc(m_theta_inc), min_theta(m_min_theta),
    max_theta(m_max_theta) {
    initialize_thetas();
}
int Polar_trig::get_max_theta() const { return max_theta; }
double Polar_trig::get_max_x() const { return max_x; }
double Polar_trig::get_max_y() const { return max_y; }
int Polar_trig::get_min_theta() const { return min_theta; }
double Polar_trig::get_min_x() const { return min_x; }
double Polar_trig::get_min_y() const { return min_y; }
int Polar_trig::get_nthetas() const { return nthetas; }
int Polar_trig::get_theta_inc() const { return theta_inc; }
/**
 * @brief
 */
void Polar_trig::initialize_thetas() {
    int theta_index = 0;
    bool done = false;
    bool one_more_time = false;
    int theta = min_theta;
    while (!done) {
        done = one_more_time;
        if ((theta % theta_inc) == 0) {
            theta_to_index[theta] = theta_index;
            index_to_theta[theta_index] = theta;
            theta_index++;
        }
        if (theta == theta_pi)
            theta = -(theta_pi - 1);
        else
            theta++;
        one_more_time = (theta == max_theta);
    }
    nthetas = theta_index;
}
bool Polar_trig::is_theta_index_valid(int theta_index) const { return theta_index >= 0 && theta_index < nthetas; }
bool Polar_trig::is_theta_valid(int theta) const { return theta >= 0 && theta < theta_pi; }
/**
 * @brief
 * @param theta_index
 * @return
 */
double Polar_trig::theta_index_to_cos(int theta_index) { return Polar_line::to_cos(theta_index_to_theta(theta_index)); }
/**
 * @brief
 * @param theta_index
 * @return
 */
double Polar_trig::theta_index_to_sin(int theta_index) { return Polar_line::to_sin(theta_index_to_theta(theta_index)); }
/**
 * @brief
 * @param theta_index
 * @return
 */
int Polar_trig::theta_index_to_theta(int theta_index) {
    assert(is_theta_index_valid(theta_index));
    return index_to_theta[theta_index];
}
/**
 * @brief
 * @param theta
 * @return
 */
int Polar_trig::theta_to_theta_index(int theta) {
    assert(is_theta_valid(theta));
    return theta_to_index[theta];
}
