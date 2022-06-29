//
// Created by kushn on 6/27/2022.
//

#include "hough_trig.hpp"
#include "polar_line.hpp"
#include "hough_accum.hpp"

Hough_accum::~Hough_accum() {
  dealloc_accum();
}

Hough_accum::Hough_accum(int m_rows, int m_cols) :
    rows(m_rows),
    cols(m_cols) {
  max_rho = round(sqrt(rows * rows + cols * cols)) + rho_buffer;
  alloc_accum();
}

void Hough_accum::add(int theta, int rho, int value) {
  accum[theta][rho_to_index(rho)] += value;
  bounds.add(value);
  variance_stats.update(value);
}

void Hough_accum::alloc_accum() {
  accum = new int *[Hough_trig::nthetas];
  for (int i = 0; i < Hough_trig::nthetas; i++) {
    accum[i] = new int[max_rho];
    for (int j = 0; j < max_rho; j++)
      accum[i][j] = 0;
  }
}

int choose_threshold(cv_enums::CV_threshold_type threshold_type) {
  if (threshold_type == cv_enums::CV_threshold_type::FIXED) {
    return 5;
  } else if (threshold_type == cv_enums::CV_threshold_type::PERCENTAGE) {
    return 5;
  } else return -1;
}

void Hough_accum::dealloc_accum() {
  for (int i = 0; i < Hough_trig::nthetas; i++)
    delete accum[i];
}

void Hough_accum::find_peaks(list<Polar_line *> &lines, int threshold) {
  for (int theta = 0; theta < Hough_trig::nthetas; theta++) {
    for (int rho = 0; rho < max_rho; rho++) {
      if (accum[theta][rho] > threshold) {
        Polar_line *line = new Polar_line(rho, theta);
        lines.push_back(line);
      }
    }
  }
}

int Hough_accum::index_to_rho(int index) {
  return index - max_rho / 2;
}

bool Hough_accum::read(ifstream &ifs, Errors &errors) {
  string line;
  while (getline(ifs, line)) {
    vector<string> values = File_utils::string_split(line);
    for (string value_str: values) {
      int value;
      if (!Workbench_utils::string_to_int(value_str, value))
        errors.add("Hough_accum::read: invalid value '" + value_str + "'");
      return false;
    }
  }
  return true;
}

int Hough_accum::rho_to_index(int rho) {
  return rho + max_rho / 2;
}

int Hough_accum::theta_rho_to_index(int theta, int rho) {
  return theta * max_rho + rho;
}

bool Hough_accum::write(ofstream &ofs, string delim, Errors &errors) {
  for (int rho = 0; rho < max_rho; rho++)
    ofs << index_to_rho(rho) << delim;
  ofs << endl;
  for (int theta = 0; theta < Hough_trig::nthetas; theta++) {
    ofs << Hough_trig::index_to_deg(theta) << delim;
    for (int rho = 0; rho < max_rho; rho++) {
      ofs << accum[theta][rho] << delim;
    }
    ofs << endl;
  }
  return true;
}

