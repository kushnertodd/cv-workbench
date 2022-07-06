//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include <list>
#include <iostream>
#include "hough_accum.hpp"
#include "polar_line.hpp"

extern bool debug;

Polar_line::Polar_line() {
}

/**
 * initialize (rho, theta) line
 * @param m_rho
 * @param m_theta_index
 */

Polar_line::Polar_line(int m_rho, float m_cos_theta, float m_sin_theta):
rho(m_rho),
    cos_theta(m_cos_theta),
    sin_theta(m_sin_theta) {
}

/**
 * create line from point and theta
 * @param point
 * @param m_theta_index
 * @return
 */
/*
Polar_line *Polar_line::from_point_theta(Point *point, int m_theta_index) {
  int rho = point->to_rho(m_theta_index);
  Polar_line *polar_line = new Polar_line(rho, m_theta_index);
  return polar_line;
}

Point *Polar_line::point_from_x(float x, int rows, int cols) {
  float y = y_from_x(x);
  Point *point = Point::from_x_y(x, y, rows, cols);
  return point;
}

Point *Polar_line::point_from_y(float y, int rows, int cols) {
  float x = x_from_y(y);
  Point *point = Point::from_x_y(x, y, rows, cols);
  return point;
}
*/

/**
 * point resulting from projecting point unto line
 * @param from_point
 * @return
 */
/*
Point *Polar_line::project_onto(Point *from_point) {
  float from_rho = from_point->to_rho(cos_theta, sin_theta);
  float x = rho * cos_theta + from_rho * sin_theta;
  float y = rho * sin_theta - from_rho * cos_theta;
  Point *to_point = Point::from_x_y(x, y, from_point->rows, from_point->cols);
  return to_point;
}
*/

/**
 * difference of rho difference to these two points
 * @param point1
 * @param point2
 * @return
 */
/*
float Polar_line::rho_difference(Point *point1, Point *point2) {
  return point1->to_rho(cos_theta, sin_theta) - point2->to_rho(cos_theta, sin_theta);
}
*/

/**
 * distance from origin to point on normal to polar line
 * @param point
 * @return
 */
/*
float Polar_line::rho_normal(Point *point) {
  return point->x * sin_theta - point->y * cos_theta;
}
*/

/*
std::list<Point *> Polar_line::to_line_points(int rows, int cols) {
  std::list<Point *> points;
  int theta1 = Hough_accum::nthetas / 4;
  int theta2 = 3 * Hough_accum::nthetas / 4;

  if (theta_index >= theta1 && theta_index <= theta2) {
    // pi/4..3*pi/4
    for (int col = 0; col < cols; col++) {
      float x = Point::col_to_x(col, cols);
      Point *point = point_from_x(x, rows, cols);

      if (debug)
        std::cout << "Polar_line::to_line_points: col-wise "
                  << " theta1 " << theta1 << " theta2 " << theta2
                  << " rho " << rho
                  << " theta_index " << theta_index
                  << " cos_theta " << cos_theta
                  << " sin_theta " << sin_theta
                  << " rows " << rows << " cols " << cols << " col " << col
                  << " x " << x << " point '" << point->to_string() << "'" << std::endl;

      points.push_back(point);
    }


  } else {
// 0..pi/4, 3*pi/4..pi
    for (int row = 0; row < rows; row++) {
      float y = Point::row_to_y(row, rows);
      Point *point = point_from_y(y, rows, cols);
      if (debug)
        std::cout << "Polar_line::to_line_points: row-wise "
                  << " theta1 " << theta1 << " theta2 " << theta2
                  << " rho " << rho
                  << " theta_index " << theta_index
                  << " cos_theta " << cos_theta
                  << " sin_theta " << sin_theta
                  << " rows " << rows << " cols " << cols << " row " << row
                  << " y " << y << " point addr " << point << " point '" << point->to_string() << "'" << std::endl;
      if (point->in_window()) {
        points.push_back(point);
      }
    }

  }
  return points;
}
*/

/*
float Polar_line::y_from_x(float x) {
  return (rho - x * cos_theta) / sin_theta;
}

float Polar_line::x_from_y(float y) {
  return (rho - y * sin_theta) / cos_theta;
}
*/

