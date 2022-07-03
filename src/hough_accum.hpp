//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__HOUGH_ACCUM_HPP_
#define SRC__HOUGH_ACCUM_HPP_

#include <fstream>
#include <cmath>
#include "errors.hpp"
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "bounds.hpp"
#include "point.hpp"
#include "polar_line.hpp"
#include "hough_trig.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"

using namespace std;

class Hough_accum {
 public:
  static const int rho_buffer = 10;
  int **accum;
  int max_rho;
  int rows;
  int cols;
  Bounds bounds;

  ~Hough_accum();
  Hough_accum(Image *image, int threshold);
  void add(int theta_index, int rho, int value);
  void alloc_accum();
  int choose_threshold(cv_enums::CV_threshold_type threshold_type);
  void dealloc_accum();
  bool maximum(int theta, int rho_index);
  void find_peaks(list<Polar_line *> &lines, int threshold);
  void update_stats();
  int index_to_rho(int rho_index);
  bool read(ifstream &ifs, Errors& errors);
  int rho_to_index(int rho);
  int theta_rho_to_index(int theta_index, int rho);
  bool write(ofstream &ofs, string delim, Errors& errors);
};

#endif //SRC__HOUGH_ACCUM_HPP_
