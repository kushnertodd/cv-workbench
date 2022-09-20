//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_HOUGH_HPP_
#define CV_WORKBENCH_SRC_HOUGH_HPP_

#include <string>
#include "hough_accum.hpp"

class Hough {
 public:
  Hough_accum *hough_accum{};

  ~Hough();
  explicit Hough(Hough_accum *m_hough_accum);
  static Hough *create_image(Image *input, int theta_inc, int rho_inc, int pixel_threshold);
  void find_peaks(std::list<Hough_peak> &hough_peaks, int rho_size, int theta_size, int threshold_count,
                  int threshold_difference,
                  double threshold_percentage);
  //void peaks_to_line_segments(std::list<Line_segment> &line_segments, int rows, int cols, int nrhos);
  void log(Image *image, std::list<WB_log_entry> &log_entries) const;
  static Hough *read(const std::string &path, Errors &errors);
  static Hough *read(FILE *fp, Errors &errors);
 // static Hough *read_text(std::ifstream &ifs, Errors &errors);
  void write(const std::string &path, Errors &errors) const;
  void write(FILE *fp, Errors &errors) const;
  void write_text(const std::string &path, const std::string &delim, Errors &errors) const;
  void write_text(std::ofstream &ofs, const std::string &delim) const;
};

#endif //CV_WORKBENCH_SRC_HOUGH_HPP_
