//
// Created by kushn on 6/27/2022.
//

#include <cmath>
#include <iostream>
#include "image.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"
#include "wb_utils.hpp"
#include "hough_accum.hpp"

Hough_accum::~Hough_accum() {
  delete rho_theta_counts;
}

Hough_accum::Hough_accum(int m_theta_inc, int m_rows, int m_cols) :
theta_inc(m_theta_inc),
rows(m_rows),
cols(m_cols)
{
nrhos=wb_utils::double_to_int_round(sqrt(rows * rows + cols * cols)) + rho_pad;
nbins = get_nrhos() * get_nthetas();
  rho_theta_counts = new int[nbins];
  for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++)
      set(rho_index, theta_index, 0);
  }
}

Hough_accum *Hough_accum::create_image(Image *image, int theta_inc, int pixel_threshold) {
  auto *hough_accum = new Hough_accum(theta_inc, image->get_rows(), image->get_cols());
  hough_accum->initialize(image, pixel_threshold);
  return hough_accum;
}

void Hough_accum::find_peaks(int rho_size, int theta_size, int threshold_count) {
  peaks.clear();
  for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
      Hough_peak hough_peak;
      double rho = Polar_trig::rho_index_to_rho(rho_index, get_nrhos());
      if (is_maximum(hough_peak, rho, rho_size, theta_index, theta_size, threshold_count)) {
        peaks.push_back(hough_peak);
      }
    }
  }
}

int Hough_accum::get(int rho_index, int theta_index) const {
  if (polar_trig == nullptr || rho_theta_counts == nullptr)
    return 0;
  int index = polar_trig->rho_theta_to_index(rho_index, theta_index);
  return rho_theta_counts[index];
}

/**
 * initialize_image accumulator
 * grayscale only
 *
 * @param image_theshold
 */
