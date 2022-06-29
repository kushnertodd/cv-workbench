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

Hough::Hough(int m_rows, int m_cols) :
    rows(m_rows),
    cols(m_cols) {
  accum = new Hough_accum(rows, cols);
}

void Hough::find_peaks() {
  int threshold = accum->choose_threshold(cv_enums::CV_threshold_type::FIXED);
  accum->find_peaks(lines, threshold);
}

bool Hough::read(string filename, Errors& errors) {
  ifstream ifs(filename, ofstream::in);
  if (!ifs) {
    errors.add("Hough:read invalid filename '" + filename + "'");
    return false;
  }
  bool return_value = true;
  if (!accum->read(ifs, errors)){
    return_value = false;
  }
  ifs.close();
  return return_value;
}

bool Hough::write(string filename, string delim, Errors& errors) {
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




