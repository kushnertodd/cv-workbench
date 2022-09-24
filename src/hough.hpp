//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_HOUGH_HPP_
#define CV_WORKBENCH_SRC_HOUGH_HPP_

#include <string>
#include "hough_accum.hpp"

class Hough {
 private:
  Hough_accum *hough_accum{};
 public:
  Variance_stats count_stats;
  Variance_stats difference_stats;
  Variance_stats percentage_stats;

  ~Hough();
  explicit Hough(Hough_accum *m_hough_accum);
  static Hough *create_image(Image *input, int theta_inc, int rho_inc, int pixel_threshold);
  void find_peaks(std::list<Hough_peak> &hough_peaks, int rho_size, int theta_size, int threshold_count,
                  int threshold_difference,
                  double threshold_percentage);
  inline int get(int rho_index, int theta_index) const { return hough_accum->get(rho_index, theta_index); }
  inline int get_nrhos() const { return hough_accum->get_nrhos(); }
  inline int get_nthetas() const { return hough_accum->get_nthetas(); }
  void log(std::list<WB_log_entry> &log_entries) const;
  void log_peaks(std::list<Hough_peak> &hough_peaks, std::list<WB_log_entry> &log_entries);
  static Hough *read(const std::string &path, Errors &errors);
  static Hough *read(FILE *fp, Errors &errors);
  // static Hough *read_text(std::ifstream &ifs, Errors &errors);
  void write(const std::string &path, Errors &errors) const;
  void write(FILE *fp, Errors &errors) const;
  void write_text(const std::string &path, const std::string &delim, Errors &errors) const;
  void write_text(std::ofstream &ofs, const std::string &delim) const;
};

#endif //CV_WORKBENCH_SRC_HOUGH_HPP_
