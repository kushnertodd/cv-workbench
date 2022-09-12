//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include <iostream>
#include <sstream>
#include "file_utils.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"
#include "wb_utils.hpp"

Polar_line::Polar_line(
    double m_rho,
    int m_theta,
    int m_nrhos) :
    theta(m_theta),
    nrhos(m_nrhos) {}

static Polar_line *from_rho_index_theta_index(int rho_index,
                                              int theta_index,
                                              int nrhos) {
  return new Polar_line(Polar_trig::rho_index_to_rho(rho_index, nrhos),
                        Polar_trig::theta_index_to_theta(theta_index),
                        nrhos);
}

static Polar_line *from_rho_theta_index(double rho,
                                        int theta_index,
                                        int nrhos) {
  return new Polar_line(rho,
                        Polar_trig::theta_index_to_theta(theta_index),
                        nrhos);
}

static Polar_line *from_rho_index_theta(int rho_index,
                                        int theta,
                                        int nrhos) {
  return new Polar_line(Polar_trig::rho_index_to_rho(rho_index, nrhos),
                        theta,
                        nrhos);
}

static Polar_line *from_rho_theta(int rho,
                                  int theta,
                                  int nrhos) {
  return new Polar_line(rho,
                        theta,
                        nrhos);
}

/**
 * Read binary file image header
 * @param fp
 * @param errors
 */
void Polar_line::read(FILE *fp, Errors &errors) {
  float rho_float;
  wb_utils::read_float(fp, rho_float, "Polar_line::read_header", "", "missing polar line rho", errors);
  rho = rho_float;
  if (!errors.has_error())
    wb_utils::read_int(fp, theta, "Polar_line::read_header", "", "missing polar line theta", errors);
  if (!errors.has_error())
    wb_utils::read_int(fp,
                       nrhos,
                       "Polar_line::read_header",
                       "",
                       "missing polar line nrhos",
                       errors);
}

/**
 * convert tab-delimited file to image
 * grayscale only
 * @param ifs
 * @param errors
 * @return
 */
void Polar_line::read_text(std::vector<std::string> &values, Errors &errors) {
  if (values.size() < 3) {
    errors.add("Polar_line::read_text", "", "missing values ");
  }
  if (!errors.has_error()) {
    std::string rho_string = values.at(0);
    if (!wb_utils::string_to_double(rho_string, rho))
      errors.add("Polar_line::read_text", "", "invalid rho value ");
  }
  if (!errors.has_error()) {
    std::string theta_string = values.at(1);
    if (!wb_utils::string_to_int(theta_string, theta))
      errors.add("Hough_peak::read_text", "", "invalid theta value");
  }
  if (!errors.has_error()) {
    std::string nrhos_string = values.at(2);
    if (!wb_utils::string_to_int(nrhos_string, nrhos))
      errors.add("Hough_peak::read_text", "", "invalid nrhos value");
  }
}

std::string Polar_line::to_string() const {
  std::ostringstream os;
  os << " rho " << rho
     << " theta " << theta
     << " nrhos " << nrhos;
  return os.str();
}

void Polar_line::write(FILE *fp, Errors &errors) {
  float rho_float = wb_utils::double_to_float(rho);
  fwrite(&rho_float, sizeof(float), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Polar_line::write", "", "cannot write rho");
    return;
  }
  fwrite(&theta, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Polar_line::write", "", "cannot write theta");
    return;
  }
  fwrite(&nrhos, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Polar_line::write", "", "cannot write nrhos");
  }
}

void Polar_line::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  ofs << rho << delim << theta << delim << nrhos;
}