//
// Created by kushn on 6/27/2022.
//

#include <cmath>
#include "hough_trig.hpp"
#include "point.hpp"

Point::Point() {}

/**
 * create point from (row, col)
 * @param m_row
 * @param m_col
 * @param m_rows
 * @param m_cols
 * @return
 */
Point *Point::from_row_col(
    int m_row,
    int m_col,
    int m_rows,
    int m_cols) {
  Point *point = new Point();
  point->row = m_row;
  point->col = m_col;
  point->rows = m_rows;
  point->cols = m_cols;
  point->y = row_to_y(m_row, m_rows);
  point->x = col_to_x(m_col, m_cols);
  return point;
}

/**
 * create point from (x, y)
 * @param m_x
 * @param m_y
 * @param m_rows
 * @param m_cols
 * @return
 */
Point *Point::from_x_y(
    int m_x,
    int m_y,
    int m_rows,
    int m_cols) {
  Point *point = new Point();
  point->x = m_x;
  point->y = m_y;
  point->rows = m_rows;
  point->cols = m_cols;
  point->row = y_to_row(m_y, m_rows);
  point->col = x_to_col(m_x, m_cols);
  return point;
}

/**
 * distance between current and passed point
 * @param point
 * @return
 */
float Point::distance(Point *point) {
  return sqrt((x - point->x) * (x - point->x));
}

/**
 * polar rho from point and theta
 * @param theta_index
 * @return
 */
float Point::to_rho(int theta_index) {
  return to_rho(Hough_trig::cos(theta_index), Hough_trig::sin(theta_index));
}

/**
 * polar rho from point and cos, sin theta
 * @param cos
 * @param sin
 * @return
 */
float Point::to_rho(float cos, float sin) {
  return x * cos + y * sin;
}

float Point::row_to_y(int row, int rows) {
  return row + rows / 2.0;
}

float Point::col_to_x(int col, int cols) {
  return col - cols / 2.0;
}

int Point::y_to_row(float y, int rows) {
  return round(y - rows / 2.0);
}

int Point::x_to_col(float x, int cols) {
  return round(x + cols / 2.0);
}