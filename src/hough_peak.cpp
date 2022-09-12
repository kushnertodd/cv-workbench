//
// Created by kushn on 6/11/2022.
//

#include <cstring>
#include "errors.hpp"
#include "file_utils.hpp"
#include "hough_accum.hpp"
#include "theta.hpp"
#include "wb_utils.hpp"
#include "wb_window.hpp"

Hough_peak::~Hough_peak() = default;

Hough_peak::Hough_peak(Polar_line &m_polar_line,
                       int m_count,
                       int m_total_difference,
                       float m_percent_difference) :
    polar_line(m_polar_line),
    count(m_count),
    total_difference(m_total_difference),
    percent_difference(m_percent_difference) {}

Hough_peak::Hough_peak(Polar_line &m_polar_line) :
    polar_line(m_polar_line),
    count(0),
    total_difference(0),
    percent_difference(0.0) {}

void Hough_peak::read(const std::string &path, std::list<Hough_peak> &hough_peaks, Errors &errors) {
  FILE *fp = file_utils::open_file_read(path, errors);
  if (fp) {
    read(fp, hough_peaks, errors);
    fclose(fp);
  }
}

void Hough_peak::read(FILE *fp, std::list<Hough_peak> &hough_peaks, Errors &errors) {
  while (!errors.has_error() && !feof(fp)) {
    Hough_peak hough_peak;
    hough_peak.read(fp, errors);
    if (!errors.has_error()) {
      hough_peaks.emplace_back(hough_peak);
    }
  }
}

void Hough_peak::read(FILE *fp, Errors &errors) {
  polar_line.read(fp, errors);
  if (!errors.has_error())
    wb_utils::read_int(fp, count, "Hough_peak::read", "", "missing count", errors);
  if (!errors.has_error())
    wb_utils::read_int(fp, total_difference, "Hough_peak::read", "", "missing total_difference", errors);
  float percent_difference_float;
  if (!errors.has_error())
    wb_utils::read_float(fp, percent_difference_float, "Hough_peak::read", "", "missing percent_difference", errors);
  if (!errors.has_error())
    percent_difference = percent_difference_float;
}

void Hough_peak::read_text(const std::string &path, std::list<Hough_peak> &hough_peaks, Errors &errors) {
  std::ifstream ifs = file_utils::open_file_read_text(path, errors);
  if (ifs) {
    read_text(ifs, hough_peaks, errors);
    ifs.close();
  }
}

/**
 * convert tab-delimited file to hough peak
 * note: skips count, total_difference, percentage_difference
 * grayscale only
 * @param ifs
 * @param errors
 * @return
 */
void Hough_peak::read_text(std::ifstream &ifs, std::list<Hough_peak> &hough_peaks, Errors &errors) {
  std::string line;
  for (int count = 1; !errors.has_error() && getline(ifs, line); count++) {
    std::vector<std::string> values = wb_utils::string_split(line);
    Polar_line polar_line;
    polar_line.read_text(values, errors);
    if (!errors.has_error())
      hough_peaks.emplace_back(polar_line);
  }
}

void Hough_peak::write(const std::string &path, std::list<Hough_peak> &hough_peaks, Errors &errors) {
  FILE *fp = file_utils::open_file_write(path, errors);
  if (fp) {
    write(fp, hough_peaks, errors);
    fclose(fp);
  }
}

void Hough_peak::write(FILE *fp, std::list<Hough_peak> &hough_peaks, Errors &errors) {
  for (Hough_peak &hough_peak: hough_peaks)
    hough_peak.write(fp, errors);
}

void Hough_peak::write(FILE *fp, Errors &errors) {
  polar_line.write(fp, errors);
  if (!errors.has_error())
    wb_utils::write_int(fp,
                        count,
                        "Hough_peak::write",
                        "",
                        "cannot write Hough peak count ",
                        errors);
  if (!errors.has_error())
    wb_utils::write_int(fp,
                        total_difference,
                        "Hough_peak::write",
                        "",
                        "cannot write Hough peak total_difference ",
                        errors);
  if (!errors.has_error()) {
    float percent_difference_float = wb_utils::double_to_float(percent_difference);
    wb_utils::write_float(fp,
                          percent_difference_float,
                          "Hough_peak::write",
                          "",
                          "cannot write Hough peak percent_difference ",
                          errors);
  }
}

void Hough_peak::write_text(const std::string &path, std::list<Hough_peak> &hough_peaks, Errors &errors) {
  std::ofstream ofs = file_utils::open_file_write_text(path, errors);
  if (ofs) {
    write_text(ofs, hough_peaks, "\t");
    ofs.close();
  }
}

void Hough_peak::write_text(std::ofstream &ofs, std::list<Hough_peak> &hough_peaks, const std::string &delim) {
  for (Hough_peak &hough_peak: hough_peaks)
    hough_peak.write_text(ofs, delim);
}

void Hough_peak::write_text(std::ofstream &ofs, const std::string &delim) const {
  polar_line.write_text(ofs, delim);
  ofs << delim;
  ofs << count << delim;
  ofs << total_difference << delim;
  ofs << percent_difference << delim;
  ofs << std::endl;
}




