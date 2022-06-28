//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__HOUGH_ACCUM_HPP_
#define SRC__HOUGH_ACCUM_HPP_

#include <fstream>
#include <cmath>
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "hough_trig.hpp"

using namespace std;

extern Hough_trig hough_trig;

class Hough_accum {
 public:
  static const int rho_buffer = 10;
  int **accum;
  int max_rhos;
  int rows;
  int cols;
  ~Hough_accum();
  Hough_accum(int m_rows, int m_cols);
  void alloc_accum();
  int rho_to_index(int rho);
  int index_to_rho(int index);
  int theta_rho_to_index(int theta, int rho);
  void assign_accum(int theta, int rho, int value);
  void dealloc_accum();
  int row_col_to_rho(int row, int col, int theta);
  void write(string filename, string delim = "\t");
  void read(string filename);
};

#endif //SRC__HOUGH_ACCUM_HPP_
