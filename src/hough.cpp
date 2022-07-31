//
// Created by kushn on 6/11/2022.
//

#include <cstring>
#include <fstream>
#include <iostream>
#include "errors.hpp"
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "hough_accum.hpp"
#include "hough.hpp"

extern bool debug;

Hough::~Hough() {
  delete hough_accum;
}

/**
 * For reading a Hough
 * @param m_hough_accum
 * @param m_hough_accum
 * @param m_theta_inc
 * @param m_threshold
 */
Hough::Hough(Hough_accum *m_hough_accum) :
    hough_accum(m_hough_accum) {
}

Hough *Hough::create_image(Image *image, int theta_inc, int pixel_threshold) {
  if (debug)
    std::cout << "Hough::Hough image " << image->to_string() << " theta_inc " << theta_inc << std::endl;
  auto *hough_accum = Hough_accum::create_image(image, theta_inc, pixel_threshold);
  auto *hough = new Hough(hough_accum);
  return hough;
}

void Hough::find_lines() {
  find_peaks();
  lines_to_line_segments();
}

void Hough::find_peaks() {
  int peak_threshold = hough_accum->choose_threshold(cv_enums::WB_threshold_type::FIXED);
  hough_accum->find_peaks(lines, peak_threshold);
  if (debug) {
    for (Polar_line line: lines) {
      std::cout << "Hough::find_peaks: lines " << line.to_string() << std::endl;
    }
  }
}

void Hough::lines_to_line_segments() {
  for (Polar_line line: lines) {
    Line_segment line_segment;
    if (hough_accum->clip_window(line_segment, line))
      line_segments.push_back(line_segment);
  }
}

Hough *Hough::read(const std::string &path, Errors &errors) {
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == nullptr) {
    errors.add("Image::read", "", "invalid file '" + path + "' " + std::string(strerror(errno)) + "'");
    return nullptr;
  }
  Hough_accum *hough_accum = Hough_accum::read(fp, path, errors);
  if (hough_accum == nullptr || errors.has_error())
    return nullptr;
  fclose(fp);
  return new Hough(hough_accum);
}

// NRFPT
Hough *Hough::read_text(const std::string &path, Errors &errors) {
  std::ifstream ifs(path, std::ofstream::in);
  if (!ifs) {
    errors.add("read_text:read", "", "invalid filename '" + path + "'");
    return nullptr;
  }
  Hough_accum *hough_accum = Hough_accum::read_text(ifs, errors);
  if (hough_accum == nullptr || errors.has_error())
    return nullptr;
  ifs.close();
  return new Hough(hough_accum);
}

void Hough::write(const std::string &path, Errors &errors) const {
  if (debug)
    std::cout << "Image::write path '" << path << std::endl;
  FILE *fp = fopen(path.c_str(), "w");
  if (fp == nullptr) {
    errors.add("Hough::write", "", "invalid file '" + path + "'");
  }
  hough_accum->write(fp, path, errors);
  fclose(fp);
}

void Hough::write_text(const std::string &filename, const std::string &delim, Errors &errors) const {
  std::ofstream ofs(filename, std::ofstream::out);
  if (!ofs) {
    errors.add("Hough:write", "", "invalid filename '" + filename + "'");
  }
  hough_accum->write_text(ofs, "\t", errors);
  ofs.close();
}




