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
int Polar_trig::add_thetas(int start_theta, int end_theta, int theta_index) {
    assert(is_theta_valid(start_theta));
    assert(is_theta_valid(end_theta));
    assert(start_theta <= end_theta);
    for (int theta = start_theta; theta <= end_theta; theta++) {
        if ((theta % theta_inc) == 0) {
            theta_to_index[theta] = theta_index;
            index_to_theta[theta_index] = theta;
            theta_index++;
        }
    }
    return theta_index;
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
 * assumes:
 * - min_theta <= max_theta
 * - min_theta, max_theta in -180..179
 * - map input thetas -180..179 to output theta 0..179
     map(theta) = (theta + 180) % 180
 * four cases:
 * - min_theta positive, max_theta positive
 *   range is min_theta..max_theta
 * - min_theta negative, max_theta negative
 *   range is map(min_theta)..map(max_theta)
 * - two cases where min_theta negative, max_theta positive
 *   + map(min_theta) >= map(max_theta)
 *     range is map(min_theta)..179, 0..max_theta
 *   + map(min_theta) < map(max_theta)
 *     range is 0..179
 */
void Polar_trig::initialize_thetas() {
    assert(min_theta <= max_theta);
    assert(is_min_max_theta_valid(min_theta));
    assert(is_min_max_theta_valid(max_theta));
    int min_theta_mapped = map_theta_pi(min_theta);
    int max_theta_mapped = map_theta_pi(max_theta);
    int theta_index = 0;

    // case 1: min_theta positive, max_theta positive
    if (min_theta >= 0 && max_theta >= 0) //  range is min_theta..max_theta
        nthetas = add_thetas(min_theta, max_theta, 0);
    // case 2: min_theta negative, max_theta negative
    else if (min_theta < 0 && max_theta < 0) //  range is map(min_theta)..map(max_theta)
        nthetas = add_thetas(min_theta_mapped, max_theta_mapped, 0);
    // case 3: min_theta negative, max_theta positive, map(min_theta) >= map(max_theta)
    else if (min_theta_mapped >= max_theta_mapped) { // range is map(min_theta)..179, 0..max_theta
        int theta_index = add_thetas(min_theta_mapped, theta_pi - 1, 0);
        nthetas = add_thetas(0, max_theta, theta_index);
    }
    // case 4: min_theta negative, max_theta positive, map(min_theta) < map(max_theta)
    else
        nthetas = add_thetas(0, theta_pi - 1, 0);
}
bool Polar_trig::is_theta_index_valid(int theta_index) const { return theta_index >= 0 && theta_index < nthetas; }
bool Polar_trig::is_theta_valid(int theta) const { return theta >= 0 && theta < theta_pi; }
/**
 * @brief
 * @param theta
 * @return theta in range -180..180
 */
bool Polar_trig::is_min_max_theta_valid(int theta) { return (theta >= -theta_pi && theta < theta_pi); }
/**
 * @brief map theta -180..179 to 0..179
 * @param theta
 * @return
 */
int Polar_trig::map_theta_pi(int theta) { return (theta + theta_pi) % theta_pi; }
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
