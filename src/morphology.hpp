//
// Created by kushn on 8/2/2022.
//

#ifndef SRC__MORPHOLOGY_HPP_
#define SRC__MORPHOLOGY_HPP_

#include "kernel.hpp"

class Morphology {
  static Kernel *create_structuring_element_rectangle(int rows, int cols);
  static Kernel *create_structuring_element_cross(int rows, int cols, int thickness = 0);
  static Kernel *create_structuring_element_ellipse(int rows, int cols);

static Image* dilate(Image* image);
  static Image* erode(Image* image);

};

#endif //SRC__MORPHOLOGY_HPP_
