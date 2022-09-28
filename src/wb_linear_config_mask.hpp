//
// Created by kushn on 9/24/2022.
//

#ifndef SRC__WB_LINEAR_CONFIG_MASK_H_
#define SRC__WB_LINEAR_CONFIG_MASK_H_

#include "wb_config_mask.hpp"
#include "wb_linear_config_mask.hpp"

/**
 * Configurable edge mask
 *
 * Configurable three zone mask.
 * left zone:
 * - ulc (0,0)
 * - lrc (height-1,width_left-1)
 * - value value_left
 * center zone:
 * - ulc (0,width_left)
 * - lrc (height-1,width_left+width_center-1)
 * - value value_center
 * right zone:
 * - ulc (0,width_left+width_center)
 * - lrc (height-1,width_left+width_center+width_right-1)
 * - value value_right
 *
 * @image html WB_config_mask1.jpg
 *
 * @image html WB_config_mask1.jpg
 */
class WB_linear_config_mask : public WB_config_mask {
 private:
  int height;
  int width_left;
  double value_left;
  int width_center;
  double value_center;
  int width_right;
  double value_right;
  int rows;
  int cols;
 public:
  WB_linear_config_mask(int m_height,
                        int m_width_left,
                        double m_value_left,
                        int m_width_center,
                        double m_value_center,
                        int m_width_right,
                        double m_value_right);
  double value(double x, double y) const;
};

#endif //SRC__WB_LINEAR_CONFIG_MASK_H_
