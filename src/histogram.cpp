//
// Created by kushn on 6/11/2022.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include "errors.hpp"
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "polar_trig.hpp"
#include "histogram.hpp"

extern bool debug;

Histogram::~Histogram() {
  delete bins;
}

Histogram::Histogram() = default;

Histogram::Histogram(int m_nbins,
                     double m_lower_value,
                     double m_upper_value) :
    nbins(m_nbins),
    lower_value(m_lower_value),
    upper_value(m_upper_value) {
  bins = new int[nbins];
  for (int i = 0; i < nbins; i++)
    bins[i] = 0;
}

Histogram *Histogram::create_image(Image *image,
                                   int nbins,
                                   double lower_value,
                                   double upper_value,
                                   bool saw_lower_value,
                                   bool saw_upper_value) {
  auto *histogram = new Histogram(nbins, lower_value, upper_value);
  histogram->initialize_image(image, saw_lower_value, saw_upper_value);
  return histogram;
}

Histogram *Histogram::create_hough(Hough *hough,
                                   int nbins,
                                   double lower_value,
                                   double upper_value,
                                   bool saw_lower_value,
                                   bool saw_upper_value) {
  auto *histogram = new Histogram(nbins, lower_value, upper_value);
  histogram->initialize_hough(hough, saw_lower_value, saw_upper_value);
  return histogram;
}

void Histogram::find_hough_peaks(Hough *hough, int npeaks) {
  const int nbins = 1000;
  Histogram *histogram = create_hough(hough, nbins, 0, 0, false, false);
  int peak_ct = 0;
  double threshold = 0.0;
  for (int i = nbins - 1; i >= 0 && peak_ct < npeaks; i--) {
    peak_ct += histogram->bins[i];
    if (peak_ct <= npeaks) {
      threshold = histogram->get_value(i);
    }
  }
  hough->hough_accum->find_peaks(hough->lines, threshold);
}

int Histogram::get_bin(double value) const {
  if (value < lower_value)
    return 0;
  else if (value > upper_value)
    return nbins - 1;
  else
    return wb_utils::double_to_int_round((nbins - 1) * (value - lower_value) / (upper_value - lower_value));
}

float Histogram::get_value(int bin) const {
  return wb_utils::double_to_float(bin * (upper_value - lower_value) / (nbins - 1) + lower_value);
}

double Histogram::get_lower_value() const {
  return lower_value;
}

double Histogram::get_max_value() const {
  return input_value_stats.get_max_value();
}

double Histogram::get_min_value() const {
  return input_value_stats.get_min_value();
}

double Histogram::get_upper_value() const {
  return upper_value;
}

void Histogram::initialize_hough(Hough *hough, bool saw_lower_value, bool saw_upper_value) {
  for (int theta_index = 0; theta_index < Polar_trig::get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < hough->hough_accum->get_nrhos(); rho_index++) {
      double value = hough->hough_accum->get(rho_index, theta_index);
      input_value_stats.update(value);
    }
  }
  input_value_stats.finalize();
  if (!saw_lower_value)
    lower_value = input_value_stats.get_min_value();
  if (!saw_upper_value)
    upper_value = input_value_stats.get_max_value();
  for (int theta_index = 0; theta_index < Polar_trig::get_nthetas(); theta_index++) {
    for (int rho_index = 0; rho_index < hough->hough_accum->get_nrhos(); rho_index++) {
      double value = hough->hough_accum->get(rho_index, theta_index);
      update_input_value(value);
    }
  }
  update_bin_count_bounds();
}

void Histogram::initialize_image(Image *image, bool saw_lower_value, bool saw_upper_value) {
  for (int row = 0; row < image->get_rows(); row++) {
    for (int col = 0; col < image->get_cols(); col++) {
      double value = image->get(row, col);
      input_value_stats.update(value);
    }
  }
  input_value_stats.finalize();
  if (!saw_lower_value)
    lower_value = input_value_stats.get_min_value();
  if (!saw_upper_value)
    upper_value = input_value_stats.get_max_value();
  for (int row = 0; row < image->get_rows(); row++) {
    for (int col = 0; col < image->get_cols(); col++) {
      double value = image->get(row, col);
      update_input_value(value);
    }
  }
  update_bin_count_bounds();
}

void Histogram::log(std::list<WB_log_entry> &log_entries) {
  WB_log_entry log_entry_lower_value("lower_value", wb_utils::double_to_string(lower_value));
  log_entries.push_back(log_entry_lower_value);
  WB_log_entry log_entry_upper_value("upper_value", wb_utils::double_to_string(upper_value));
  log_entries.push_back(log_entry_upper_value);
  WB_log_entry log_entry_pixel_count("pixel count", wb_utils::int_to_string(input_value_stats.get_count()));
  log_entries.push_back(log_entry_pixel_count);
  WB_log_entry log_entry_pixel_mean("pixel mean", wb_utils::double_to_string(input_value_stats.get_mean()));
  log_entries.push_back(log_entry_pixel_mean);
  WB_log_entry log_entry_pixel_standard_deviation(
      "pixel standard deviation",
      wb_utils::double_to_string(input_value_stats.get_standard_deviation()));
  log_entries.push_back(log_entry_pixel_standard_deviation);
  WB_log_entry log_entry_pixel_min_value("min pixel value",
                                         wb_utils::double_to_string(input_value_stats.get_min_value()));
  log_entries.push_back(log_entry_pixel_min_value);
  WB_log_entry log_entry_pixel_max_value("max pixel value",
                                         wb_utils::double_to_string(input_value_stats.get_max_value()));
  log_entries.push_back(log_entry_pixel_max_value);
  WB_log_entry log_entry_bin_min_count(
      "min bin count",
      wb_utils::int_to_string(wb_utils::double_to_int_round(bin_count_bounds.get_min_value())));
  log_entries.push_back(log_entry_bin_min_count);
  WB_log_entry log_entry_bin_max_count(
      "max bin count",
      wb_utils::int_to_string(wb_utils::double_to_int_round(bin_count_bounds.get_max_value())));
  log_entries.push_back(log_entry_bin_max_count);
}

