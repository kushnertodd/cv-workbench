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
  const int max_theta = 180;
  int theta_inc;
  Image *image;
  Hough_accum *accum;
  std::list<Polar_line> lines;
  std::list<Line_segment> line_segments;

  ~Hough();
  Hough(Image *m_image, int m_theta_inc, int threshold);
  void find_lines();
  void find_peaks();
  void lines_to_line_segments();
  static bool read(const std::string &filename, Errors &errors);
  bool write(const std::string &filename, Errors &errors) const;
  bool write_text(const std::string &filename, const std::string &delim, Errors &errors) const;
};

#endif //CV_WORKBENCH_SRC_HOUGH_HPP_
