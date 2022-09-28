//
// Created by kushn on 8/9/2022.
//

#ifndef SRC__WB_WINDOW_HPP_
#define SRC__WB_WINDOW_HPP_

#include "errors.hpp"
#include "line_segment.hpp"
#include "polar_line.hpp"

class WB_window {
 private:
  int rows;
  int cols;
 public:
  WB_window() = default;
  WB_window(int m_rows, int m_cols);
  static void clip_window(int rows, int cols, Line_segment &line_segment, Polar_line &line, Errors &errors);
  double col_to_x(int col);
  static double col_to_x(int col, int cols);
  static double ellipse_dist(int row, int col, int rows, int cols);
  static bool in_ellipse(int row, int col, int rows, int cols);
  void rotate(int theta_degrees, int row, int col, double &x_rotate, double &y_rotate) const;
  void rotate(double cos_theta, double sin_theta, int row, int col, double &x_rotate, double &y_rotate) const;
  static void rotate(int theta_degrees, int row, int col, double &x_rotate, double &y_rotate, int rows, int cols);
  static void rotate(double cos_theta,
                     double sin_theta,
                     int row,
                     int col,
                     double &x_rotate,
                     double &y_rotate,
                     int rows,
                     int cols);
  static double row_to_y(int row, int rows);
  double row_to_y(int row) const;
  int x_to_col(double x) const;
  static int x_to_col(double x, int cols);
  int y_to_row(double y) const;
  static int y_to_row(double y, int rows);
};

#endif //SRC__WB_WINDOW_HPP_
