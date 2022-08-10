//
// Created by kushn on 6/27/2022.
//

#include <cassert>
#include <iostream>
#include "image.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"
#include "hough_accum.hpp"
#include "line_segment.hpp"

extern bool debug;

Hough_accum::~Hough_accum() {
  delete[] hough_cos;
  delete[] hough_sin;
  delete rho_theta_counts;
}

Hough_accum::Hough_accum() = default;

Hough_accum::Hough_accum(int m_theta_inc, int m_nrhos, int m_rows, int m_cols) :
    theta_inc(m_theta_inc),
    nrhos(m_nrhos),
    nbins(nrhos * Polar_trig::get_nthetas()),
    rows(m_rows),
    cols(m_cols) {

  // allocate cosine table
  hough_cos = new double[Polar_trig::get_nthetas()];
  for (int theta_index = 0; theta_index < Polar_trig::get_nthetas(); theta_index++) {
    hough_cos[theta_index] = std::cos(deg_to_rad(Polar_trig::theta_index_to_theta(theta_index)));
  }

  // allocate sine table
  hough_sin = new double[Polar_trig::get_nthetas()];
  for (int theta_index = 0; theta_index < Polar_trig::get_nthetas(); theta_index++) {
    hough_sin[theta_index] = std::sin(deg_to_rad(Polar_trig::theta_index_to_theta(theta_index)));
  }

  // accumulator
  rho_theta_counts = new int[nbins];
  for (int theta_index = 0; theta_index < Polar_trig::get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < nrhos; rho_index++)
      set(rho_index, theta_index, 0);
  }
}

/*
double Hough_accum::col_to_x(int col) const {
  double col_offset = get_cols() / 2.0;
  double x = col - col_offset;
  return x;
}
*/

Hough_accum *Hough_accum::create_image(Image *image, int theta_inc, int pixel_threshold) {
  int rows = image->get_rows();
  int cols = image->get_cols();
  int nrhos = wb_utils::double_to_int_round(sqrt(rows * rows
                                                     + image->get_cols() * image->get_cols())) + rho_pad;
  auto *hough_accum = new Hough_accum(theta_inc, nrhos, rows, cols);
  hough_accum->initialize(image, pixel_threshold);
  return hough_accum;
}

double Hough_accum::deg_to_rad(int deg) {
  double rad = deg * M_PI / max_theta;
  return rad;
}

void Hough_accum::find_peaks(std::list<Polar_line> &lines, double threshold) const {
  for (int theta_index = 0; theta_index < Polar_trig::get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < nrhos; rho_index++) {
      int count = get(rho_index, theta_index);
      if (count > threshold) {
        Polar_line line(rho_index, Polar_trig::rho_index_to_rho(rho_index, nrhos), theta_index, Polar_trig::to_cos(theta_index),
                        Polar_trig::to_sin(theta_index), count);
        lines.push_back(line);
      }
    }
  }
}

int Hough_accum::get(int rho_index, int theta_index) const {
  int index = Polar_trig::rho_theta_to_index(rho_index, theta_index, nrhos);
  return rho_theta_counts[index];
}

int Hough_accum::get_cols() const { return cols; }

//double Hough_accum::get_cos(int theta_index) const { return hough_cos[theta_index]; }

int Hough_accum::get_rows() const { return rows; }

//double Hough_accum::get_sin(int theta_index) const { return hough_sin[theta_index]; }

bool Hough_accum::in_window(Point &point) const {
  bool row_valid = point.row >= 0 && point.row < get_rows();
  bool col_valid = point.col >= 0 && point.col < get_cols();
  bool result = row_valid && col_valid;
  return result;
}

/**
 * initialize_image accumulator
 *
 * @param image_theshold
 */
void Hough_accum::initialize(Image *image, int image_theshold) {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      double value = std::abs(image->get(row, col));
      if (value > image_theshold) {
        for (int theta_index = 0; theta_index < Polar_trig::get_nthetas(); theta_index++) {
          int rho_index = Polar_trig::row_col_theta_to_rho_index(row, col, theta_index, nrhos, rows, cols);
          update(rho_index, theta_index, wb_utils::double_to_int_round(value));
        }
      }
    }
  }
  update_accumulator_stats();
}

Hough_accum *Hough_accum::read(FILE *fp, Errors &errors) {
  int theta_inc;
  int nrhos;
  int rows;
  int cols;
  wb_utils::read_int(fp,
                     theta_inc,
                     "Hough_accum::read",
                     "",
                     "missing hough accumulator theta_inc",
                     errors);
  if (!errors.has_error())
    wb_utils::read_int(fp, nrhos, "Hough_accum::read", "", "missing hough accumulator nrhos", errors);
  if (!errors.has_error())
    wb_utils::read_int(fp, rows, "Hough_accum::read", "", "missing hough accumulator rows", errors);
  if (!errors.has_error())
    wb_utils::read_int(fp, cols, "Hough_accum::read", "", "missing hough accumulator cols", errors);
  if (errors.has_error())
    return nullptr;
  else {
    auto *hough_accum = new Hough_accum(theta_inc, nrhos, rows, cols);
    wb_utils::read_int_buffer(fp,
                              hough_accum->rho_theta_counts,
                              hough_accum->nbins,
                              "Hough_accum::read",
                              "",
                              "cannot read hough accumulator data",
                              errors);
    if (errors.has_error()) {
      delete hough_accum;
      return nullptr;
    }
    hough_accum->update_accumulator_stats();
    return hough_accum;
  }
}

