//
// Created by kushn on 10/3/2022.
//

#ifndef SRC__LINEAR_FEATURES_HPP_
#define SRC__LINEAR_FEATURES_HPP_

#include <cfloat>
#include "image.hpp"
#include "wb_utils.hpp"

class Linear_features {
 private:
  enum LINE_TRACK {
    BELOW_BOTTOM,
    INSIDE,
    ABOVE_TOP
  };
  enum QUADRANT {
    QUADRANT_1,  // 0..45 degrees
    QUADRANT_2,  // 45..90 degrees
    QUADRANT_3,  // 90..135 degrees
    QUADRANT_4,  // 135..180 degrees
  };
  const double unassigned = -FLT_MIN;
  Image *features;
  int feature_length{};
  int theta_degrees;
  QUADRANT quadrant;
  double cos_theta{};
  double sin_theta{};
  int cols{};
  int rows{};
 public:
  ~Linear_features();
  Linear_features() = default;
  Linear_features(Image *image,
                                          int m_feature_length,
                                          int m_theta_degrees);
  inline int get_cols() const { return cols; }
  inline Image* get_features() const { return features; }
  inline int get_rows() const { return rows; }
  inline float get(int row, int col) { return features->get_32F(row, col); }
  inline void set(int row, int col, double value) {  features->set_32F(row, col, wb_utils::double_to_float(value)); }
};

#endif //SRC__LINEAR_FEATURES_HPP_
