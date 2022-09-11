//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include <iostream>
#include <sstream>
#include "polar_line.hpp"
#include "polar_trig.hpp"

Polar_line::Polar_line(
    double m_rho,
    int m_rho_index,
    int m_theta_index):
 rho(m_rho),
 rho_index(m_rho_index),
 theta_index(m_theta_index) { }

  Polar_line *Polar_line::from_theta_index_rho(int theta_index,
                                         double rho,
                                         int nrhos){
  return new Polar_line(rho, Polar_trig::get)
}
  Polar_line *Polar_line::from_theta_index_rho_index(int theta_index,
                                               int rho_index,
                                               int nrhos){

}
  Polar_line *Polar_line::from_theta_rho(int theta,
                                   int rho){

}
  Polar_line *Polar_line::from_theta_rho_index(int theta,
                                         int rho_index){

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
  ofs << rho_index << delim << theta_index << delim << count << std::endl;
}