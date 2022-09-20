//
// Created by kushn on 6/27/2022.
//

#include <cassert>
#include <cmath>
#include <iostream>
#include "image.hpp"
#include "theta.hpp"
#include "wb_utils.hpp"
#include "hough_accum.hpp"

Hough_accum::~Hough_accum() {
  delete rho_theta_counts;
}

Hough_accum::Hough_accum(int m_theta_inc, int m_rho_inc, int m_rows, int m_cols) :
    theta_inc(m_theta_inc),
    rho_inc(m_rho_inc),
    rows(m_rows),
    cols(m_cols) {
  nthetas = max_degrees / theta_inc;
  max_rhos = wb_utils::double_to_int_round(sqrt(rows * rows + cols * cols)) + rho_pad;
  nrhos = max_rhos / rho_inc;
  nbins = nrhos * get_nthetas();
  rho_theta_counts = new int[nbins];
  for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < nrhos; rho_index++)
      set(rho_index, theta_index, 0);
  }
}

Hough_accum *Hough_accum::create_image(Image *image, int theta_inc, int rho_inc, int pixel_threshold) {
  assert(image != nullptr);
  auto *hough_accum = new Hough_accum(theta_inc, rho_inc, image->get_rows(), image->get_cols());
  hough_accum->initialize(image, pixel_threshold);
  return hough_accum;
}

void Hough_accum::find_peaks(std::list<Hough_peak> &hough_peaks,
                             int rho_size,
                             int theta_size,
                             int threshold_count,
                             int threshold_difference,
                             double threshold_percentage) const {
  hough_peaks.clear();
  for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
      Hough_peak hough_peak;
      if (is_maximum(hough_peak, rho_index, rho_size, theta_index, theta_size, threshold_count,
                     threshold_difference, threshold_percentage)) {
        hough_peaks.push_back(hough_peak);
      }
    }
  }
}

int Hough_accum::get(int rho_index, int theta_index) const {
  assert (rho_theta_counts != nullptr);
  int index = to_accum_index(rho_index, theta_index);
  return rho_theta_counts[index];
}

/**
 * initialize_image accumulator
 * grayscale only
 *
 * @param image_theshold
 */
void Hough_accum::initialize(Image *image, int image_threshold) {
  assert(image != nullptr);
  for (int row = image->get_min_row(); row <= image->get_max_row(); row++) {
    for (int col = image->get_min_col(); col <= image->get_max_col(); col++) {
      double value = std::abs(image->get(row, col));
      if (value > image_threshold) {
        for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
          int rho_index = row_col_theta_index_to_rho_index(row, col, theta_index);
          update(rho_index, theta_index, wb_utils::double_to_int_round(value));
        }
      }
    }
  }
  update_accumulator_stats();
}

/**
 * Determines whether a hough accumulator (rho, theta) bin is a local maximum
 * within a neighborhood rho_size x theta_size centered at the bin. Neighborhood
 * points outside the accumulator are ignored.
 *
 * Peak parameters are returned for maxima. Ties can occur, caller will have
 * to account for that.
 * @param hough_peak
 * @param rho_index
 * @param rho_size
 * @param theta_index
 * @param theta_size
 * @return true if the (rho, theta) bin is a local maximum for the neighborhood
 */
bool Hough_accum::is_maximum(Hough_peak &hough_peak,
                             int rho_index,
                             int rho_size,
                             int theta_index,
                             int theta_size,
                             int threshold_count,
                             int threshold_difference,
                             double threshold_percentage) const {
  assert (rho_theta_counts != nullptr);
  int rho_index_low = std::max(rho_index - rho_size / 2, 0);
  int rho_index_high = std::min(rho_index + rho_size / 2, get_nrhos() - 1);
  int theta_index_low = std::max(theta_index - theta_size / 2, 0);
  int theta_index_high = std::min(theta_index + theta_size / 2, get_nthetas() - 1);
  int bin_index = to_accum_index(rho_index, theta_index);
  int bin_count = rho_theta_counts[bin_index];
  if (bin_count < threshold_count)
    return false;
  int next_highest = 0;
  for (int i = theta_index_low; i <= theta_index_high; i++)
    for (int j = rho_index_low; j <= rho_index_high; j++) {
      if (theta_index != i || rho_index != j) {
        int index = to_accum_index(j, i);
        int neighbor_bin_count = rho_theta_counts[index];
        if (neighbor_bin_count > bin_count)
          return false;
        if (neighbor_bin_count > next_highest)
          next_highest = neighbor_bin_count;
      }
    }
  int difference = bin_count - next_highest;
  if (difference < threshold_difference)
    return false;
  double percentage_difference = (bin_count == 0 ? 0.0 : ((double) difference) / bin_count);
  if (percentage_difference < threshold_percentage)
    return false;
  hough_peak.set_theta_degrees(to_theta_degrees(theta_index));
  hough_peak.set_rho(rho_index_to_rho(rho_index));
  hough_peak.set_count(bin_count);
  hough_peak.set_total_difference(bin_count - next_highest);
  hough_peak.set_percent_difference(percentage_difference);
  return true;
}

