#include <cmath>
#include <fstream>
#include <iostream>
#include "theta.hpp"

double deg_to_rad(double deg) {
  return deg * 3.14159 / 180.0;
}

/**
 * This is a program that reads a tab-delimited text image file and writes it out as an internal binary format file.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  std::ofstream ofs("theta_static.hpp", std::ofstream::out);
  ofs << "const double Theta::cos_theta_table[max_thetas] = {" << std::endl;
  for (int theta = 0; theta < max_thetas; theta++) {
    double theta_degrees = theta / theta_factor;
    ofs << cos(deg_to_rad(theta_degrees))
        << (theta < max_thetas - 1 ? "," : "") << std::endl;
  }
  ofs << "};" << std::endl << std::endl;

  ofs << "const double Theta::sin_theta_table[max_thetas] = {" << std::endl;
  for (int theta = 0; theta < max_thetas; theta++) {
    double theta_degrees = theta / theta_factor;
    ofs << sin(deg_to_rad(theta_degrees))
        << (theta < max_thetas - 1 ? "," : "") << std::endl;
  }
  ofs << "};" << std::endl;
  ofs.close();
}
