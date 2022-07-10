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
#include "variance_stats.hpp"
#include "wb_defs.hpp"
#include "line_segment.hpp"

class Hough_accum {
 public:
  const int max_theta = 180;
  const int rho_buffer = 10;
  const float pi = M_PI;
  int theta_inc;
  Image *image;
  int nthetas;
  int max_rho;
  float *hough_cos;
  float *hough_sin;

  int **accum;
  Bounds bounds;

  ~Hough_accum();
  Hough_accum(int m_theta_inc, Image *m_image);

  // accessors

  int get_cols();
  int get_rows();
  bool in_window(Point* point);

  float get_cos(int theta_index);
  float get_sin(int theta_index);
  float deg_to_rad(float deg);

  float col_to_x(int col);
  float rho_index_to_rho(int rho_index);
  int rho_theta_col_to_row(int rho_index, int theta_index, int col);
  int rho_theta_row_to_col(int rho_index, int theta_index, int row);
  int rho_to_index(float rho);
  float row_col_theta_to_rho(int row, int col, int theta_index);
  int row_col_theta_to_rho_index(int row, int col, int theta_index);
  float row_to_y(int row);
  int theta_index_to_theta(int index);
  int x_to_col(float x);
  int y_to_row(float y);

  // methods

  void add(int theta_index, int rho_index, int value);
  Line_segment* clip_window(Polar_line* line);
  int choose_threshold(cv_enums::CV_threshold_type threshold_type);
  void find_peaks(std::list<Polar_line *> &lines, int peak_threshold,
                  bool non_max_suppression = false);
  void initialize(int image_theshold);
  bool maximum(int theta, int rho_index);
  void update_stats();

  bool read(std::ifstream &ifs, Errors &errors);
  bool write(std::ofstream &ofs, std::string delim, Errors &errors);
};

#endif //SRC__HOUGH_ACCUM_HPP_
