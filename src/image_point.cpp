//
// Created by kushn on 6/27/2022.
//

#include <cmath>
#include <sstream>
#include "hough_trig.hpp"
#include "image_point.hpp"

Image_point::Image_point() {}

/**
 * create point from (row, col)
 * @param m_row
 * @param m_col
 * @param m_rows
 * @param m_cols
 * @return
 */
Image_point *Image_point::from_row_col(
    int m_row,
    int m_col,
    int m_rows,
    int m_cols) {
  Image_point *point = new Image_point();
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
Image_point *Image_point::from_x_y(
    int m_x,
    int m_y,
    int m_rows,
    int m_cols) {
  Image_point *point = new Image_point();
  point->x = m_x;
  point->y = m_y;
  point->rows = m_rows;
  point->cols = m_cols;
  point->row = y_to_row(m_y, m_rows);
  point->col = x_to_col(m_x, m_cols);
  return point;
}

bool Image_point::in_window() {
  return (row >= 0 && row < rows && col >= 0 && col < cols);
}

/**
 * distance between current and passed point
 * @param point
 * @return
 */
float Image_point::distance(Image_point *point) {
  return sqrt((x - point->x) * (x - point->x));
}

/**
 * polar rho from point and theta
 * @param theta_index
 * @return
 */
float Image_point::to_rho(int theta_index) {
  return to_rho(Hough_trig::cos(theta_index), Hough_trig::sin(theta_index));
}

/**
 * polar rho from point and cos, sin theta
 * @param cos
 * @param sin
 * @return
 */
float Image_point::to_rho(float cos, float sin) {
  return x * cos + y * sin;
}

float Image_point::row_to_y(int row, int rows) {
  return -row + rows / 2.0;
}

float Image_point::col_to_x(int col, int cols) {
  return col - cols / 2.0;
}

int Image_point::y_to_row(float y, int rows) {
  return round(-y + rows / 2.0);
}

int Image_point::x_to_col(float x, int cols) {
  return round(x + cols / 2.0);
}

std::string Image_point::to_string() {
std::ostringstream os;
os
        << " row " << row
        << " col " << col
        << " rows " << rows
        << " cols " << cols
        << " x " << x
        << " y " << y;
return os.str();
}