void Hough_accum::initialize(Image *image, int image_threshold) {
  for (int row = image->get_min_row(); row < image->get_rows(); row++) {
    for (int col = image->get_min_col(); col < image->get_cols(); col++) {
      double value = std::abs(image->get(row, col));
      if (value > image_threshold) {
        for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
          if (polar_trig != nullptr) {
            int rho_index =
                polar_trig->row_col_theta_to_rho_index(row, col, theta_index);
            update(rho_index, theta_index, wb_utils::double_to_int_round(value));
          }
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
                             int threshold_count) const {
  int rho_index_low = std::max(rho_index - rho_size / 2, 0);
  int rho_index_high = std::min(rho_index + rho_size / 2, get_nrhos() - 1);
  int theta_index_low = std::max(theta_index - theta_size / 2, 0);
  int theta_index_high = std::min(theta_index + theta_size / 2, get_nthetas() - 1);
  if (polar_trig == nullptr || rho_theta_counts == nullptr)
    return false;
  int bin_index = polar_trig->rho_theta_to_index(rho_index, theta_index);
  int bin_count = rho_theta_counts[bin_index];
  if (bin_count < threshold_count)
    return false;
  int next_highest = 0;
  for (int i = theta_index_low; i <= theta_index_high; i++)
    for (int j = rho_index_low; j <= rho_index_high; j++) {
      if (theta_index != i || rho_index != j) {
        int index = polar_trig->rho_theta_to_index(j, i);
        int neighbor_bin_count = rho_theta_counts[index];
        if (neighbor_bin_count > bin_count)
          return false;
        if (neighbor_bin_count > next_highest)
          next_highest = neighbor_bin_count;
      }
    }
  hough_peak.set_theta_index(theta_index);
  hough_peak.set_rho(rho_index, get_nrhos());
  hough_peak.set_count(bin_count);
  int difference = bin_count - next_highest;
  hough_peak.set_total_difference(bin_count - next_highest);
  double percentage_difference = (bin_count == 0 ? 0.0 : ((double) difference) / bin_count);
  hough_peak.set_percent_difference(percentage_difference);
  return true;
}

Hough_accum *Hough_accum::read(FILE *fp, Errors &errors) {
  int theta_inc;
  wb_utils::read_int(fp,
                     theta_inc,
                     "Hough_accum::read",
                     "",
                     "missing hough accumulator theta_inc",
                     errors);
  int rows;
  if (!errors.has_error())
    wb_utils::read_int(fp, rows, "Hough_accum::read", "", "missing hough accumulator get_rows()", errors);
  int cols;
  if (!errors.has_error())
    wb_utils::read_int(fp, cols, "Hough_accum::read", "", "missing hough accumulator get_cols()", errors);
  if (errors.has_error())
    return nullptr;
  else {
    auto *hough_accum = new Hough_accum(theta_inc, rows, cols);
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
/*
Hough_accum *Hough_accum::read_text(std::ifstream &ifs, Errors &errors) {
  auto *hough_accum = new Hough_accum();
  std::string line;
  while (getline(ifs, line)) {
    std::vector<std::string> values = wb_utils::string_split(line);
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
*/

void Hough_accum::set(int rho_index, int theta_index, int value) const {
  if (polar_trig != nullptr && rho_theta_counts != nullptr) {
    int index = polar_trig->rho_theta_to_index(rho_index, theta_index);
    rho_theta_counts[index] = value;
  }
}

void Hough_accum::update(int rho_index, int theta_index, int value) const {
  if (polar_trig != nullptr && rho_theta_counts != nullptr) {
    int index = polar_trig->rho_theta_to_index(rho_index, theta_index);
    rho_theta_counts[index] += value;
  }
}

void Hough_accum::update_accumulator_stats() {
  for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
      accumulator_stats.update(get(rho_index, theta_index));
    }
  }
}

void Hough_accum::write(FILE *fp, Errors &errors) const {
  int theta_inc = get_theta_inc();
  fwrite(&theta_inc, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_accum::write", "", "cannot write Hough accumulator theta_inc");
    return;
  }
  int rows = get_rows();
  fwrite(&rows, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_accum::write", "", "cannot write Hough accumulator get_rows()");
    return;
  }
  int cols = get_cols();
  fwrite(&cols, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_accum::write", "", "cannot write Hough accumulator get_cols()");
    return;
  }
  size_t newLen;
  newLen = fwrite(rho_theta_counts, sizeof(int), nbins, fp);
  if (ferror(fp) != 0 || newLen != nbins) {
    errors.add("Hough_accum::write", "", "cannot write Hough accumulator data ");
    return;
  }
}

void Hough_accum::write_peak_lines(FILE *fp, Errors &errors) const {
  size_t npeaks = peaks.size();
  fwrite(&npeaks, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough::write_peak_lines", "", "cannot write Hough peak line count");
    return;
  }
  int theta_inc = Hough_accum::get_theta_inc();
  fwrite(&theta_inc, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough::write_peak_lines", "", "cannot write Hough theta_inc  ");
    return;
  }
  int nrhos = get_nrhos();
  fwrite(&nrhos, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough::write_peak_lines", "", "cannot write Hough nrhos ");
    return;
  }
  for (Hough_peak peak: peaks) {
    peak.write(fp, errors);
    if (errors.has_error())
      break;
  }
}

void Hough_accum::write_peak_lines_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  for (Hough_peak peak: peaks) {
    peak.write_text(ofs, delim, errors);
    if (errors.has_error())
      break;
  }
}

void Hough_accum::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  if (polar_trig != nullptr) {
    ofs << delim;
    for (int rho_index = 0; rho_index <= get_nrhos(); rho_index++)
      ofs << polar_trig->rho_index_to_rho(rho_index) << delim;
    ofs << std::endl;
  }
  for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
    ofs << Polar_trig::theta_index_to_theta(theta_index) << delim;
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
      ofs << get(rho_index, theta_index) << delim;
    }
    ofs << std::endl;
  }
}




