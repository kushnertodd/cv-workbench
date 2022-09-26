//
// Created by kushn on 9/24/2022.
//

#ifndef SRC__WB_CONFIG_MASK_H_
#define SRC__WB_CONFIG_MASK_H_

/**
 * Configurable edge mask
 */
class WB_config_mask {
  virtual double value(int row, int col) = 0;
};

#endif //SRC__WB_CONFIG_MASK_H_
