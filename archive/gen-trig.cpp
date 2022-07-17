#include <cmath>
#include <fstream>
#include <iostream>

//

float deg_to_rad(float deg) {
  return deg * 3.14159 / 180.0;
}

const int theta_inc = 3;

int main(int argc, char **argv) {

  std::ofstream ofs ("hough_theta.hpp", std::ofstream::out);
  ofs << "float hough_cos[] = {" << std::endl;
  for (int theta = 0; theta < 180; theta += theta_inc) {
    ofs << cos(deg_to_rad(theta))
    << (theta < 180 - theta_inc ? "," : "") << std::endl;
  }
  ofs << "};" << std::endl << std::endl;
  
  ofs << "float hough_sin[] = {" << std::endl;
  for (int theta = 0; theta < 180; theta += theta_inc) {
    ofs << sin(deg_to_rad(theta))
    << (theta < 180 - theta_inc ? "," : "") << std::endl;
  }
  ofs << "};" << std::endl;
  ofs.close();
  
}
