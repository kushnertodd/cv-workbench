//
// Created by kushn on 6/27/2022.
//

#include <cmath>
#include "hough_trig_alt.hpp"

Hough_trig_alt::Hough_trig_alt() {
}

void Hough_trig_alt::init(int m_theta_inc) {
  theta_inc = m_theta_inc;
  nthetas = 180 / theta_inc;

  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    hough_cos[theta_index] = std::cos(deg_to_rad(index_to_theta(theta_index)));
  }

  for (int theta_index = 0; theta_index < nthetas; theta_index ++) {
    hough_sin[theta_index] = std::sin(deg_to_rad(index_to_theta(theta_index)));
  }
}

float Hough_trig_alt::deg_to_rad(float deg) {
  return deg * 3.14159 / 180.0;
}

int Hough_trig_alt::index_to_theta(int index) {
  return index * Hough_trig_alt::theta_inc;
}

float Hough_trig_alt::cos(int theta_index) {
  return hough_cos[theta_index];
}

float Hough_trig_alt::sin(int theta_index) {
  return hough_sin[theta_index];
}