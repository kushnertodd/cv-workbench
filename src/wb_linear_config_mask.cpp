//
// Created by kushn on 9/24/2022.
//

#include "wb_linear_config_mask.hpp"

WB_linear_config_mask::WB_linear_config_mask(int m_width_left,
                                             double m_value_left,
                                             int m_width_center,
                                             double m_value_center,
                                             int m_width_right,
                                             double m_value_right) :
    width_left(m_width_left),
    value_left(m_value_left),
    width_center(m_width_center),
    value_center(m_value_center),
    width_right(m_width_right),
    value_right(m_value_right) {}

double WB_linear_config_mask::value(double x, double y) {
  if (x >= 0 && x <= window_left - 1 && y >= 0 && y < h) {
    return value_left;
  } else if (x >= window_left && x <= window_center - 1 && y >= 0 && y < h) {
    return value_center;
  } else if (x >= window_center && x <= window_right - 1 && y >= 0 && y < h) {
    return value_right;
  } else
    return 0.0;
}
