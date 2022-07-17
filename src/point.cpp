//
// Created by kushn on 6/27/2022.
//

#include <cassert>
#include <sstream>
#include "point.hpp"

Point::Point() :
    row(0),
    col(0) {

}

Point::Point(int m_row,
             int m_col) :
    row(m_row),
    col(m_col) {}

Point::Point(const Point &point) :
    Point::Point(point.row, point.col) {}

void Point::check_point_valid(int rows, int cols) const {
  assert (row >= 0 && row < rows && col >= 0 && col < cols);
}

void Point::set(int m_row, int m_col) {
  row = m_row;
  col = m_col;
}
std::string Point::to_string() const {
  std::ostringstream os;
  os << "row " << row
     << " col " << col;
  return os.str();
}