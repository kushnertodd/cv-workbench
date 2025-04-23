//
// Created by kushn on 6/27/2022.
//

#include <cassert>
#include <sstream>
#include "wb_utils.hpp"
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

Point::Point(double x, double y, int ncols, int nrows) {
  col = x_to_col(x, ncols);
  row = y_to_row(y, nrows);
}

void Point::check_point_valid(int nrows, int ncols) const {
  assert (row >= 0 && row < nrows && col >= 0 && col < ncols);
}

double Point::col_to_x(int col, int ncols) {
  return (col + 0.5) - ncols / 2.0;

}

double Point::ellipse_dist(int nrows, int ncols) const {
  return ellipse_dist(row, col, nrows, ncols);
}

/**
 * distance from (row, col) to center of elipse inscribed into rectangle (nrows, ncols) is:
 *   a = ncols/2
 *   b = nrows/2
 *   dist = x^2/a^2 + y^2/b^2
 * @param row
 * @param col
 * @param nrows
 * @param ncols
 * @return
 */
double Point::ellipse_dist(int row, int col, int nrows, int ncols) {
  double a_sq = ncols * ncols / 4.0;
  double b_sq = nrows * nrows / 4.0;
  double x = col_to_x(col, ncols);
  double y = row_to_y(row, nrows);
  double dist = x * x / a_sq + y * y / b_sq;
  return dist;
}

bool Point::in_ellipse(int nrows, int ncols) const {
  return in_ellipse(row, col, nrows, ncols);
}

bool Point::is_valid(int row, int col, int nrows, int ncols) {
  return (row >= 0 && row < nrows && col >= 0 && col < ncols);
}

bool Point::in_ellipse(int row, int col, int nrows, int ncols) {
  double dist = ellipse_dist(row, col, nrows, ncols);
  return dist <= 1.0;
}

double Point::row_to_y(int row, int nrows) {
  return nrows / 2.0 - (row + 0.5);

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

double Point::to_x(int ncols) const {
  return col_to_x(col, ncols);
}

double Point::to_y(int nrows) const {
  return col_to_x(row, nrows);
}

int Point::x_to_col(double x, int cols) {
  return wb_utils::double_to_int_round(x + cols / 2.0 - 0.5);
}

int Point::y_to_row(double y, int nrows) {
  return wb_utils::double_to_int_round(nrows / 2.0 - y - 0.5);
}
