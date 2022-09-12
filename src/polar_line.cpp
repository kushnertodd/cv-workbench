//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include <iostream>
#include <sstream>
#include "file_utils.hpp"
#include "polar_line.hpp"
#include "theta.hpp"
#include "wb_utils.hpp"

Polar_line::Polar_line() = default;
Polar_line::Polar_line(double m_rho,
                       Theta m_theta) :
    rho(m_rho),
    theta(m_theta) {}

Polar_line::Polar_line(double m_rho,
           int theta_degrees):
    rho(m_rho) {
    theta.set_theta_degrees(theta_degrees);
}

/**
 * Read binary file image header
 * @param fp
 * @param errors
 */
void Polar_line::read(FILE *fp, Errors &errors) {
  float rho_float;
  wb_utils::read_float(fp, rho_float, "Polar_line::read_header", "", "missing polar line rho", errors);
  if (!errors.has_error()) {
    rho = rho_float;
    int theta_degrees;
    wb_utils::read_int(fp, theta_degrees, "Polar_line::read_header", "", "missing polar line theta degrees", errors);
    theta.set_theta_degrees(theta_degrees);
  }
}

/**
 * convert tab-delimited file to image
 * grayscale only
 * @param ifs
 * @param errors
 * @return
 */
void Polar_line::read_text(std::vector<std::string> &values, Errors &errors) {
  if (values.size() < 2) {
    errors.add("Polar_line::read_text", "", "missing values");
  }
  if (!errors.has_error()) {
    std::string rho_string = values.at(0);
    if (!wb_utils::string_to_double(rho_string, rho))
      errors.add("Polar_line::read_text", "", "invalid polar line rho");
  }
  if (!errors.has_error()) {
    std::string theta_degrees_string = values.at(1);
    int theta_degrees;
    if (!wb_utils::string_to_int(theta_degrees_string, theta_degrees))
      errors.add("Hough_peak::read_text", "", "invalid polar line theta degrees");
    else
      theta.set_theta_degrees(theta_degrees);
  }
}

void Polar_line::set(double m_rho, int theta_degrees) {
  rho = m_rho;
  theta.set_theta_degrees(theta_degrees);
}

std::string Polar_line::to_string() const {
  std::ostringstream os;
  os << " rho " << rho
     << " theta " << theta.to_string();
  return os.str();
}

void Polar_line::write(FILE *fp, Errors &errors) {
  float rho_float = wb_utils::double_to_float(rho);
  wb_utils::write_float(fp,
                        rho_float,
                        "Polar_line::write",
                        "",
                        "cannot write Polar_line rho ",
                        errors);

  if (!errors.has_error()) {
    int theta_degrees = theta.get_theta_degrees();
    wb_utils::write_int(fp,
                        theta_degrees,
                        "Polar_line::write",
                        "",
                        "cannot write Polar_line theta_degrees ",
                        errors);
  }
}

void Polar_line::write_text(std::ofstream &ofs, const std::string &delim) const {
  ofs << rho << delim << theta;
}