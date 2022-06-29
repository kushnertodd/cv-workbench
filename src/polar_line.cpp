//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include "hough_trig.hpp"
#include "polar_line.hpp"

Polar_line::Polar_line(int m_rho_index, int m_theta_index) :
    rho_index(m_rho_index),
    theta_index(m_theta_index),
    cos_theta(Hough_trig::cos(theta_index)),
    sin_theta(Hough_trig::sin(theta_index)) {

}

/**
 * distance from origin to point on polar line
 * @param point
 * @return
 */
float Polar_line::point_to_rho(Point *point) {
  return point->x * cos_theta + point->y * sin_theta;
}

float Polar_line::rho_difference(Point *point1, Point *point2) {
  return abs(point_to_rho(point1) - point_to_rho(point2));
}

/**
 * distance from origin to point on normal to polar line
 * @param point
 * @return
 */
float Polar_line::rho_normal(Point *point) {
  return point->x * sin_theta - point->y * cos_theta;
}
