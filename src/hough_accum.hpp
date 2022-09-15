//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__HOUGH_ACCUM_HPP_
#define SRC__HOUGH_ACCUM_HPP_

#include "image.hpp"
#include "theta.hpp"
#include "hough_peak.hpp"

const int rho_pad = 2;

class Hough_accum {
 private:
  int theta_inc{};
  int rows{};
  int cols{};
  int nrhos{};
  int nbins{};
  int nthetas{};
  int *rho_theta_counts{};
  Variance_stats accumulator_stats;
 public:
  ~Hough_accum();
  Hough_accum(int m_theta_inc, int m_rows, int m_cols);

  static Hough_accum *create_image(Image *image, int theta_inc, int pixel_threshold);
  void find_peaks(std::list<Hough_peak> &hough_peaks,
                  int rho_size,
                  int theta_size,
                  int threshold_count,
                  int threshold_difference,
                  double threshold_percentage) const;
  int get(int rho_index, int theta_index) const;
  inline int get_cols() const { return cols; }
  inline int get_count() const { return accumulator_stats.get_count(); }
  inline double get_max_value() const { return accumulator_stats.get_max_value(); }
  inline double get_mean() { return accumulator_stats.get_mean(); }
  inline double get_min_value() const { return accumulator_stats.get_min_value(); }
  inline int get_nrhos() const { return nrhos; }
  inline int get_nthetas() const { return nthetas; }
  inline int get_rows() const { return rows; }
  inline double get_standard_deviation() { return accumulator_stats.get_standard_deviation(); }
  inline int get_theta_inc() const { return theta_inc; }
  void initialize(Image *image, int image_threshold);
  bool is_maximum(Hough_peak &hough_peak,
                  int rho_index,
                  int rho_size,
                  int theta_index,
                  int theta_size,
                  int threshold_count,
                  int threshold_difference,
                  double threshold_percentage) const;
  static Hough_accum *read(FILE *fp, Errors &errors);
  inline double rho_index_to_rho(int rho_index) const;
  int to_accum_index(int rho_index, int theta_index) const;
  int rho_to_rho_index(double rho) const;
  double row_col_theta_index_to_rho(int row, int col, int theta_index) const;
  int row_col_theta_index_to_rho_index(int row, int col, int theta_index) const;
  void set(int rho_index, int theta_index, int value) const;
  int to_theta_degrees(int theta_index) const;
  double to_cos(int theta_index) const;
  double to_sin(int theta_index) const;
  void update(int rho_index, int theta_index, int value) const;
  void update_accumulator_stats();
  void write(FILE *fp, Errors &errors) const;
  void write_text(std::ofstream &ofs, const std::string &delim) const;
};

#endif //SRC__HOUGH_ACCUM_HPP_
