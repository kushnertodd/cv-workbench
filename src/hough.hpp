//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_HOUGH_HPP_
#define CV_WORKBENCH_SRC_HOUGH_HPP_

#include <string>
#include "errors.hpp"
#include "hough_accum.hpp"
#include "polar_line.hpp"

class Hough {
 public:
  Hough_accum *hough_accum{};
  std::list<Polar_line> lines;
  std::list<Line_segment> line_segments;

  ~Hough();
  explicit Hough(Hough_accum *m_hough_accum);
  static Hough *create_image(Image *input, int theta_inc, int pixel_threshold);
  void find_lines();
  void find_peaks(int npeaks);
  void lines_to_line_segments();
  static Hough *read(const std::string &path, Errors &errors);
  static Hough *read_text(const std::string &path, Errors &errors);
  void write(const std::string &filename, Errors &errors) const;
  void write_text(const std::string &filename, const std::string &delim, Errors &errors) const;
  void write_peak_lines(const std::string &filename, Errors &errors) const;
  void write_peak_lines_text(const std::string &filename, const std::string &delim, Errors &errors) const;
};

#endif //CV_WORKBENCH_SRC_HOUGH_HPP_
