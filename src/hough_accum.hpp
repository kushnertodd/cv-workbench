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
#include "polar_trig.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"
#include "line_segment.hpp"

class Hough_accum {
 public:
  int nbins{};
  Polar_trig *polar_trig{};
  int *rho_theta_counts{};
  Variance_stats accumulator_stats;

  ~Hough_accum();
  Hough_accum();
//  Hough_accum(int m_theta_inc, int m_nrhos, int m_rows, int m_cols);
  Hough_accum(int m_theta_inc, int m_rows, int m_cols);

//  bool clip_window(Line_segment &line_segment, Polar_line &line) const;
//  double col_to_x(int col) const;
  static Hough_accum *create_image(Image *image, int theta_inc, int pixel_threshold);
  void find_peaks(std::list<Polar_line> &lines, double threshold) const;
  int get(int rho_index, int theta_index) const;
  int get_cols() const;

  int get_nrhos() const;
  static int get_nthetas();
  int get_rows() const;
  static int get_theta_inc();
  void initialize(Image *image, int image_theshold);
  static Hough_accum *read(FILE *fp, Errors &errors);
  static Hough_accum *read_text(std::ifstream &ifs, Errors &errors);
  void set(int rho_index, int theta_index, int value) const;
  void update(int rho_index, int theta_index, int value) const;
  void update_accumulator_stats();
  void write(FILE *fp, Errors &errors) const;
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};

#endif //SRC__HOUGH_ACCUM_HPP_
