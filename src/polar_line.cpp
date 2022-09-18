//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include <iostream>
#include <sstream>
#include "file_utils.hpp"
#include "point.hpp"
#include "polar_line.hpp"
#include "theta.hpp"
#include "wb_utils.hpp"

Polar_line::Polar_line() = default;

Polar_line::Polar_line(double m_rho,
                       int theta_degrees) :
    rho(m_rho) {
  theta.set_theta_degrees(theta_degrees);
}

// can have a singularity if theta ~= , 180, sin ~= 0
int Polar_line::col_to_row(int col, int rows, int cols) const {
  double x = Point::col_to_x(col, cols);
  double cos_t = to_cos();
  double sin_t = to_sin();
  double row_offset = rows / 2.0;
  double row = row_offset + (x * cos_t - rho) / sin_t;
  return wb_utils::double_to_int_round(row);
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

// can have a singularity if theta ~= 90, cos ~= 0
int Polar_line::row_to_col(int row, int rows, int cols) const {
  double y = Point::row_to_y(row, rows);
  double cos_t = to_cos();
  double sin_t = to_sin();
  double col_offset = cols / 2.0;
  double col = (rho - y * sin_t) / cos_t + col_offset;
  return wb_utils::double_to_int_round(col);
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