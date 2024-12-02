//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include <iostream>
#include <sstream>
#include "errors.hpp"
#include "polar_line.hpp"

extern bool debug;

/**
 * initialize_image (rho, theta) line
 * @param m_rho
 * @param m_theta_index
 */

Polar_line::Polar_line(int m_rho_index, double m_rho, int m_theta_index,
                       double m_cos_theta, double m_sin_theta, int m_count)
    :
    rho_index(m_rho_index),
    rho(m_rho),
    theta_index(m_theta_index),
    cos_theta(m_cos_theta),
    sin_theta(m_sin_theta),
    count(m_count) {
}

void Polar_line::set(int m_rho_index, double m_rho, int m_theta_index,
                     double m_cos_theta, double m_sin_theta, int m_count) {
  rho_index = m_rho_index;
  rho = m_rho;
  theta_index = m_theta_index;
  cos_theta = m_cos_theta;
  sin_theta = m_sin_theta;
  count = m_count;
}

std::string Polar_line::to_string() const {
  std::ostringstream os;
  os << " rho_index " << rho_index
     << " rho " << rho
     << " theta_index " << theta_index
     << " count " << count
     << " cos_theta " << cos_theta
     << " sin_theta " << sin_theta
     << " count " << count;
  return os.str();
}

void Polar_line::write(FILE *fp, Errors &errors) {
  fwrite(&rho_index, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Polar_line::write", "", "cannot write Hough rho_index");
    return;
  }
  fwrite(&theta_index, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Polar_line::write", "", "cannot write Hough theta_index");
    return;
  }
  fwrite(&count, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Polar_line::write", "", "cannot write Hough count");
  }
}

void Polar_line::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
    ofs << rho_index << delim << theta_index << delim << count<< std::endl;
}