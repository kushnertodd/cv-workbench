//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__BOUNDS_HPP_
#define SRC__BOUNDS_HPP_

#include <string>

using namespace std;

class Bounds {
 public:
  float min_value;
  float max_value;
  Bounds();
  Bounds(float m_min_value, float m_max_value);
  void update(float value);
  static float map_input_to_output_bounds(float value, Bounds *input_bounds, Bounds *output_bounds);
  float map_to_output_bounds(float value, Bounds *output_bounds);
  float map_from_input_bounds(float value, Bounds *input_bounds);
  int bin(float value, int nbins);
  string to_string();
};

#endif //SRC__BOUNDS_HPP_
