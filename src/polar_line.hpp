//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include "point.hpp"

class Polar_line {
 public:
  int rho;
  int theta_index;
  float cos_theta;
  float sin_theta;
  Polar_line();
  Polar_line(int m_rho, int m_theta_index);
  static Polar_line *from_point_theta(Point *point, int m_theta_index);
  Point* project_onto(Point* from_point);
  float rho_difference(Point* point1, Point* point2);
  float rho_normal(Point* point);
};

#endif //SRC__POLAR_LINE_HPP_
