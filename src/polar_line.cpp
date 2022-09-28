//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include <iostream>
#include <sstream>
#include "file_utils.hpp"
#include "point.hpp"
#include "theta.hpp"
#include "wb_utils.hpp"
#include "wb_window.hpp"
#include "polar_line.hpp"

Polar_line::Polar_line() = default;

Polar_line::Polar_line(double m_rho,
                       int theta_degrees) :
    rho(m_rho) {
  theta.set_theta_degrees(theta_degrees);
}

// can have a singularity if theta ~= , 180, sin ~= 0
int Polar_line::col_to_row(int col, int rows, int cols) const {
  double cos_t = to_cos();
  double sin_t = to_sin();
  if (abs(sin_t) < 1e-8)
    return INT32_MAX;
  double x = WB_window::col_to_x(col, cols);
  double row_offset = rows / 2.0;
  double row = row_offset - (rho - x * cos_t) / sin_t;
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
  double cos_t = to_cos();
  double sin_t = to_sin();
  if (abs(cos_t) < 1e-8)
    return INT32_MAX;
  double y = WB_window::row_to_y(row, rows);
  double col_offset = cols / 2.0;
  double col = col_offset + (rho - y * sin_t) / cos_t;
  return wb_utils::double_to_int_round(col);
}

void Polar_line::set(double m_rho, int theta_degrees) {
  rho = m_rho;
  theta.set_theta_degrees(theta_degrees);
}

/**
 * return arc-tangent angle for tangent in degrees
 * can have a singularity if theta ~= , 180, delta_x ~= 0
 * @return
 */
double Polar_line::to_atan(double delta_y, double delta_x) const {
  double ratio = delta_y / delta_x;
  double last_ratio = ratio;
  double last_ratio_delta = 0;
  for (int theta_increment = 0; theta_increment < max_thetas; theta_increment++) {
    double next_ratio = Theta::sin_theta_table[theta_increment] / Theta::cos_theta_table[theta_increment];
    double ratio_delta = abs(next_ratio - last_ratio);
    if (ratio_delta > last_ratio_delta)
      return theta_increment * theta_resolution;
  }
  return 0;
}

std::string Polar_line::to_string() const {
  std::ostringstream os;
  os << "(" << rho << ", " << theta.to_string() << ")";
  return os.str();
}

/**
 * return tangent for line angle
 * can have a singularity if theta ~= , 180, sin ~= 0
 * @return
 */
double Polar_line::to_tan() const {
  return to_sin() / to_cos();
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

std::ostream &operator<<(std::ostream &out, const Polar_line &polar_line) {
  out << "(" << polar_line.rho << ", " << polar_line.theta.to_string() << ")";
  return out;
}
