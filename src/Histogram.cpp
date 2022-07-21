//
// Created by kushn on 6/11/2022.
//

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include "errors.hpp"
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "histogram.hpp"

extern bool debug;

Histogram::~Histogram() {
  delete bins;
}

Histogram::Histogram(Image *m_image,
                     int m_nbins,
                     double m_lower_value,
                     double m_upper_value) :
    image(m_image),
    nbins(m_nbins),
    lower_value(m_lower_value),
    upper_value(m_upper_value) {
  bins = new int[nbins];
  for (int i = 0; i < nbins; i++)
    bins[i] = 0;
  initialize();
}

int Histogram::get_bin(double value) const {
  if (value < lower_value)
    return 0;
  else if (value > upper_value)
    return nbins - 1;
  else
    return wb_utils::round_double_to_int((nbins - 1) * (value - lower_value) / (upper_value - lower_value));
}

double Histogram::get_lower_value() const {
  return lower_value;
}

double Histogram::get_max_value() const {
  return stats.get_max_value();
}

double Histogram::get_min_value() const {
  return stats.get_min_value();
}

double Histogram::get_upper_value() const {
  return upper_value;
}

void Histogram::initialize() {
  for (int row = 0; row < image->get_rows(); row++) {
    for (int col = 0; col < image->get_cols(); col++) {
      double value = image->get(row, col);
      update(value);
    }
  }
  update_stats();
}

void Histogram::update_stats() {
  for (int i = 0; i < nbins; i++) {
    stats.update(bins[i]);
  }
}

void Histogram::read(const std::string &path, Errors &errors) {
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == nullptr) {
    errors.add("Histogram::read", "", "invalid file '" + path + "' " + std::string(strerror(errno)) + "'");
  } else {
    wb_utils::read_int(fp, nbins, "Histogram::read", "", "missing histogram nbins in '" + path + "'", errors);
    if (errors.error_ct == 0)
      wb_utils::read_double(fp,
                            lower_value,
                            "Histogram::read",
                            "",
                            "missing histogram read_double in '" + path + "'",
                            errors);
    if (errors.error_ct == 0)
      wb_utils::read_double(fp,
                            upper_value,
                            "Histogram::read",
                            "",
                            "missing histogram upper_value in '" + path + "'",
                            errors);
    if (errors.error_ct == 0)
      wb_utils::read_int_buffer(fp,
                                bins,
                                nbins,
                                "Histogram::read",
                                "",
                                "cannot read histogram data in '" + path + "'",
                                errors);
  }
}

std::string Histogram::to_string() {
  std::ostringstream os;
  os << "nbins " << nbins
     << " lower_value " << lower_value
     << " upper_value " << upper_value
     << " stats " << stats.to_string();
  return os.str();
}

void Histogram::update(double new_value) const {
  int bin = get_bin(new_value);
  bins[bin]++;
}

void Histogram::write(const std::string &path, Errors &errors) {
  if (debug)
    std::cout << "Histogram::write path '" << path << "' " << to_string() << std::endl;
  FILE *fp = fopen(path.c_str(), "w");
  if (fp == nullptr) {
    errors.add("Image::write", "", "invalid file '" + path + "'");
  }
  wb_utils::write_int(fp, nbins, "Histogram::write", "", "cannot write nbins to '" + path + "'", errors);
  if (errors.error_ct == 0)
    wb_utils::write_float(fp,
                          wb_utils::double_to_float(lower_value),
                          "Histogram::write", "", "cannot write lower_value to '" + path + "'",
                          errors);
  if (errors.error_ct == 0)
    wb_utils::write_float(fp,
                          wb_utils::double_to_float(upper_value),
                          "Histogram::write", "", "cannot write upper_value to '" + path + "'",
                          errors);
  if (errors.error_ct == 0)
    stats.write(fp, path, errors);
  if (errors.error_ct == 0)
    wb_utils::write_int_buffer(fp, bins, nbins, "Histogram::write", "", "cannot write bins to '" + path + "'", errors);
  fclose(fp);
}

void Histogram::write_text(const std::string &path, const std::string &delim, Errors &errors) {
  if (debug)
    std::cout << "Histogram::write_text path '" << path << "' " << to_string() << std::endl;
  std::ofstream ofs(path, std::ofstream::out);
  if (!ofs) {
    errors.add("Histogram::write_text", "", "invalid file '" + path + "'");
    return;
  }
  ofs << "nbins " << nbins
      << " lower_value " << lower_value
      << " upper_value " << upper_value
      << stats.to_string()
      << std::endl;
  for (int i = 0; i < nbins; i++)
    ofs << i << delim;
  ofs << std::endl;
  for (int i = 0; i < nbins; i++)
    ofs << bins[i] << delim;
  ofs << std::endl;
  ofs.close();
}

