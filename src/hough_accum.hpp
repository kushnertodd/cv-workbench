//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__HOUGH_ACCUM_HPP_
#define SRC__HOUGH_ACCUM_HPP_

#include "image.hpp"
#include "polar_trig.hpp"
#include "hough_peak.hpp"

class Hough_accum {
 private:
  int rows{};
  int cols{};
  int nrhos{};
  int nbins{};
  Polar_trig *polar_trig{};
  int *rho_theta_counts{};
  std::list<Hough_peak> peaks;
  Variance_stats accumulator_stats;
 public:
  ~Hough_accum();
  //Hough_accum();
  Hough_accum(int m_theta_inc, int m_rows, int m_cols);

  static Hough_accum *create_image(Image *image, int theta_inc, int pixel_threshold);
  void find_peaks(int rho_size, int theta_size, int threshold_count);
  int get(int rho_index, int theta_index) const;

  inline int get_cols() const { return cols; }//polar_trig->get_cols(); }
  inline int get_nrhos() const { return nrhos; } //polar_trig->get_nrhos(); }
  inline static int get_nthetas() { return Polar_trig::get_nthetas(); }
  inline int get_rows() const { return polar_trig->get_rows(); }
  inline static int get_theta_inc() { return Polar_trig::get_theta_inc(); }
  inline int get_count() const { return accumulator_stats.get_count(); }
  inline double get_max_value() const { return accumulator_stats.get_max_value(); }
  inline double get_mean() { return accumulator_stats.get_mean(); }
  inline double get_min_value() const { return accumulator_stats.get_min_value(); }
  inline double get_sample_variance() { return accumulator_stats.get_sample_variance(); }
  inline double get_standard_deviation() { return accumulator_stats.get_standard_deviation(); }
  inline double get_variance() { return accumulator_stats.get_variance(); }

  void initialize(Image *image, int image_threshold);
  bool is_maximum(Hough_peak &hough_peak, int rho_index, int rho_size, int theta_index, int theta_size, int threshold_count) const;
  static Hough_accum *read(FILE *fp, Errors &errors);
  //static Hough_accum *read_text(std::ifstream &ifs, Errors &errors);
  void set(int rho_index, int theta_index, int value) const;
  void update(int rho_index, int theta_index, int value) const;
  void update_accumulator_stats();
  void write(FILE *fp, Errors &errors) const;
  void write_peak_lines(FILE *fp, Errors &errors) const;
  void write_peak_lines_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};

#endif //SRC__HOUGH_ACCUM_HPP_
