//
// Created by kushn on 6/11/2022.
//

#include <cstring>
#include <iostream>
#include "errors.hpp"
#include "file_utils.hpp"
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
  lines_to_line_segments();
}

void Hough::lines_to_line_segments() {
  for (Polar_line line: lines) {
    Line_segment line_segment;
    if (hough_accum->clip_window(line_segment, line))
      line_segments.push_back(line_segment);
  }
}
Hough *Hough::read(const std::string &path, Errors &errors) {
  FILE *fp = file_utils::open_file_read(path, errors);
  Hough *hough = nullptr;
  if (fp) {
    hough = Hough::read(fp, errors);
    fclose(fp);
  }
  return hough;
}

Hough *Hough::read(FILE *fp, Errors &errors) {
  Hough_accum *hough_accum = Hough_accum::read(fp, errors);
  if (hough_accum == nullptr || errors.has_error())
    return nullptr;
  return new Hough(hough_accum);
}

// NRFPT
Hough *Hough::read_text(std::ifstream &ifs, Errors &errors) {
  Hough_accum *hough_accum = Hough_accum::read_text(ifs, errors);
  if (hough_accum == nullptr || errors.has_error())
    return nullptr;
  return new Hough(hough_accum);
}

void Hough::write(const std::string &path, Errors &errors) const {
  FILE *fp = file_utils::open_file_write(path, errors);
  if (fp) {
    write(fp, errors);
    fclose(fp);
  }
}

void Hough::write(FILE *fp, Errors &errors) const {
  hough_accum->write(fp, errors);
}

void Hough::write_text(const std::string &path, const std::string &delim, Errors &errors) const {
  std::ofstream ofs = file_utils::open_file_write_text(path, errors);
  if (ofs) {
    hough_accum->write_text(ofs, "\t", errors);
    ofs.close();
  }
}

void Hough::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  hough_accum->write_text(ofs, "\t", errors);
}

void Hough::write_peak_lines(FILE *fp, Errors &errors) const {
  size_t npeaks = lines.size();
  fwrite(&npeaks, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_header", "", "cannot write Hough peak line count");
    return;
  }
  fwrite(&hough_accum->theta_inc, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_header", "", "cannot write Hough theta_inc  ");
    return;
  }
  fwrite(&hough_accum->nrhos, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_header", "", "cannot write Hough nrhos ");
    return;
  }
  for (Polar_line line: lines) {
    line.write(fp, errors);
    if (errors.has_error())
      break;
  }
}

void Hough::write_peak_lines_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  for (Polar_line line: lines) {
    line.write_text(ofs, delim, errors);
    if (errors.has_error())
      break;
  }
}



