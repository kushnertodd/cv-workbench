//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include "point.hpp"

class Polar_line {
 public:
  int theta_index;
  float theta;
  float cos_theta;
  float sin_theta;
  float rho;
  Polar_line(Point *point, int theta) {

  }
};

#endif //SRC__POLAR_LINE_HPP_
