//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include "image_point.hpp"

class Polar_line {
 public:
  int rho;
  int theta_index;
  int count;
  float cos_theta;
  float sin_theta;
  Polar_line();
  Polar_line(int m_rho, int m_theta_index);
  static Polar_line *from_point_theta(Image_point *point, int m_theta_index);
  Image_point *point_from_x(float x, int rows, int cols);
  Image_point *point_from_y(float y, int rows, int cols);
  Image_point *project_onto(Image_point *from_point);
  float rho_difference(Image_point *point1, Image_point *point2);
  float rho_normal(Image_point *point);
  std::list<Image_point *> to_line_points(int rows, int cols);
  float x_from_y(float y);
  float y_from_x(float x);
};

#endif //SRC__POLAR_LINE_HPP_
