#include <cmath>
#include <fstream>
#include <iostream>

double deg_to_rad(double deg) { return deg * 3.14159 / 180.0; }

const int theta_inc = 3;

int main(int argc, char **argv) {
    std::ofstream ofs("polar_trig_static.hpp", std::ofstream::out);
    ofs << "const double Polar_line::polar_cos[max_thetas] = {" << std::endl;
    for (int theta = 0; theta < 180; theta += theta_inc) {
        ofs << cos(deg_to_rad(theta)) << (theta < 180 - theta_inc ? "," : "") << std::endl;
    }
    ofs << "};" << std::endl << std::endl;

    ofs << "const double Polar_line::polar_sin[max_thetas] = {" << std::endl;
    for (int theta = 0; theta < 180; theta += theta_inc) {
        ofs << sin(deg_to_rad(theta)) << (theta < 180 - theta_inc ? "," : "") << std::endl;
    }
    ofs << "};" << std::endl;
    ofs.close();
}
