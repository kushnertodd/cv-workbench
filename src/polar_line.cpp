//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include "hough_trig.hpp"
#include "polar_line.hpp"

Polar_line::Polar_line() {
}

/**
 * initialize (rho, theta) line
 * @param m_rho
 * @param m_theta_index
 */
Polar_line::Polar_line(int m_rho, int m_theta_index) :
    rho(m_rho),
    theta_index(m_theta_index),
    cos_theta(Hough_trig::cos(theta_index)),
    sin_theta(Hough_trig::sin(theta_index)) {
}

/**
 * create line from point and theta
 * @param point
 * @param m_theta_index
 * @return
 */
Polar_line *Polar_line::from_point_theta(Point *point, int m_theta_index) {
  Polar_line *polar_line = new Polar_line(point->to_rho(m_theta_index), m_theta_index);
  return polar_line;
}

/**
 * point resulting from projecting point unto line
 * @param from_point
 * @return
 */
Point *Polar_line::project_onto(Point *from_point) {
  float from_rho = from_point->to_rho(cos_theta, sin_theta);
  float x = rho * cos_theta + from_rho * sin_theta;
  float y = rho * sin_theta - from_rho * cos_theta;
  Point *to_point = Point::from_x_y(x, y, from_point->rows, from_point->cols);
  return to_point;
}

/**
 * difference of rho difference to these two points
 * @param point1
 * @param point2
 * @return
 */
float Polar_line::rho_difference(Point *point1, Point *point2) {
  return point1->to_rho(cos_theta, sin_theta) - point2->to_rho(cos_theta, sin_theta);
}

/**
 * distance from origin to point on normal to polar line
 * @param point
 * @return
 */
float Polar_line::rho_normal(Point *point) {
  return point->x * sin_theta - point->y * cos_theta;
}