//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POINT_HPP_
#define SRC__POINT_HPP_
#include <string>

/**
 * Image point
 */
class Point {
 private:
  int row{};
  int col{};
 public:
  Point();
  Point(int m_row, int m_col);
  Point(const Point &point);
  Point(double x, double y, int cols, int rows);
  void check_point_valid(int rows, int cols) const;
  static double col_to_x(int col, int cols);
  double ellipse_dist(int rows, int cols) const;
  static double ellipse_dist(int row, int col, int rows, int cols);
  inline int get_col() const { return col; }
  double get_x(int cols) const;
  double get_y(int rows) const;
  inline int get_row() const { return row; }
  bool in_ellipse(int rows, int cols) const;
  static bool in_ellipse(int row, int col, int rows, int cols);
  static bool is_valid(int row, int col, int rows, int cols);
  void rotate(int theta_degrees, double &x_rotate, double &y_rotate, int rows, int cols) const;
  void rotate(double cos_theta, double sin_theta, double &x_rotate, double &y_rotate, int rows, int cols) const;
  static void rotate(int theta_degrees, int row, int col, double &x_rotate, double &y_rotate, int rows, int cols);
  static void rotate(double cos_theta, double sin_theta, int row, int col, double &x_rotate, double &y_rotate, int rows, int cols);
  static double row_to_y(int row, int rows);
  void set(int m_row, int m_col);
  void set_row(int m_row);
  void set_col(int m_col);
  std::string to_string() const;
  double to_x(int cols) const;
  double to_y(int rows) const;
  static int x_to_col(double x, int cols);
  static int y_to_row(double y, int rows);
};

#endif //SRC__POINT_HPP_
