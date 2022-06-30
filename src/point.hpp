//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POINT_HPP_
#define SRC__POINT_HPP_

class Point {
 public:
  int row;
  int col;
  int rows;
  int cols;
  float x;
  float y;
  Point();
  static Point *from_row_col(
      int m_row,
      int m_col,
      int m_rows,
      int m_cols);
  static Point *from_x_y(
      int m_x,
      int m_y,
      int m_rows,
      int m_cols);
  float distance(Point *point);
  float to_rho(int theta);
  float to_rho(float cos, float sin);
};

#endif //SRC__POINT_HPP_
