//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__BOUNDS_HPP_
#define SRC__BOUNDS_HPP_

#include <string>

class Bounds {
 public:
  float min_value;
  float max_value;
  bool changed;
  Bounds();
  Bounds(float m_min_value, float m_max_value);
  float get_min_value() const;
  float get_max_value() const;
  static float map_input_to_output_bounds(float value, Bounds &input_bounds, Bounds &output_bounds);
  std::string to_string() const;
  void update(float value);
};

#endif //SRC__BOUNDS_HPP_
