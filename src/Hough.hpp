//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_HOUGH_HPP_
#define CV_WORKBENCH_SRC_HOUGH_HPP_

#include <string>
#include "errors.hpp"
#include "hough_trig.hpp"
#include "hough_accum.hpp"
#include "polar_line.hpp"

class Hough {
 public:
  string hough_filename;
  Hough_accum *accum;
  int rows;
  int cols;
  list<Polar_line *> lines;
  std::list<std::list<Point *>> line_points;

  ~Hough();
  Hough(Image *image, int threshold = 100);
  void find_lines();
  void find_peaks();
  bool read(string filename, Errors &errors);
  bool write(string filename, string delim, Errors &errors);
};

#endif //CV_WORKBENCH_SRC_HOUGH_HPP_
