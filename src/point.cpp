//
// Created by kushn on 6/27/2022.
//

#include <cmath>
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


