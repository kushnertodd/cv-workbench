#include "morphology.hpp"
#include <memory>

/**
 * @brief
 * @param ncols
 * @param nrows
 * @return
 */
Kernel *Morphology::create_structuring_element_rectangle(int ncols, int nrows) {
    return Kernel::create_structuring_element(WB_morphology_types::Structuring_element_type::RECTANGLE, ncols, nrows);
}
/**
 * @brief
 * @param ncols
 * @param nrows
 * @param thickness
 * @return
 */
Kernel *Morphology::create_structuring_element_cross(int ncols, int nrows, int thickness) {
    return Kernel::create_structuring_element(WB_morphology_types::Structuring_element_type::CROSS, nrows, ncols,
                                              thickness);
}
/**
 * @brief
 * @param ncols
 * @param nrows
 * @return
 */
Kernel *Morphology::create_structuring_element_ellipse(int ncols, int nrows) {
    return Kernel::create_structuring_element(WB_morphology_types::Structuring_element_type::ELLIPSE, ncols, nrows);
}
// Subtract the original image from the closed image

/**
 * @brief
 * @param image
 * @param structuring_element_type
 * @param ncols
 * @param nrows
 * @param thickness
 * @param errors
 * @return
 */
Image *Morphology::black_hat(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                             int ncols, int nrows, int thickness, Errors &errors) {
    std::unique_ptr<Image> closed_image(
            Morphology::close(image, structuring_element_type, ncols, nrows, thickness, errors));
    if (errors.has_error())
        return nullptr;
    return Image::subtract(closed_image.get(), image, errors);
}
// Dilation followed by eroding

/**
 * @brief
 * @param image
 * @param structuring_element_type
 * @param ncols
 * @param nrows
 * @param thickness
 * @param errors
 * @return
 */
Image *Morphology::close(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                         int ncols, int nrows, int thickness, Errors &errors) {

    std::unique_ptr<Image> dilated_image(
            Morphology::dilate(image, structuring_element_type, ncols, nrows, thickness, errors));
    return Morphology::erode(dilated_image.get(), structuring_element_type, ncols, nrows, thickness, errors);
}
// Output the maximum value under the structuring element

/**
 * @brief
 * @param image
 * @param structuring_element_type
 * @param ncols
 * @param nrows
 * @param thickness
 * @param errors
 * @return
 */
Image *Morphology::dilate(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                          int ncols, int nrows, int thickness, Errors &errors) {
    std::unique_ptr<Kernel> structuring_element(
            Kernel::create_structuring_element(structuring_element_type, ncols, nrows, thickness));
    return structuring_element->convolve_morphological(image, WB_morphology_types::Convolution_type::DILATE, errors);
}
// Output the minimum value under the structuring element

/**
 * @brief
 * @param image
 * @param structuring_element_type
 * @param ncols
 * @param nrows
 * @param thickness
 * @param errors
 * @return
 */
Image *Morphology::erode(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                         int ncols, int nrows, int thickness, Errors &errors) {
    std::unique_ptr<Kernel> structuring_element(
            Kernel::create_structuring_element(structuring_element_type, ncols, nrows, thickness));
    return structuring_element->convolve_morphological(image, WB_morphology_types::Convolution_type::ERODE, errors);
}
// Subtract the eroded image from the dilated image

/**
 * @brief
 * @param image
 * @param structuring_element_type
 * @param ncols
 * @param nrows
 * @param thickness
 * @param errors
 * @return
 */
Image *Morphology::gradient(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                            int ncols, int nrows, int thickness, Errors &errors) {
    std::unique_ptr<Image> eroded_image(
            Morphology::erode(image, structuring_element_type, ncols, nrows, thickness, errors));
    if (errors.has_error())
        return nullptr;
    std::unique_ptr<Image> dilated_image(
            Morphology::dilate(image, structuring_element_type, ncols, nrows, thickness, errors));
    if (errors.has_error())
        return nullptr;
    return Image::subtract(dilated_image.get(), eroded_image.get(), errors);
}
// Erosion followed by dilation

/**
 * @brief
 * @param image
 * @param structuring_element_type
 * @param ncols
 * @param nrows
 * @param thickness
 * @param errors
 * @return
 */
Image *Morphology::open(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type, int ncols,
                        int nrows, int thickness, Errors &errors) {
    std::unique_ptr<Image> eroded_image(
            Morphology::erode(image, structuring_element_type, ncols, nrows, thickness, errors));
    return Morphology::dilate(eroded_image.get(), structuring_element_type, ncols, nrows, thickness, errors);
}
// Subtract the opened image from the original image

/**
 * @brief
 * @param image
 * @param structuring_element_type
 * @param ncols
 * @param nrows
 * @param thickness
 * @param errors
 * @return
 */
Image *Morphology::top_hat(Image *image, WB_morphology_types::Structuring_element_type structuring_element_type,
                           int ncols, int nrows, int thickness, Errors &errors) {
    std::unique_ptr<Image> opened_image(
            Morphology::open(image, structuring_element_type, ncols, nrows, thickness, errors));
    if (errors.has_error())
        return nullptr;
    return Image::subtract(image, opened_image.get(), errors);
}
