//
// Created by kushn on 6/27/2022.
//

#include <cassert>
#include <cfloat>
#include <climits>
#include <algorithm>
#include <string>
#include <sstream>
#include "bounds.hpp"

Bounds::Bounds() :
    Bounds(FLT_MAX, -FLT_MAX) {
}

Bounds::Bounds(float m_min_value, float m_max_value) :
    min_value(m_min_value),
    max_value(m_max_value),
    changed(false){
}

void Bounds::update(float value) {
  min_value = std::min(min_value, value);
  max_value = std::max(max_value, value);
  changed=true;
}

float Bounds::get_min_value() const{
  assert(changed);
  return min_value;
}

float Bounds::get_max_value() const {
  assert(changed);
return max_value;
}

float Bounds::map_input_to_output_bounds(float value, Bounds &input_bounds, Bounds &output_bounds) {
  if (value < input_bounds.get_min_value())
    return output_bounds.get_min_value();
  else if (value > input_bounds.get_max_value())
    return output_bounds.get_max_value();
  else
    return output_bounds.get_min_value()
        + (value - input_bounds.get_min_value())
            * (output_bounds.get_max_value() - output_bounds.get_min_value())
            / (input_bounds.get_max_value() - input_bounds.get_min_value());
}

std::string Bounds::to_string() const {
  std::ostringstream os;
  os << "min_value " << min_value << " max_value " << max_value;
  return os.str();
}