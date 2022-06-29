//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include "point.hpp"

class Polar_line {
 public:
  int rho_index;
  int theta_index;
  float cos_theta;
  float sin_theta;
  Polar_line(int m_rho_index, int m_theta_index);
  float point_to_rho(Point* point);
  float rho_difference(Point* point1, Point* point2);
  float rho_normal(Point* point);
};

#endif //SRC__POLAR_LINE_HPP_