// NRFPT
Hough_accum *Hough_accum::read_text(std::ifstream &ifs, Errors &errors) {
  auto *hough_accum = new Hough_accum();
  std::string line;
  while (getline(ifs, line)) {
    std::vector<std::string> values = file_utils::string_split(line);
    for (const std::string &value_str: values) {
      int value;
      if (!wb_utils::string_to_int(value_str, value)) {
        errors.add("Hough_accum::read_text", "", "invalid value '" + value_str + "'");
        delete hough_accum;
        return nullptr;
      }
    }
  }
  return hough_accum;
}
/*

double Hough_accum::rho_index_to_rho(int rho_index) const {
  double rho_offset = nrhos / 2.0;
  double rho = rho_index - rho_offset;
  return rho;
}
// can have a singularity if theta ~= , 180, sin ~= 0
int Hough_accum::rho_theta_col_to_row(int rho_index, int theta_index, int col) const {
  double x = col_to_x(col);
  double cos_t = Polar_trig::to_cos(theta_index);
  double rho = rho_index_to_rho(rho_index);
  double sin_t = Polar_trig::to_sin(theta_index);
  double row_offset = get_rows() / 2.0;
  double row = (x * cos_t - rho) / sin_t + row_offset;
  return wb_utils::double_to_int_round(row);
}

// can have a singularity if theta ~= 90, cos ~= 0
int Hough_accum::rho_theta_row_to_col(int rho_index, int theta_index, int row) const {
  double rho = rho_index_to_rho(rho_index);
  double cos_t = Polar_trig::to_cos(theta_index);
  double y = row_to_y(row);
  double sin_t = Polar_trig::to_sin(theta_index);
  double col_offset = get_cols() / 2.0;
  double col = (rho - y * sin_t) / cos_t + col_offset;
  return wb_utils::double_to_int_round(col);
}

int Hough_accum::rho_theta_to_index(int rho_index, int theta_index) const {
  assert(rho_index >= 0 && rho_index < nrhos && theta_index >= 0 && theta_index < Polar_trig::get_nthetas());
  return theta_index * nrhos + rho_index;
}

int Hough_accum::rho_to_index(double rho) const {
  double rho_offset = nrhos / 2.0;
  int rho_index = wb_utils::double_to_int_round(rho + rho_offset);
  return rho_index;
}

double Hough_accum::row_col_theta_to_rho(int row, int col, int theta_index) const {
  double x = col_to_x(col);
  double cos_t = Polar_trig::to_cos(theta_index);
  double y = row_to_y(row);
  double sin_t = Polar_trig::to_sin(theta_index);
  double rho = x * cos_t + y * sin_t;
  return rho;
}

int Hough_accum::row_col_theta_to_rho_index(int row, int col, int theta_index) const {
  double rho = row_col_theta_to_rho(row, col, theta_index);
  int rho_index = rho_to_index(rho);
  return rho_index;
}

double Hough_accum::row_to_y(int row) const {
  double row_offset = get_rows() / 2.0;
  double y = row_offset - row;
  return y;
}

int Hough_accum::theta_index_to_theta(int theta_index) const {
  int theta = theta_index * theta_inc;
  return theta;
}
*/

void Hough_accum::set(int rho_index, int theta_index, int value) const {
  int index = Polar_trig::rho_theta_to_index(rho_index, theta_index, nrhos);
  rho_theta_counts[index] = value;
}

void Hough_accum::update(int rho_index, int theta_index, int value) const {
  int index = Polar_trig::rho_theta_to_index(rho_index, theta_index, nrhos);
  rho_theta_counts[index] += value;
}

void Hough_accum::update_accumulator_stats() {
  for (int theta_index = 0; theta_index < Polar_trig::get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < nrhos; rho_index++) {
      accumulator_stats.update(get(rho_index, theta_index));
    }
  }
}

void Hough_accum::write(FILE *fp, Errors &errors) const {
  fwrite(&theta_inc, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_header", "", "cannot write Hough accumulator theta_inc");
    return;
  }
  fwrite(&nrhos, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_header", "", "cannot write Hough accumulator nrhos");
    return;
  }
  fwrite(&rows, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_header", "", "cannot write Hough accumulator rows");
    return;
  }
  fwrite(&cols, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_header", "", "cannot write Hough accumulator cols");
    return;
  }
  size_t newLen;
  newLen = fwrite(rho_theta_counts, sizeof(int), nbins, fp);
  if (ferror(fp) != 0 || newLen != nbins) {
    errors.add("Image::write", "", "cannot write Hough accumulator data ");
    return;
  }
}

void Hough_accum::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  for (int rho_index = 0; rho_index < nrhos; rho_index++)
    ofs << Polar_trig::rho_index_to_rho(rho_index, nrhos) << delim;
  ofs << std::endl;
  for (int theta_index = 0; theta_index < Polar_trig::get_nthetas(); theta_index++) {
    ofs << Polar_trig::theta_index_to_theta(theta_index) << delim;
    for (int rho_index = 0; rho_index < nrhos; rho_index++) {
      ofs << get(rho_index, theta_index) << delim;
    }
    ofs << std::endl;
  }
}

int Hough_accum::x_to_col(double x) const {
  double col_offset = get_cols() / 2.0;
  int col = wb_utils::double_to_int_round(x + col_offset);
  return col;
}

int Hough_accum::y_to_row(double y) const {
  double row_offset = get_rows() / 2.0;
  int row = wb_utils::double_to_int_round(row_offset - y);
  return row;
}



