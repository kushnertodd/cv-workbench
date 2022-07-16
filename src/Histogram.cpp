//
// Created by kushn on 6/11/2022.
//

#include <cmath>
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

Histogram::Histogram(int m_nbins,
                     float m_min_value,
                     float m_max_value) :
    nbins(m_nbins),
    min_value(m_min_value),
    max_value(m_max_value),
    bounds(min_value, max_value) {
  bins = new int[nbins];
  for (int i = 0; i < nbins; i++)
    bins[i] = 0;
}

int Histogram::get_bin(float value) const {
  if (value < min_value)
    return 0;
  else if (value > max_value)
    return nbins - 1;
  else
    return std::round((nbins - 1) * (value - min_value) / (max_value - min_value));
}

float Histogram::get_max_value() const {
  return bounds.get_max_value();
}

float Histogram::get_min_value() const {
  return bounds.get_min_value();
}

bool Histogram::read(std::ifstream &ifs, Errors &errors) {
/*
  string line;
  while (getline(ifs, line)) {
    vector<string> values = file_utils::string_split(line);
    for (std::string value_str: values) {
      int value;
      if (!wb_utils::string_to_int(value_str, value))
        errors.add("Hough_accum::read", "", "invalid value '" + value_str + "'");
      return false;
    }
  }
*/
  return true;
}

std::string Histogram::to_string() {
  std::ostringstream os;
  os << "nbins " << nbins
     << " min_value " << min_value
     << " max_value " << max_value
     << " stats " << stats.to_string();
  return os.str();
}

void Histogram::update(float new_value) {
  int bin = get_bin(new_value);
  bins[bin]++;
  stats.update(new_value);
}

void Histogram::write(const std::string &path, Errors &errors) {
  if (debug)
    std::cout << "Histogram::write path '" << path << "' " << to_string() << std::endl;
  FILE *fp = fopen(path.c_str(), "w");
  if (fp == nullptr) {
    errors.add("Image::write", "", "invalid file '" + path + "'");
  }
  wb_utils::write_int(fp, nbins, "Histogram::write: cannot write nbins to '" + path + "'", errors);
  wb_utils::write_float(fp, min_value, "Histogram::write: cannot write min_value to '" + path + "'", errors);
  wb_utils::write_float(fp, max_value, "Histogram::write: cannot write max_value to '" + path + "'", errors);
  stats.write(fp, path, errors);
  wb_utils::write_int_buffer(fp, bins, nbins, "Histogram::write: cannot write bins to '" + path + "'", errors);
  fclose(fp);
}

void Histogram::write_text(const std::string &path, const std::string &delim, Errors &errors) {
  if (debug)
    std::cout << "Histogram::write_string path '" << path << "' " << to_string() << std::endl;
  std::ofstream ofs(path, std::ofstream::out);
  if (!ofs) {
    errors.add("Histogram::write_string", "", "invalid file '" + path + "'");
    return;
  }
  ofs << "nbins " << nbins
      << " min_value " << min_value
      << " max_value " << max_value
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