Histogram *Histogram::read(std::string &path, Errors &errors) {
  FILE *fp = file_utils::open_file_read(path, errors);
  Histogram *histogram = nullptr;
  if (fp) {
    histogram = Histogram::read(fp, errors);
    fclose(fp);
  }
  return histogram;
}

Histogram *Histogram::read(FILE *fp, Errors &errors) {
  auto *histogram = new Histogram();
  if (fp == nullptr)
    return nullptr;

  wb_utils::read_int(fp, histogram->nbins, "Histogram::read", "", "missing nbins", errors);
  if (errors.has_error()) {
    delete histogram;
    return nullptr;
  }

  float lower_value_float = 0.0;
  wb_utils::read_float(fp,
                       lower_value_float, "Histogram::read", "", "missing lower_value", errors);
  if (errors.has_error()) {
    delete histogram;
    return nullptr;
  }
  histogram->lower_value = lower_value_float;

  float upper_value_float = 0.0;
  wb_utils::read_float(fp,
                       upper_value_float,
                       "Histogram::read",
                       "",
                       "missing upper_value",
                       errors);
  if (errors.has_error()) {
    delete histogram;
    return nullptr;
  }
  histogram->upper_value = upper_value_float;

  histogram->bins = new int[histogram->nbins];
  wb_utils::read_int_buffer(fp,
                            histogram->bins,
                            histogram->nbins,
                            "Histogram::read",
                            "",
                            "cannot read data",
                            errors);
  if (errors.has_error()) {
    delete histogram;
    return nullptr;
  }
  histogram->update_bin_count_bounds();
  return histogram;
}

Histogram *Histogram::read_text(const std::string& path, Errors &errors) {
  return nullptr;
}

Histogram *Histogram::read_text(std::ifstream &ifs, Errors &errors) {
  return nullptr;
}

std::string Histogram::to_string(const std::string &prefix) {
  std::ostringstream os;
  os << "histogram:" << std::endl
     << prefix << "    " << std::setw(20) << std::left << "nbins " << nbins << std::endl
     << prefix << "    " << std::setw(20) << std::left << "lower_value " << lower_value << std::endl
     << prefix << "    " << std::setw(20) << std::left << "upper_value " << upper_value << std::endl
     << prefix << "    " << bin_count_bounds.to_string(prefix + "    ")
     << prefix << "    " << input_value_stats.to_string(prefix + "    ");
  return os.str();
}

void Histogram::update_input_value(double value) const {
  int bin = get_bin(value);
  bins[bin]++;
}

void Histogram::update_bin_count_bounds() {
  for (int i = 0; i < nbins; i++)
    bin_count_bounds.update(bins[i]);
}

void Histogram::write(std::string &path, Errors &errors) const {  }

void Histogram::write(FILE *fp, Errors &errors) const {
  wb_utils::write_int(fp, nbins, "Histogram::write", "", "cannot write nbins", errors);
  if (!errors.has_error())
    wb_utils::write_float(fp,
                          wb_utils::double_to_float(lower_value),
                          "Histogram::write", "", "cannot write lower_value",
                          errors);
  if (!errors.has_error())
    wb_utils::write_float(fp,
                          wb_utils::double_to_float(upper_value),
                          "Histogram::write", "", "cannot write upper_value",
                          errors);
  if (!errors.has_error())
    input_value_stats.write(fp, errors);
  if (!errors.has_error())
    wb_utils::write_int_buffer(fp, bins, nbins, "Histogram::write", "", "cannot write bins'", errors);
}

void Histogram::write_gp_script(const Wb_filename &wb_filename) {
  std::string script_filename = wb_filename.to_hist_script();
  std::string data_filename = wb_filename.to_hist_text();
  std::ofstream ofs(script_filename, std::ofstream::out);
  ofs << "set style data histograms" << std::endl;
  ofs << "plot './" << data_filename << "' using 2:xtic(10)" << std::endl;
  ofs << "pause -1 \"Hit any key to continue\"" << std::endl;
  ofs.close();
}

// path excludes extension, so write_text() can add .txt for text and .gp for gnuplot script
void Histogram::write_text(std::string &path, const std::string &delim, Errors &errors) const {
  Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::TEXT);
  std::ofstream ofs = file_utils::open_file_write_text(wb_filename.to_hist_text(), errors);
  if (!ofs) {
    errors.add("Histogram::write_text", "", "invalid file '" + path + "'");
    return;
  }
  ofs << "bin" << delim << "count" << std::endl;
  for (int i = 0; i < nbins; i++)
    ofs << get_value(i) << delim << bins[i] << std::endl;
  ofs << std::endl;
  ofs.close();
  write_gp_script(wb_filename);
}


 
