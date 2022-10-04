//
// Created by kushn on 10/3/2022.
//

#include "line_segment.hpp"
#include "linear_features.hpp"
#include "theta.hpp"
#include "wb_utils.hpp"
#include "wb_window.hpp"

Linear_features::~Linear_features() {
  delete features;
}

Linear_features::Linear_features(Image *image, int m_feature_length, int m_theta_degrees) {
  theta_degrees = m_theta_degrees;
  Theta theta(theta_degrees);
  cos_theta = Theta::to_cos(theta_degrees);
  sin_theta = Theta::to_sin(theta_degrees);
  feature_length = m_feature_length;
  cols = image->get_cols() / feature_length + 1;
  if (theta_degrees <= 45) {
    quadrant = QUADRANT_1;
    double tan_theta = sin_theta / cos_theta;
    //double y_offset = cols * tan_theta;
    //int row_offset = WB_window::y_to_row(y_offset, get_rows());
    int row_offset = wb_utils::double_to_int_round(cols * tan_theta);
    rows = image->get_rows() + row_offset;
    int feature_cols = image->get_cols() / feature_length;
    features = new Image(rows,
                         feature_cols,
                         image->get_components(),
                         WB_image_depth::Image_depth::CV_32F,
                         unassigned);
    Line_segment line(0, 0, -row_offset, image->get_cols()-1);
    //LINE_TRACK line_track = BELOW_BOTTOM;
    for (int row = 0; row < rows; row++) {
      int col_out = 0;
      bool accumulating;
      double feature_sum;
      for (auto iter = line.begin();
           iter != line.end();
           iter++) {
        Point point = *iter;
        int point_row = point.get_row() + row;
        int point_col = point.get_col();
        if (point_col % feature_length == 0) {
          accumulating = true;
          feature_sum = 0;
        }
        if (point_row < 0 || point_row >= rows) {
          accumulating = false;
        } else if (accumulating) {
          double value = image->get(point_row, point_col);
          feature_sum += value;
        }
        if (point_col % feature_length == feature_length - 1) {
          if (accumulating)
            set(point_row, col_out, feature_sum);
          col_out++;
        }
      }
    }
  } else if (theta_degrees <= 90) {
    double cot_theta = cos_theta / sin_theta;
    quadrant = QUADRANT_2;
  } else if (theta_degrees <= 135) {
    double cot_theta = cos_theta / sin_theta;
    quadrant = QUADRANT_3;
  } else {
    double tan_theta = sin_theta / cos_theta;
    quadrant = QUADRANT_4;
  }
}
