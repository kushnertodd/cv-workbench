//
// Created by kushn on 9/12/2022.
//

#ifndef SRC__THETA_H_
#define SRC__THETA_H_

#include <cmath>
#include "theta_static.hpp"

// give theta resolution fraction length, e.g., for 0.1 allows 45.1)
const double theta_resolution = 0.1;
const int max_degrees = 180;
const int max_thetas = max_degrees / theta_resolution;

class Theta {
 private:
  static const double cos_theta_table[max_thetas];
  static const double sin_theta_table[max_thetas];
  int theta_increment;
 public:
  Theta();
  static inline int begin() { return 0; }
  static inline int end(){ return max_thetas - 1;}
  inline double to_rad() const {    return to_degrees() * M_PI / max_degrees;  }
  inline  double to_cos() const { return cos_theta_table[theta_increment]; }
  inline double to_degrees() const { return theta_increment * theta_resolution; }
  inline  double to_sin() const { return sin_theta_table[theta_increment]; }

};

#endif //SRC__THETA_H_
