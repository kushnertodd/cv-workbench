//
// Created by kushn on 6/27/2022.
//

#include <cassert>
#include <sstream>
#include "point.hpp"

Point::Point() {}

Point::Point(int m_row,
             int m_col) :
    row(m_row),
    col(m_col) {}

Point::Point(Point &point) :
    Point::Point(point.row, point.col) {}

Point::Point(Point *point) :
    Point::Point(point->row, point->col) {}

void Point::check_point_valid(int rows, int cols) {
  assert (row >= 0 && row < rows && col >= 0 && cols < cols);
}

std::string Point::to_string() {
  std::ostringstream os;
  os << "row " << row
     << " col " << col;
  return os.str();
}