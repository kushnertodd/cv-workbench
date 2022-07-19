//
// Created by kushn on 6/27/2022.
//

#include <algorithm>
#include <list>
#include <iostream>
#include <sstream>
#include "polar_line.hpp"

extern bool debug;

/**
 * initialize (rho, theta) line
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

