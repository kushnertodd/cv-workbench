//
// Created by kushn on 8/23/2022.
//

#include "pearsons_correlation.hpp"

Pearsons_correlation::Pearsons_correlation(Image *m_image, Kernel *m_pattern) :
    image(m_image),
    pattern(m_pattern),
    image_rows(image->get_rows()),
    image_cols(image->get_cols()),
    pattern_rows(pattern->get_rows()),
    pattern_cols(pattern->get_cols()),
    opm(new One_pass_mean(image, pattern_rows, pattern_cols)) {
}

Image *Pearsons_correlation::correlate() {
  Image *output = new Image(*image);
  for (int row = 0; row <= image_rows - pattern_rows; row++) {
    for (int col = 0; col <= image_cols - pattern_cols; col++) {
      output->set(row + opm->row_delta, col + opm->col_delta, opm->get_mean());
      opm->col_right();
    }
    opm->row_down();
  }
  return output;
}
