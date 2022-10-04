//
// Created by kushn on 6/27/2022.
//

#include <cassert>
#include <sstream>
#include "theta.hpp"
#include "wb_utils.hpp"
#include "wb_window.hpp"
#include "point.hpp"

/**
 * Constructor
 */
Point::Point(int m_row,
             int m_col) :
    row(m_row),
    col(m_col) {}

/**
 * Constructor
 */
Point::Point(const Point &point) :
    Point::Point(point.get_row(), point.get_col()) {}

/**
 * Constructor
 */
//Point::Point(double x, double y, int cols, int rows) {
//  col = x_to_col(x, cols);
//  row = y_to_row(y, rows);
//}

/**
 * Check point is in image
 * @param rows
 * @param cols
 */
void Point::check_point_valid(int rows, int cols) const {
  assert (row >= 0 && row < rows && col >= 0 && col < cols);
}

/**
 * Computer elliptical distance
 * @param rows
 * @param cols
 * @return
 */
//double Point::ellipse_dist(int rows, int cols) const {
//  return ellipse_dist(row, col, rows, cols);
//}

//double Point::get_x(int cols) const {
//  return col_to_x(col, cols);
//}
//
//double Point::get_y(int rows) const {
//  return row_to_y(row, rows);
//}

/**
 * Check if point is in ellipse
 * @param rows
 * @param cols
 * @return
 */
//bool Point::in_ellipse(int rows, int cols) const {
//  return in_ellipse(row, col, rows, cols);
//}

/**
 * Check if point inside image
 * @param row
 * @param col
 * @param rows
 * @param cols
 * @return
 */
bool Point::is_valid(int row, int col, int rows, int cols) {
  return (row >= 0 && row < rows && col >= 0 && col < cols);
}

void Point::set_row(int m_row) {
  row = m_row;
}

void Point::set_col(int m_col) {
  col = m_col;
}

/**
 * setter from row, col
 * @param m_row
 * @param m_col
 */
void Point::set(int m_row, int m_col) {
  row = m_row;
  col = m_col;
}

/**
 * convert to information string
 * @return
 */
std::string Point::to_string() const {
  std::ostringstream os;
  os << "row " << row
     << " col " << col;
  return os.str();
}

/**
 * convert column to x coordinate
 * @param cols
 * @return
 */
//double WB_window::to_x(int cols) const {
//  return col_to_x(col, cols);
//}

/**
 * convert row to y coordinate
 * @param rows
 * @return
 */
//double WB_window::to_y(int rows) const {
//  return col_to_x(row, rows);
//}

