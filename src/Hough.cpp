//
// Created by kushn on 6/11/2022.
//

#include <cmath>
#include <fstream>
#include "errors.hpp"
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "hough_accum.hpp"
#include "hough_trig.hpp"
#include "hough.hpp"

using namespace std;

Hough::~Hough() {
}

Hough::Hough(Image *image, int threshold) :
    rows(image->image_header->rows),
    cols(image->image_header->cols) {
  accum = new Hough_accum(image, threshold);
}

void Hough::find_lines() {
  find_peaks();
  for (Polar_line *polar_line: lines) {
    std::list<Point *> point_list = polar_line->to_points(rows, cols);
    line_points.push_back(point_list);
  }
}

void Hough::find_peaks() {
  int threshold = accum->choose_threshold(cv_enums::CV_threshold_type::FIXED);
  accum->find_peaks(lines, threshold);
  std::list<std::list<Point *>> line_points;
  for (Polar_line *polar_line: lines) {
    std::list<Point *> point_list = polar_line->to_points(rows, cols);
    line_points.push_back(point_list);
  }
}

bool Hough::read(string filename, Errors &errors) {
  ifstream ifs(filename, ofstream::in);
  if (!ifs) {
    errors.add("Hough:read invalid filename '" + filename + "'");
    return false;
  }
  bool return_value = true;
  if (!accum->read(ifs, errors)) {
    return_value = false;
  }
  ifs.close();
  return return_value;
}

bool Hough::write(string filename, string delim, Errors &errors) {
  ofstream ofs(filename, ofstream::out);
  if (!ofs) {
    errors.add("Hough:write invalid filename '" + filename + "'");
    return false;
  }
  bool return_value = true;
  if (!accum->write(ofs, "\t", errors)) {
    return_value = false;
  }
  ofs.close();
  return return_value;
}




