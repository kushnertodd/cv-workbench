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
  const double pi = M_PI;
  int theta_inc;
  Image *image;
  int nthetas;
  int max_rho;
  double *hough_cos;
  double *hough_sin;

  int **rho_theta_accum;
  Bounds bounds;

  ~Hough_accum();
  Hough_accum(int m_theta_inc, Image *m_image);

  void add(int theta_index, int rho_index, int value) const;
  int choose_threshold(cv_enums::CV_threshold_type threshold_type) const;
  bool clip_window(Line_segment &line_segment, Polar_line &line) const;
  double col_to_x(int col) const;
  double deg_to_rad(int deg) const;
  void find_peaks(std::list<Polar_line> &lines, int peak_threshold,
                  bool non_max_suppression = false) const;
  int get_cols() const;
  double get_cos(int theta_index) const;
  int get_rows() const;
  double get_sin(int theta_index) const;
  bool in_window(Point &point) const;
  void initialize(int image_theshold);
  static bool read(std::ifstream &ifs, Errors &errors);
  double rho_index_to_rho(int rho_index) const;
  int rho_theta_col_to_row(int rho_index, int theta_index, int col) const;
  int rho_theta_row_to_col(int rho_index, int theta_index, int row) const;
  int rho_to_index(double rho) const;
  double row_col_theta_to_rho(int row, int col, int theta_index) const;
  int row_col_theta_to_rho_index(int row, int col, int theta_index) const;
  double row_to_y(int row) const;
  int theta_index_to_theta(int index) const;
  void update_stats();
  bool write_str(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
  int x_to_col(double x) const;
  int y_to_row(double y) const;
};

#endif //SRC__HOUGH_ACCUM_HPP_
