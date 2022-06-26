#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

float deg_to_rad(float deg) {
  return deg * 3.14159 / 180.0;
}

int main(int argc, char **argv) {

  ofstream ofs ("hough_theta.hpp", ofstream::out);
  ofs << "float hough_cos[] = {" << endl;
  for (int theta = 0; theta < 180; theta += 3) {
    ofs << cos(deg_to_rad(theta)) << (theta < 177 ? "," : "") << endl;
  }
  ofs << "};" << endl << endl;
  
  ofs << "float hough_sin[] = {" << endl;
  for (int theta = 0; theta < 180; theta += 3) {
    ofs << sin(deg_to_rad(theta)) << (theta < 177 ? "," : "") << endl;
  }
  ofs << "};" << endl;
  ofs.close();
  
}
