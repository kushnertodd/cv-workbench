//
// Created by kushn on 9/24/2022.
//

#ifndef SRC__WB_CONFIG_MASK_H_
#define SRC__WB_CONFIG_MASK_H_

/**
 * Configurable edge mask
 */
class WB_config_mask {
 public:
  virtual double value(double x, double y) const = 0;
};

#endif //SRC__WB_CONFIG_MASK_H_
