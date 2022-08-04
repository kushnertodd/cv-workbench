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

const int rho_pad = 10;
const int max_theta = 180;

class Hough_accum {
 public:
  int theta_inc{};
  int nrhos{};
  int nthetas{};
  int nbins{};
  int rows{};
  int cols{};
  double *hough_cos{};
  double *hough_sin{};
  int *rho_theta_counts{};
  Variance_stats accumulator_stats;

  ~Hough_accum();
  Hough_accum();
  Hough_accum(int m_theta_inc, int m_nrhos, int m_rows, int m_cols);

  bool clip_window(Line_segment &line_segment, Polar_line &line) const;
  double col_to_x(int col) const;
  static Hough_accum *create_image(Image *image, int theta_inc, int pixel_threshold);
  static double deg_to_rad(int deg);
  void find_peaks(std::list<Polar_line> &lines, double threshold) const;
  int get(int rho_index, int theta_index) const;
  int get_cols() const;
  double get_cos(int theta_index) const;
  int get_rows() const;
  double get_sin(int theta_index) const;
  bool in_window(Point &point) const;
  void initialize(Image *image, int image_theshold);
  static Hough_accum *read(FILE *fp, Errors &errors);
  static Hough_accum *read_text(std::ifstream &ifs, Errors &errors);
  double rho_index_to_rho(int rho_index) const;
  int rho_theta_col_to_row(int rho_index, int theta_index, int col) const;
  int rho_theta_row_to_col(int rho_index, int theta_index, int row) const;
  int rho_theta_to_index(int rho_index, int theta_index) const;
  int rho_to_index(double rho) const;
  double row_col_theta_to_rho(int row, int col, int theta_index) const;
  int row_col_theta_to_rho_index(int row, int col, int theta_index) const;
  double row_to_y(int row) const;
  void set(int rho_index, int theta_index, int value) const;
  int theta_index_to_theta(int index) const;
  void update(int rho_index, int theta_index, int value) const;
  void update_accumulator_stats();
  void write(FILE *fp, Errors &errors) const;
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
  int x_to_col(double x) const;
  int y_to_row(double y) const;
};

#endif //SRC__HOUGH_ACCUM_HPP_
