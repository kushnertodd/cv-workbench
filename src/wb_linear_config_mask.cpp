//
// Created by kushn on 9/24/2022.
//

#include "wb_linear_config_mask.hpp"

WB_linear_config_mask::WB_linear_config_mask(int m_height,
                                             int m_width_left,
                                             double m_value_left,
                                             int m_width_center,
                                             double m_value_center,
                                             int m_width_right,
                                             double m_value_right) :
    height(m_height),
    width_left(m_width_left),
    value_left(m_value_left),
    width_center(m_width_center),
    value_center(m_value_center),
    width_right(m_width_right),
    value_right(m_value_right) {}

double WB_linear_config_mask::value(int row, int col) {
  if (col >= 0 && col < width_left
      && row >= 0 && row < height) {
    return value_left;
  } else if (col >= width_left && col < width_left + width_center
      && row >= 0 && row < height) {
    return value_center;
  } else if (col >= width_left + width_center && col < width_left + width_center + width_right
      && row >= 0 && row < height) {
    return value_right;
  } else
    return 0.0;
}
