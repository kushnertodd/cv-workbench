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
  Point() = default;
  Point(int m_row, int m_col);
  Point(const Point &point);
  //Point(double x, double y, int cols, int rows);
  void check_point_valid(int rows, int cols) const;
  //double ellipse_dist(int rows, int cols) const;
  inline int get_col() const { return col; }
  inline int get_row() const { return row; }
//  double get_x(int cols) const;
//  double get_y(int rows) const;
//  bool in_ellipse(int rows, int cols) const;
  static bool is_valid(int row, int col, int rows, int cols);
  void set(int m_row, int m_col);
  void set_row(int m_row);
  void set_col(int m_col);
  std::string to_string() const;
//  double to_x(int cols) const;
//  double to_y(int rows) const;
};

#endif //SRC__POINT_HPP_
