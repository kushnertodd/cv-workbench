//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__BOUNDS_HPP_
#define SRC__BOUNDS_HPP_

#include "point.hpp"

class Bounds {
 public:
  float min_value;
  float max_value;
  static float map_input_to_output_bounds(float value, Bounds *input_bounds, Bounds *output_bounds);
  float map_to_output_bounds(float value, Bounds *output_bounds);
  float map_from_input_bounds(float value, Bounds *input_bounds);
  int bin(float value, int nbins);
};

#endif //SRC__BOUNDS_HPP_
