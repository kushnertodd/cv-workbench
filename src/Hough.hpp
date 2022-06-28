//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_HOUGH_HPP_
#define CV_WORKBENCH_SRC_HOUGH_HPP_

#include <string>
#include "hough_accum.hpp"

using namespace std;

class Hough {
 public:
  string hough_filename;
//    static const int theta_inc = 3;
//    static const int nthetas = 180 / theta_inc;
//    static const int rho_buffer = 10;
  Hough_accum *accum;
//    int max_rhos;
  int rows;
  int cols;

  ~Hough();
  Hough(int m_rows, int m_cols);
  int index_to_theta_deg(int index);
  float index_to_theta_cos(int index);
  float index_to_theta_sin(int index);
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

#endif //CV_WORKBENCH_SRC_HOUGH_HPP_
