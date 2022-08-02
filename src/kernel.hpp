//
// Created by kushn on 6/16/2022.
//

#ifndef CV_WORKBENCH_SRC_KERNEL_HPP_
#define CV_WORKBENCH_SRC_KERNEL_HPP_

#include "image.hpp"
#include "wb_defs.hpp"
#include "wb_morphology_types.hpp"

/**
 * Kernel class
 * Supports convolution of rectangular image filters
 * Some convolution kernels are separable, e.g., Sobel (http://www.k-zone.nl/Kroon_DerivativePaper.pdf),
 * Gaussian (http://www-edlab.cs.umass.edu/~smaji/cmpsci370/slides/hh/lec02_hh_advanced_edges.pdf),
 * but few enough that specially implementing them is not necessarily useful.
 */
class Kernel : public Image {
 public:

  ~Kernel() override;
  Kernel();
  Kernel(int m_rows, int m_cols, WB_image_depth::Image_depth m_depth);

  Image *convolve_numeric(Image *src, Errors &errors)const;
  Image *convolve_morphological(Image *src, WB_morphology_types::Convolution_type convolution_type, Errors &errors) const;
  Image *convolve(Image *src, WB_image_depth::Image_depth out_depth, WB_morphology_types::Convolution_type convolution_type, Errors &errors) const;
  static Kernel *create_32S(int rows, int cols, const pixel_32S *buf_32S);
  static Kernel *create_32F(int rows, int cols, const pixel_32F *buf_32F);
  static Kernel *create_structuring_element(WB_morphology_types::Structuring_element_type structuring_element_type,
                                            int rows,
                                            int cols,
                                            int thickness = 0);

};

#endif //CV_WORKBENCH_SRC_KERNEL_HPP_
