//
// Created by kushn on 9/12/2022.
//

#ifndef SRC__THETA_H_
#define SRC__THETA_H_

#include <cmath>
#include <iostream>
#include "wb_utils.hpp"

// give theta resolution fraction length, e.g., for 0.1 allows 45.1)
const double theta_resolution = 0.1;
const int max_degrees = 180;
const int max_thetas = static_cast<int>(max_degrees / theta_resolution);

class Theta {
 private:
  static const double cos_theta_table[max_thetas];
  static const double sin_theta_table[max_thetas];
  int theta_increment;
 public:
  Theta();
  explicit Theta(int theta_degrees);

  // prefix increment
  Theta &operator++();

  // postfix increment
  Theta operator++(int);

  static double degrees_to_radians(int degrees) ;
    int get_theta_degrees() const;
  inline int get_theta_increment() const { return theta_increment; }
  double get_theta_radians() const;
  static int radians_to_degrees(double radians);
  void set_theta_degrees(int theta_degrees);
  void set_theta_radians(double theta_radians);
  inline void set_theta_increment(int m_theta_increment) { theta_increment = m_theta_increment; }
  inline double to_cos() const { return cos_theta_table[theta_increment]; }
  inline double to_sin() const { return sin_theta_table[theta_increment]; }
  static double to_cos(int theta_degrees);
  static double to_sin(int theta_degrees);
  std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &os, const Theta &theta);
  friend class Polar_line;
};

#endif //SRC__THETA_H_
