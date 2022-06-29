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
  hough_cos = new float[nthetas];
  hough_sin = new float[nthetas];

  for (int theta = 0; theta < 180; theta += theta_inc) {
    hough_cos[theta] = std::cos(deg_to_rad(theta));
  }

  for (int theta = 0; theta < 180; theta += theta_inc) {
    hough_sin[theta] = std::sin(deg_to_rad(theta));
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