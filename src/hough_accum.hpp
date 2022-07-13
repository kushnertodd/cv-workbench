//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__HOUGH_ACCUM_HPP_
#define SRC__HOUGH_ACCUM_HPP_

#include <fstream>
#include <cmath>
#include "errors.hpp"
#include "file_utils.hpp"
#include "image.hpp"
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

  int **rho_theta_accum;
  Bounds bounds;

  ~Hough_accum();
  Hough_accum(int m_theta_inc, Image *m_image);

  void add(int theta_index, int rho_index, int value);
  int choose_threshold(cv_enums::CV_threshold_type threshold_type);
  Line_segment *clip_window(Polar_line *line);
  float col_to_x(int col);
  float deg_to_rad(float deg);
  void find_peaks(std::list<Polar_line *> &lines, int peak_threshold,
                  bool non_max_suppression = false);
  int get_cols();
  float get_cos(int theta_index);
  int get_rows();
  float get_sin(int theta_index);
  bool in_window(Point *point);
  void initialize(int image_theshold);
  Polar_line *make_polar_line(int rho_index, int theta_index, int count = 0);
//  bool maximum(int theta, int rho_index);
  bool read(std::ifstream &ifs, Errors &errors);
  float rho_index_to_rho(int rho_index);
  int rho_theta_col_to_row(int rho_index, int theta_index, int col);
  int rho_theta_row_to_col(int rho_index, int theta_index, int row);
  int rho_to_index(float rho);
  float row_col_theta_to_rho(int row, int col, int theta_index);
  int row_col_theta_to_rho_index(int row, int col, int theta_index);
  float row_to_y(int row);
  int theta_index_to_theta(int index);
  void update_stats();
  bool write_str(std::ofstream &ofs, std::string delim, Errors &errors);
  int x_to_col(float x);
  int y_to_row(float y);
};

#endif //SRC__HOUGH_ACCUM_HPP_
