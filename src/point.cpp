//
// Created by kushn on 6/27/2022.
//

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

std::string Point::to_string() {
  std::ostringstream os;
  os << " row " << row
     << " col " << col;
  return os.str();
}