//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include "point.hpp"

class Polar_line {
 public:
  int rho_index;
  int rho;
  int theta_index;
  int count;
  float cos_theta;
  float sin_theta;
  Polar_line();
  Polar_line(int m_rho_index, int m_rho, int m_theta_index, float m_cos_theta, float m_sin_theta,int m_count);
  std::string to_string();
/*
  static Polar_line *from_point_theta(Point *point, int m_theta_index);
  Point *point_from_x(float x, int rows, int cols);
  Point *point_from_y(float y, int rows, int cols);
  Point *project_onto(Point *from_point);
  float rho_difference(Point *point1, Point *point2);
  float rho_normal(Point *point);
  float x_from_y(float y);
  float y_from_x(float x);
  std::list<Point *> to_line_points(int rows, int cols);
*/
};

#endif //SRC__POLAR_LINE_HPP_
