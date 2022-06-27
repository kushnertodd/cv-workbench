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
  Point(int m_row,  int m_col,  int m_rows,  int m_cols);
  float distance(Point* point);
};

#endif //SRC__POINT_HPP_
