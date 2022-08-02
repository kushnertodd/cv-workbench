//
// Created by kushn on 8/2/2022.
//

#include "morphology.hpp"


Kernel *Morphology::create_structuring_element_rectangle(int rows, int cols) {
  return Kernel::create_structuring_element(
      WB_morphology_types::Structuring_element_type::RECTANGLE,
      rows, cols);
}

Kernel *Morphology::create_structuring_element_cross(int rows, int cols, int thickness) {
  return Kernel::create_structuring_element(
      WB_morphology_types::Structuring_element_type::CROSS,
      rows, cols, thickness);
}

Kernel *Morphology::create_structuring_element_ellipse(int rows, int cols) {
  return Kernel::create_structuring_element(
      WB_morphology_types::Structuring_element_type::ELLIPSE,
      rows, cols);
}