#include <cmath>
#include <fstream>
#include <iostream>
#include "theta.hpp"

/**
 * Produce constant cosine/sine tables in file theta_static.hpp
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  std::ofstream ofs("theta_static.hpp", std::ofstream::out);
  ofs << "const double Theta::cos_theta_table[max_thetas] = {" << std::endl;
  for (Theta theta; theta.get_theta_increment() < max_thetas; theta++) {
    ofs << cos(theta.get_theta_radians())
        << (theta.get_theta_increment() < max_thetas - 1 ? "," : "") << std::endl;
  }
  ofs << "};" << std::endl << std::endl;

  ofs << "const double Theta::sin_theta_table[max_thetas] = {" << std::endl;
  for (Theta theta; theta.get_theta_increment() < max_thetas; theta++) {
    ofs << sin(theta.get_theta_radians())
        << (theta.get_theta_increment() < max_thetas - 1 ? "," : "") << std::endl;
  }
  ofs << "};" << std::endl;
  ofs.close();
}
