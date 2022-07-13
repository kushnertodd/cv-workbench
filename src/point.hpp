//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POINT_HPP_
#define SRC__POINT_HPP_
#include <string>

class Point {
 public:
  int row;
  int col;
  Point();
  Point(int m_row, int m_col);
  Point(Point &point);
  Point(Point *point);
  void check_point_valid(int rows, int cols);
  std::string to_string();
};

#endif //SRC__POINT_HPP_
