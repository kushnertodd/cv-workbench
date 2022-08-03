//
// Created by kushn on 8/2/2022.
//

#include <memory>
#include "morphology.hpp"

Kernel *Morphology::create_structuring_element_rectangle(int rows, int cols) {
  return Kernel::create_structuring_element(WB_morphology_types::Structuring_element_type::RECTANGLE, rows, cols);
}

Kernel *Morphology::create_structuring_element_cross(int rows, int cols, int thickness) {
  return Kernel::create_structuring_element(WB_morphology_types::Structuring_element_type::CROSS,
                                            rows,
                                            cols,
                                            thickness);
}

Kernel *Morphology::create_structuring_element_ellipse(int rows, int cols) {
  return Kernel::create_structuring_element(WB_morphology_types::Structuring_element_type::ELLIPSE, rows, cols);
}

// Subtract the original image from the closed image
Image *Morphology::black_hat(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                             int rows, int cols, int thickness, Errors &errors) {
  std::unique_ptr<Image>
      closed_image(Morphology::close(image, structuring_element_type, rows, cols, thickness, errors));
  if (errors.has_error())
    return nullptr;
  return Image::subtract(closed_image.get(), image, errors);

}

// Dilation followed by eroding
Image *Morphology::close(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                         int rows, int cols, int thickness, Errors &errors) {

  std::unique_ptr<Image>
      dilated_image(Morphology::dilate(image, structuring_element_type, rows, cols, thickness, errors));
  return Morphology::erode(dilated_image.get(), structuring_element_type, rows, cols, thickness, errors);
}

// Output the maximum value under the structuring element
Image *Morphology::dilate(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                          int rows, int cols, int thickness, Errors &errors) {
  std::unique_ptr<Kernel>
      structuring_element(Kernel::create_structuring_element(structuring_element_type, rows, cols, thickness));
  return structuring_element->convolve_morphological(image, WB_morphology_types::Convolution_type::DILATE, errors);
}

// Output the minimum value under the structuring element
Image *Morphology::erode(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                         int rows, int cols, int thickness, Errors &errors) {
  std::unique_ptr<Kernel>
      structuring_element(Kernel::create_structuring_element(structuring_element_type, rows, cols, thickness));
  return structuring_element->convolve_morphological(image, WB_morphology_types::Convolution_type::ERODE, errors);
}

// Subtract the eroded image from the dilated image
Image *Morphology::gradient(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                            int rows, int cols, int thickness, Errors &errors) {
  std::unique_ptr<Image>
      eroded_image(Morphology::erode(image, structuring_element_type, rows, cols, thickness, errors));
  if (errors.has_error())
    return nullptr;
  std::unique_ptr<Image>
      dilated_image(Morphology::dilate(image, structuring_element_type, rows, cols, thickness, errors));
  if (errors.has_error())
    return nullptr;
  return Image::subtract(dilated_image.get(), eroded_image.get(), errors);
}

// Erosion followed by dilation
Image *Morphology::open(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                        int rows, int cols, int thickness, Errors &errors) {
  std::unique_ptr<Image>
      eroded_image(Morphology::erode(image, structuring_element_type, rows, cols, thickness, errors));
  return Morphology::dilate(eroded_image.get(), structuring_element_type, rows, cols, thickness, errors);
}

// Subtract the opened image from the original image
Image *Morphology::top_hat(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                           int rows, int cols, int thickness, Errors &errors) {
  std::unique_ptr<Image> opened_image(Morphology::open(image, structuring_element_type, rows, cols, thickness, errors));
  if (errors.has_error())
    return nullptr;
  return Image::subtract(image, opened_image.get(), errors);
}
