//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__IMAGE_POINT_HPP_
#define SRC__IMAGE_POINT_HPP_
#include <string>

class Image_point {
 public:
  int row;
  int col;
  int rows;
  int cols;
  float x;
  float y;
  Image_point();
  static Image_point *from_row_col(
      int m_row,
      int m_col,
      int m_rows,
      int m_cols);
  static Image_point *from_x_y(
      int m_x,
      int m_y,
      int m_rows,
      int m_cols);
bool in_window();
  float distance(Image_point *point);
  float to_rho(int theta);
  float to_rho(float cos, float sin);
  static float row_to_y(int row, int rows);
  static float col_to_x(int col, int cols);
  static int y_to_row(float y, int rows);
  static int x_to_col(float x, int cols);
  std::string to_string();
};

#endif //SRC__IMAGE_POINT_HPP_
