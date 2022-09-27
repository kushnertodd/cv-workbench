//
// Created by kushn on 6/27/2022.
//

#include <cassert>
#include <sstream>
#include "theta.hpp"
#include "wb_utils.hpp"
#include "point.hpp"

/**
 * Constructor
 */
Point::Point() :
    row(0),
    col(0) {

}

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
Point::Point(double x, double y, int cols, int rows) {
  col = x_to_col(x, cols);
  row = y_to_row(y, rows);
}

/**
 * Check point is in image
 * @param rows
 * @param cols
 */
void Point::check_point_valid(int rows, int cols) const {
  assert (row >= 0 && row < rows && col >= 0 && col < cols);
}

/**
 * Convert column to x coordinate
 * @param col
 * @param cols
 * @return
 */
double Point::col_to_x(int col, int cols) {
  return (col + 0.5) - cols / 2.0;
}

/**
 * Computer elliptical distance
 * @param rows
 * @param cols
 * @return
 */
double Point::ellipse_dist(int rows, int cols) const {
  return ellipse_dist(row, col, rows, cols);
}

/**
 * distance from (row, col) to center of elipse inscribed into rectangle (rows, cols) is:
 *   a = cols/2
 *   b = rows/2
 *   dist = x^2/a^2 + y^2/b^2
 * @param row
 * @param col
 * @param rows
 * @param cols
 * @return
 */
double Point::ellipse_dist(int row, int col, int rows, int cols) {
  double a_sq = cols * cols / 4.0;
  double b_sq = rows * rows / 4.0;
  double x = col_to_x(col, cols);
  double y = row_to_y(row, rows);
  double dist = x * x / a_sq + y * y / b_sq;
  return dist;
}

double Point::get_x(int cols) const {
  return col_to_x(col, cols);
}

double Point::get_y(int rows) const {
  return row_to_y(row, rows);
}

/**
 * Check if point is in ellipse
 * @param rows
 * @param cols
 * @return
 */
bool Point::in_ellipse(int rows, int cols) const {
  return in_ellipse(row, col, rows, cols);
}

/**
 * Check if point is in ellipse
 * @param rows
 * @param cols
 * @return
 */
bool Point::in_ellipse(int row, int col, int rows, int cols) {
  double dist = ellipse_dist(row, col, rows, cols);
  return dist <= 1.0;
}

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

/**
 * rotate point around window (0,0)-(cols-1, rows-1) centered at (cols/2, rows/2)
 * @param theta_degrees
 * @param rows
 * @param cols
 * @return
 */
void Point::rotate(int theta_degrees, double &x_rotate, double &y_rotate, int rows, int cols) const {
  rotate(theta_degrees,  row,  col, x_rotate, y_rotate, rows, cols);
}

void Point::rotate(double cos_theta, double sin_theta, double &x_rotate, double &y_rotate, int rows, int cols) const {
   rotate(cos_theta, sin_theta,  row,  col, x_rotate, y_rotate, rows, cols);
}

void Point::rotate(int theta_degrees, int row, int col, double &x_rotate, double &y_rotate, int rows, int cols)  {
  double theta_radians = Theta::degrees_to_radians(theta_degrees);
  double cos_theta = cos(theta_radians);
  double sin_theta = sin(theta_radians);
  rotate(cos_theta, sin_theta,  row,  col, x_rotate, y_rotate, rows, cols);
}

/**
 * rotate point around center (rows/2, cols/2) of (rows, cols) size window
 * @param cos_theta
 * @param sin_theta
 * @param row
 * @param col
 * @param rows
 * @param cols
 * @return
 */
void Point::rotate(double cos_theta, double sin_theta, int row, int col, double &x_rotate, double &y_rotate, int rows, int cols)  {
  double x = Point::col_to_x(col, cols);
  double y = Point::row_to_y(row, rows);
   x_rotate = x * cos_theta + y * sin_theta;
   y_rotate = -x * sin_theta + y * cos_theta;
}

/**
 * Convert row to y coordinate
 * @param row
 * @param rows
 * @return
 */
double Point::row_to_y(int row, int rows) {
  return rows / 2.0 - (row + 0.5);
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
double Point::to_x(int cols) const {
  return col_to_x(col, cols);
}

/**
 * convert row to y coordinate
 * @param rows
 * @return
 */
double Point::to_y(int rows) const {
  return col_to_x(row, rows);
}

/**
 * convert x coordinate to column
 * @param x
 * @param cols
 * @return
 */
int Point::x_to_col(double x, int cols) {
  return wb_utils::double_to_int_round(x + cols / 2.0 - 0.5);
}

/**
 * convert  y coordinate to row
 * @param y
 * @param rows
 * @return
 */
int Point::y_to_row(double y, int rows) {
  return wb_utils::double_to_int_round(rows / 2.0 - y - 0.5);
}
