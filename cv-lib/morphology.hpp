//
// Created by kushn on 8/2/2022.
//

#ifndef SRC__MORPHOLOGY_HPP_
#define SRC__MORPHOLOGY_HPP_

#include "kernel.hpp"

class Morphology {
 public:
  static Kernel *create_structuring_element_rectangle(int nrows, int ncols);
  static Kernel *create_structuring_element_cross(int nrows, int ncols, int thickness = 0);
  static Kernel *create_structuring_element_ellipse(int nrows, int ncols);

  static Image *black_hat(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                          int nrows, int ncols, int thickness, Errors &errors);
  static Image *close(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                      int nrows, int ncols, int thickness, Errors &errors);
  static Image *dilate(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                       int nrows, int ncols, int thickness, Errors &errors);
  static Image *erode(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                      int nrows, int ncols, int thickness, Errors &errors);
  static Image *gradient(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                         int nrows, int ncols, int thickness, Errors &errors);
  static Image *open(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                     int nrows, int ncols, int thickness, Errors &errors);
  static Image *top_hat(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                        int nrows, int ncols, int thickness, Errors &errors);

};

#endif //SRC__MORPHOLOGY_HPP_
