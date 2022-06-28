//
// Created by kushn on 6/27/2022.
//

#include <cfloat>
#include <algorithm>
#include "bounds.hpp"

using namespace std;

Bounds::Bounds() :
    min_value(FLT_MAX),
    max_value(FLT_MIN) {
}

Bounds::Bounds(float m_min_value, float m_max_value) :
    min_value(m_min_value),
    max_value(m_max_value) {
}

void Bounds::add(float value) {
  min_value = min(min_value, value);
  max_value = max(max_value, value);
}

float Bounds::map_input_to_output_bounds(float value, Bounds *input_bounds, Bounds *output_bounds) {
  if (value < input_bounds->min_value)
    return output_bounds->min_value;
  else if (value > input_bounds->max_value)
    return output_bounds->max_value;
  else
    return output_bounds->min_value
        + (value - input_bounds->min_value)
            * (output_bounds->max_value - output_bounds->min_value)
            / (input_bounds->max_value - input_bounds->min_value);
}

float Bounds::map_to_output_bounds(float value, Bounds *output_bounds) {
  Bounds *input_bounds = this;
  return map_input_to_output_bounds(value, input_bounds, output_bounds);
}

float Bounds::map_from_input_bounds(float value, Bounds *input_bounds) {
  Bounds *output_bounds = this;
  return map_input_to_output_bounds(value, input_bounds, output_bounds);
}

int Bounds::bin(float value, int nbins) {
  if (value < min_value)
    return 0;
  else if (value > max_value)
    return nbins - 1;
  else
    return (nbins - 1) * (value - min_value) / (max_value - min_value);
}
