//
// Created by kushn on 6/11/2022.
//

#include <cstring>
#include "errors.hpp"
#include "file_utils.hpp"
#include "hough_accum.hpp"
#include "polar_trig.hpp"
#include "wb_utils.hpp"
#include "wb_window.hpp"

Hough_peak::~Hough_peak() = default;

Hough_peak::Hough_peak(double m_rho,
                       int m_theta,
                       int m_nrhos,
                       int m_count,
                       int m_total_difference,
                       float m_percent_difference) :
    count(m_count),
    total_difference(m_total_difference),
    percent_difference(m_percent_difference) {
  polar_line.set_rho(m_rho);
  polar_line.set_theta(m_theta);
  polar_line.set_nrhos(m_nrhos);
}

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

Hough_peak *from_rho_theta_index(double rho,
                                 int theta_index,
                                 int nrhos,
                                 int count,
                                 int total_difference,
                                 float percent_difference) {
  return new Hough_peak(rho,
                        Polar_trig::theta_index_to_theta(theta_index),
                        nrhos,
                        count,
                        total_difference,
                        percent_difference);
}
Hough_peak *from_rho_index_theta_index(int rho_index,
                                       int theta_index,
                                       int nrhos,
                                       int count,
                                       int total_difference,
                                       float percent_difference) {
  return new Hough_peak(Polar_trig::rho_index_to_rho(rho_index, nrhos),
                        Polar_trig::theta_index_to_theta(theta_index),
                        nrhos,
                        count,
                        total_difference,
                        percent_difference);
}
Hough_peak *from_rho_theta(int rho,
                           int theta,
                           int nrhos,
                           int count,
                           int total_difference,
                           float percent_difference) {
  return new Hough_peak(rho,
                        theta,
                        nrhos,
                        count,
                        total_difference,
                        percent_difference);
}
Hough_peak *from_rho_index_theta(int rho_index,
                                 int theta,
                                 int nrhos,
                                 int count,
                                 int total_difference,
                                 float percent_difference) {
  return new Hough_peak(Polar_trig::rho_index_to_rho(rho_index, nrhos),
                        theta,
                        nrhos,
                        count,
                        total_difference,
                        percent_difference);
}

void Hough_peak::read(const std::string &path, std::vector<Hough_peak> &peaks, Errors &errors) {
  FILE *fp = file_utils::open_file_read(path, errors);
  if (fp) {
    read(fp, peaks, errors);
    fclose(fp);
  }
}

void Hough_peak::read(FILE *fp, std::vector<Hough_peak> &peaks, Errors &errors) {
  while (!errors.has_error() && !feof(fp)) {
    Hough_peak hough_peak;
    hough_peak.read(fp, errors);
    if (!errors.has_error()) {
      peaks.push_back(hough_peak);
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
}

void Hough_peak::read_text(const std::string &path, std::vector<Hough_peak> &peaks, Errors &errors) {
  std::ifstream ifs = file_utils::open_file_read_text(path, errors);
  if (ifs) {
    read_text(ifs, peaks, errors);
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
void Hough_peak::read_text(std::ifstream &ifs, std::vector<Hough_peak> &peaks, Errors &errors) {
  std::string line;
  for (int count = 1; !errors.has_error() && getline(ifs, line); count++) {
    std::vector<std::string> values = wb_utils::string_split(line);
    Polar_line polar_line;
    polar_line.read_text(values, errors);
    peaks.push_back(polar_line);
  }
}

void Hough_peak::write(const std::string &path, Errors &errors) {
  FILE *fp = file_utils::open_file_write(path, errors);
  if (fp) {
    write(fp, errors);
    fclose(fp);
  }
}

void Hough_peak::write(FILE *fp, Errors &errors) {
  polar_line.write(fp, errors);
  if (ferror(fp) != 0)
    fwrite(&count, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak count ");
    return;
  }
  fwrite(&total_difference, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak total_difference ");
    return;
  }
  float percent_difference_float = wb_utils::double_to_float(percent_difference);
  fwrite(&percent_difference_float, sizeof(float), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak percent_difference ");
    return;
  }
}

 void write(const std::string &path, std::vector<Hough_peak> &peaks, Errors &errors) {

}
 void write(FILE *fp, std::vector<Hough_peak> &peaks, Errors &errors) {

}

void Hough_peak::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  ofs << rho << delim;
  ofs << Polar_trig::theta_index_to_theta(theta_index) << delim;
  ofs << count << delim;
  ofs << total_difference << delim;
  ofs << percent_difference << delim;
  ofs << std::endl;
}




