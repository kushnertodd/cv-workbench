#include <cmath>
#include <fstream>
#include <iostream>

/*
==============================================
polar_trig.hpp
----------------------------------------------
class Polar_trig {
public:
  static const int max_thetas = 2; // 180;
  static int theta_inc;
  static const int polar_cos[max_thetas];
  static const int polar_sin[max_thetas];
};

==============================================
polar_trig_static.hpp
----------------------------------------------
const double Polar_trig::polar_cos[max_thetas] = {
  1,
  2
};
const double Polar_trig::polar_sin[max_thetas] = {
  1,
  2
};

*/

double deg_to_rad(double deg) {
  return deg * 3.14159 / 180.0;
}

const int theta_inc = 3;

int main(int argc, char **argv) {

  std::ofstream ofs("polar_trig_static.hpp", std::ofstream::out);
  ofs << "const double Polar_trig::polar_cos[max_thetas] = {" << std::endl;
  for (int theta = 0; theta < 180; theta += theta_inc) {
    ofs << cos(deg_to_rad(theta))
        << (theta < 180 - theta_inc ? "," : "") << std::endl;
  }
  ofs << "};" << std::endl << std::endl;

  ofs << "const double Polar_trig::polar_sin[max_thetas] = {" << std::endl;
  for (int theta = 0; theta < 180; theta += theta_inc) {
    ofs << sin(deg_to_rad(theta))
        << (theta < 180 - theta_inc ? "," : "") << std::endl;
  }
  ofs << "};" << std::endl;
  ofs.close();

}
