//
// Created by kushn on 6/27/2022.
//

#include <cmath>
#include "hough_trig.hpp"

Hough_trig::Hough_trig() {
}

void Hough_trig::init(int m_theta_inc) {
  theta_inc = m_theta_inc;
  nthetas = 180 / theta_inc;

  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    hough_cos[theta_index] = std::cos(deg_to_rad(index_to_deg(theta_index)));
  }

  for (int theta_index = 0; theta_index < nthetas; theta_index ++) {
    hough_sin[theta_index] = std::sin(deg_to_rad(index_to_deg(theta_index)));
  }
}

float Hough_trig::deg_to_rad(float deg) {
  return deg * 3.14159 / 180.0;
}

int Hough_trig::index_to_deg(int index) {
  return index * Hough_trig::theta_inc;
}

float Hough_trig::cos(int theta_index) {
  return hough_cos[theta_index];
}

float Hough_trig::sin(int theta_index) {
  return hough_sin[theta_index];
}