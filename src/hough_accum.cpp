//
// Created by kushn on 6/27/2022.
//

#include <iostream>
#include "image.hpp"
#include "polar_line.hpp"
#include "hough_accum.hpp"

extern bool debug;

Hough_accum::~Hough_accum() {
  if (hough_cos != nullptr)
    delete[] hough_cos;
  if (hough_sin != nullptr)
    delete[] hough_sin;
  for (int theta_index = 0; theta_index < nthetas; theta_index++)
    if (accum[theta_index] != nullptr)
      delete accum[theta_index];
}

Hough_accum::Hough_accum(int m_theta_inc, Image *m_image) :
    theta_inc(m_theta_inc),
    image(m_image) {
  nthetas = max_theta / theta_inc;
  max_rho = round(sqrt(get_rows() * get_rows() + get_cols() * get_cols())) + rho_buffer;
  hough_cos = new float[nthetas];
  hough_sin = new float[nthetas];

  // allocate cosine table
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    hough_cos[theta_index] = std::cos(deg_to_rad(index_to_theta(theta_index)));
  }

  // allocate sine table
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    hough_sin[theta_index] = std::sin(deg_to_rad(index_to_theta(theta_index)));
  }

  // accumulator
  accum = new int *[nthetas];
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    accum[theta_index] = new int[max_rho];
    for (int j = 0; j < max_rho; j++)
      accum[theta_index][j] = 0;
  }
}

/**
 * initialize accumulator
 *
 * @param image_theshold
 */
void Hough_accum::initialize(int image_theshold) {
  for (int row = 0; row < image->image_header->rows; row++) {
    for (int col = 0; col < image->image_header->cols; col++) {
      float value = image->get(row, col);
      if (value < -image_theshold || value > image_theshold) {
        for (int theta_index = 0; theta_index < nthetas; theta_index++) {
          float rho = row_col_theta_to_rho(row, col, theta_index);
          if (debug)
            std::cout << "Hough_accum::Hough_accum: value " << value
                      << " threshold " << image_theshold
                      << " rho " << rho
                      << " theta_index " << theta_index
                      << std::endl;
          add(theta_index, rho, abs(value));
        }
      }
    }
  }
  update_stats();
}

// accessors
float Hough_accum::col_to_x(int col) { return col - get_cols() / 2.0; }
float Hough_accum::deg_to_rad(float deg) { return deg * pi / max_theta; }
int Hough_accum::get_cols() { return image->image_header->cols; }
float Hough_accum::get_cos(int theta_index) { return hough_cos[theta_index]; }
int Hough_accum::get_rows() { return image->image_header->rows; }
float Hough_accum::get_sin(int theta_index) { return hough_sin[theta_index]; }
int Hough_accum::index_to_theta(int theta_index) { return theta_index * theta_inc; }
float Hough_accum::index_to_rho(int rho_index) { return rho_index - max_rho / 2.0; }
float Hough_accum::rho_theta_col_to_row(int rho_index, int theta_index, int col) {
  return (col_to_x(col) * get_cos(theta_index) - index_to_rho(rho_index))
      / get_sin(theta_index) + get_rows() / 2.0;
}
float Hough_accum::rho_theta_row_to_col(int rho_index, int theta_index, int row) {
  return (index_to_rho(rho_index) - row_to_y(row) * get_sin(theta_index))
      / get_cos(theta_index) + get_cols() / 2.0;
}
int Hough_accum::rho_to_index(float rho) { return round(rho + max_rho / 2.0); }
int Hough_accum::row_col_theta_to_rho(int row, int col, int theta_index) {
  return rho_to_index(col_to_x(col) * get_cos(theta_index)
                          + row_to_y(row) * get_sin(theta_index));
}
float Hough_accum::row_to_y(int row) { return get_rows() / 2.0 - row; }
int Hough_accum::x_to_col(float x) { return round((x + get_cols()) / 2.0); }
int Hough_accum::y_to_row(float y) { return round((get_rows() - y) / 2.0); }

void Hough_accum::add(int theta_index, int rho, int value) {
  accum[theta_index][rho_to_index(rho)] += value;
}

int Hough_accum::choose_threshold(cv_enums::CV_threshold_type threshold_type) {
  if (threshold_type == cv_enums::CV_threshold_type::FIXED) {
    return bounds.max_value * 0.85;
  } else if (threshold_type == cv_enums::CV_threshold_type::PERCENTAGE) {
    return bounds.max_value * 0.85;
  } else return -1;
}

void Hough_accum::find_peaks(list<Polar_line *> &lines, int peak_threshold) {
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < max_rho; rho_index++) {
      int count = accum[theta_index][rho_index];
      int rho = index_to_rho(rho_index);
      if (count > peak_threshold) {
        if (true) { //maximum(theta_index, rho_index)) {
          Polar_line *line = new Polar_line(rho, get_cos(theta_index),
                                            get_sin(theta_index));
          lines.push_back(line);
          if (debug) {
            cout << "Hough_accum::find_peaks: rho_index " << rho_index
                 << " rho " << rho
                 << " theta " << theta_index
                 << " count " << accum[theta_index][rho_index]
                 << endl;
          }
        }
      }
    }
  }
}

bool Hough_accum::maximum(int theta_index, int rho_index) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int check_rho = rho_index + i;
      if (check_rho >= 0 && check_rho < max_rho) {
        int check_theta = theta_index + j;
        if (check_theta >= 0 && check_theta < nthetas) {
          if (accum[check_theta][check_rho] > accum[theta_index][rho_index]) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

void Hough_accum::update_stats() {
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < max_rho; rho_index++) {
      bounds.update(accum[theta_index][rho_index]);
    }
  }
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

bool Hough_accum::write(ofstream &ofs, string delim, Errors &errors) {
  ofs << "nthetas " << nthetas
      << " theta_inc " << theta_inc
      << " max_rho " << max_rho
      << " hough_cos " << hough_cos
      << " hough_sin " << hough_sin
      << bounds.to_string()
      << endl;
  ofs << delim;
  for (int rho = 0; rho < max_rho; rho++)
    ofs << index_to_rho(rho) << delim;
  ofs << endl;
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    ofs << index_to_theta(theta_index) << delim;
    for (int rho = 0; rho < max_rho; rho++) {
      ofs << accum[theta_index][rho] << delim;
    }
    ofs << endl;
  }
  return true;
}

