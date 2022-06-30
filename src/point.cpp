//
// Created by kushn on 6/27/2022.
//

#include <cmath>
#include "hough_trig.hpp"
#include "point.hpp"

Point::Point(
    int m_row,
    int m_col,
    int m_rows,
    int m_cols) :
    row(m_row),
    col(m_col),
    rows(m_rows),
    cols(m_cols) {
  y = row - rows / 2;
  x = col - cols / 2;
}

float Point::distance(Point *point) {
  return sqrt((x - point->x) * (x - point->x));
}

int Point::to_rho(int theta_index) {
  float cos = Hough_trig::cos(theta_index);
  float sin = Hough_trig::sin(theta_index);
  float rho = x * cos + y * sin;
  int rho_round = round(rho);
  return rho_round;
}