Hough_accum *Hough_accum::read(FILE *fp, Errors &errors) {
  int theta_inc;
  wb_utils::read_int(fp, theta_inc, "Hough_accum::read", "", "missing hough accumulator theta_inc", errors);
  int rho_inc;
  wb_utils::read_int(fp, rho_inc, "Hough_accum::read", "", "missing hough accumulator rho_inc", errors);
  int rows;
  if (!errors.has_error())
    wb_utils::read_int(fp, rows, "Hough_accum::read", "", "missing hough accumulator get_rows()", errors);
  int cols;
  if (!errors.has_error())
    wb_utils::read_int(fp, cols, "Hough_accum::read", "", "missing hough accumulator get_cols()", errors);
  if (errors.has_error())
    return nullptr;
  else {
    auto *hough_accum = new Hough_accum(theta_inc, rho_inc, rows, cols);
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

double Hough_accum::rho_index_to_rho(int rho_index) const {
  return rho_inc * rho_index - max_rhos / 2.0;
}

int Hough_accum::to_accum_index(int rho_index, int theta_index) const {
  assert(rho_index >= 0);
  assert(rho_index < nrhos);
  assert(theta_index >= 0);
  assert(theta_index < get_nthetas());
  return theta_index * nrhos + rho_index;
}

int Hough_accum::rho_to_rho_index(double rho) const {
  double rho_offset = max_rhos / 2.0;
  int rho_index = wb_utils::double_to_int_round((rho + rho_offset) / rho_inc);
  return rho_index;
}

double Hough_accum::row_col_theta_index_to_rho(int row, int col, int theta_index) const {
  double x = Point::col_to_x(col, cols);
  double cos_t = to_cos(theta_index);
  double y = Point::row_to_y(row, rows);
  double sin_t = to_sin(theta_index);
  double rho = x * cos_t + y * sin_t;
  return rho;
}

int Hough_accum::row_col_theta_index_to_rho_index(int row, int col, int theta_index) const {
  double rho = row_col_theta_index_to_rho(row, col, theta_index);
  int rho_index = rho_to_rho_index(rho);
  return rho_index;
}

void Hough_accum::set(int rho_index, int theta_index, int value) const {
  assert (rho_theta_counts != nullptr);
  int index = to_accum_index(rho_index, theta_index);
  rho_theta_counts[index] = value;
}

int Hough_accum::to_theta_degrees(int theta_index) const {
  return theta_index * theta_inc;
}

double Hough_accum::to_cos(int theta_index) const {
  return Theta::to_cos(to_theta_degrees(theta_index));
}

double Hough_accum::to_sin(int theta_index) const {
  return Theta::to_sin(to_theta_degrees(theta_index));
}

void Hough_accum::update(int rho_index, int theta_index, int value) const {
  assert (rho_theta_counts != nullptr);
  int index = to_accum_index(rho_index, theta_index);
  rho_theta_counts[index] += value;
}

void Hough_accum::update_accumulator_stats() {
  for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
      accumulator_stats.update(get(rho_index, theta_index));
    }
  }
}

void Hough_accum::write(FILE *fp, Errors &errors) const {
  wb_utils::write_int(fp, theta_inc, "Hough_accum::write", "", "cannot write Hough accumulator theta_inc", errors);
  if (!errors.has_error())
    wb_utils::write_int(fp, rho_inc, "Hough_accum::write", "", "cannot write Hough accumulator rho_inc", errors);
  if (!errors.has_error()) 
    wb_utils::write_int(fp, rows, "Hough_accum::write", "", "cannot write Hough accumulator rows", errors);
  if (!errors.has_error()) 
    wb_utils::write_int(fp, cols, "Hough_accum::write", "", "cannot write Hough accumulator cols", errors);
  if (!errors.has_error()) 
    wb_utils::write_int_buffer(fp,
                               rho_theta_counts,
                               nbins,
                               "Hough_accum::write",
                               "",
                               "cannot write Hough accumulator data",
                               errors);
}

void Hough_accum::write_text(std::ofstream &ofs, const std::string &delim) const {
  ofs << delim;
  for (int rho_index = 0; rho_index <= get_nrhos(); rho_index++)
    ofs << rho_index_to_rho(rho_index) << delim;
  ofs << std::endl;
  for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
    ofs << to_theta_degrees(theta_index) << delim;
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
      ofs << get(rho_index, theta_index) << delim;
    }
    ofs << std::endl;
  }
}


