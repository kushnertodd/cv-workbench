//
// Created by kushn on 6/27/2022.
//

#include "image.hpp"
#include "hough_trig.hpp"
#include "polar_line.hpp"
#include "hough_accum.hpp"

Hough_accum::~Hough_accum() {
  dealloc_accum();
}

Hough_accum::Hough_accum(Image *image, int threshold) :
    rows(image->image_header->rows),
    cols(image->image_header->cols) {
  max_rho = round(sqrt(rows * rows + cols * cols)) + rho_buffer;
  alloc_accum();
  for (int row = 0; row < image->image_header->rows; row++) {
    for (int col = 0; col < image->image_header->cols; col++) {
      Point *point = Point::from_row_col(row, col, rows, cols);
      float value = image->get(row, col);
      if (value < -threshold || value > threshold) {
        for (int theta_index = 0; theta_index < Hough_trig::nthetas; theta_index++) {
          add(theta_index, point->to_rho(theta_index), abs(value));
        }
      }
    }
  }
  update_stats();
}

void Hough_accum::add(int theta_index, int rho, int value) {
  accum[theta_index][rho_to_index(rho)] += value;
}

void Hough_accum::alloc_accum() {
  accum = new int *[Hough_trig::nthetas];
  for (int theta_index = 0; theta_index < Hough_trig::nthetas; theta_index++) {
    accum[theta_index] = new int[max_rho];
    for (int j = 0; j < max_rho; j++)
      accum[theta_index][j] = 0;
  }
}

int Hough_accum::choose_threshold(cv_enums::CV_threshold_type threshold_type) {
  if (threshold_type == cv_enums::CV_threshold_type::FIXED) {
    return bounds.max_value * 0.9;
  } else if (threshold_type == cv_enums::CV_threshold_type::PERCENTAGE) {
    return bounds.max_value * 0.9;
  } else return -1;
}

void Hough_accum::dealloc_accum() {
  for (int theta_index = 0; theta_index < Hough_trig::nthetas; theta_index++)
    delete accum[theta_index];
}

void Hough_accum::find_peaks(list<Polar_line *> &lines, int threshold) {
  for (int theta_index = 0; theta_index < Hough_trig::nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < max_rho; rho_index++) {
      int count = accum[theta_index][rho_index];
      if (count > threshold) {
        Polar_line *line = new Polar_line(index_to_rho(rho_index), theta_index);
        lines.push_back(line);
      }
    }
  }
}

void Hough_accum::update_stats() {
  for (int theta_index = 0; theta_index < Hough_trig::nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < max_rho; rho_index++) {
      bounds.update(accum[theta_index][rho_index]);
    }
  }
}

int Hough_accum::index_to_rho(int rho_index) {
  return rho_index - max_rho / 2;
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

int Hough_accum::theta_rho_to_index(int theta_index, int rho) {
  return theta_index * max_rho + rho;
}

bool Hough_accum::write(ofstream &ofs, string delim, Errors &errors) {
  ofs << "nthetas " << Hough_trig::nthetas
      << " theta_inc " << Hough_trig::theta_inc
      << " max_rho " << max_rho
      << " rows " << rows
      << " cols " << cols
      << bounds.to_string()
      << endl;
  ofs << delim;
  for (int rho = 0; rho < max_rho; rho++)
    ofs << index_to_rho(rho) << delim;
  ofs << endl;
  for (int theta_index = 0; theta_index < Hough_trig::nthetas; theta_index++) {
    ofs << Hough_trig::index_to_deg(theta_index) << delim;
    for (int rho = 0; rho < max_rho; rho++) {
      ofs << accum[theta_index][rho] << delim;
    }
    ofs << endl;
  }
  return true;
}
