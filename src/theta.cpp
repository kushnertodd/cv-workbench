//
// Created by kushn on 9/12/2022.
//

#include <ostream>
#include <sstream>
#include "theta.hpp"

Theta::Theta() :
    theta_increment(0) {}

Theta::Theta(int theta_degrees) :
    theta_increment(static_cast<int>(theta_degrees / theta_resolution)) {}

// prefix increment
Theta &Theta::operator++() {
  theta_increment++;
  return *this; // return new value by reference
}

// postfix increment
const Theta Theta::operator++(int) {
  Theta old = *this; // copy old value
  theta_increment++;
  return old;    // return old value
}

int Theta::get_theta_degrees() const {
  return static_cast<int>(theta_increment * theta_resolution);
}

double Theta::get_theta_radians() const {
  return get_theta_degrees() * M_PI / max_degrees;
}

void Theta::set_theta_degrees(int theta_degrees) {
  theta_increment = static_cast<int>(theta_degrees / theta_resolution);
}

void Theta::set_theta_radians(double theta_radians) {
  theta_increment = (theta_radians / M_PI) * max_degrees / theta_resolution;
}

 inline double Theta::to_cos(int theta_degrees)  {
  int theta_increment = static_cast<int>(theta_degrees / theta_resolution);
  return cos_theta_table[theta_increment];
}

 inline double Theta::to_sin(int theta_degrees)  {
  int theta_increment = static_cast<int>(theta_degrees / theta_resolution);
  return sin_theta_table[theta_increment];
}

std::string Theta::to_string() const {
  std::ostringstream os;
  os << "theta " << get_theta_degrees();
  return os.str();
}

std::ostream &operator<<(std::ostream &out, const Theta &theta) {
  out << theta.get_theta_degrees();
  return out;
}
