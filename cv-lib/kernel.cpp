#include "kernel.hpp"
#include <cmath>
#include <iostream>
#include "wb_morphology_types.hpp"
#include "wb_utils.hpp"

extern bool debug;
/**
 * @brief
 */
Kernel::~Kernel() = default;
/**
 * @brief
 */
Kernel::Kernel() = default;
/**
 * @brief
 * @param ncols
 * @param nrows
 * @param depth
 */
Kernel::Kernel(int ncols, int nrows, Image_depth depth) : Image(ncols, nrows, 1, depth) {}
/**
 * @brief
 * numeric convolution, depth defaults to CV_32S, or CV_32F if either the kernel or image is CV_32F
 * morphology convolution, depth defaults to the input image
 * @param src
 * @param out_depth
 * @param convolution_type
 * @param errors
 * @return
 */
Image *Kernel::convolve(Image *src, Image_depth out_depth, WB_morphology_types::Convolution_type convolution_type,
                        Errors &errors) const {
    Image_depth depth = get_depth();
    if (depth == Image_depth::CV_8U && convolution_type == WB_morphology_types::Convolution_type::NUMERIC) {
        errors.add("Kernel::convolve_numeric", "", "cannot perform numeric convolution with CV_8U output image");
        return nullptr;
    } else {
        int src_ncols = src->get_ncols();
        int src_nrows = src->get_nrows();
        int src_components = src->get_ncomponents();
        int ncols = get_ncols();
        int nrows = get_nrows();
        // output image is Image_depth::CV_32F if either the image and kernel are Image_depth::CV_32F, else it is
        // Image_depth::CV_32S
        auto *out = new Image(src_ncols, src_nrows, src_components, out_depth);
        int ncols_half = (ncols + 1) / 2;
        int nrows_half = (nrows + 1) / 2;
        int col_lower = 0;
        int col_upper = src_ncols - ncols;
        int row_lower = 0;
        int row_upper = src_nrows - nrows;
        if (debug)
            std::cout << " ncols_half " << ncols_half << " nrows_half " << nrows_half << " col_lower " << col_lower
                      << " col_upper " << col_upper << " row_lower " << row_lower << " row_upper " << row_upper
                      << " row_lower " << row_lower << " row_upper " << row_upper << std::endl;
        int kernel_col_lower = 0;
        int kernel_col_upper = ncols - 1;
        int kernel_row_lower = 0;
        int kernel_row_upper = nrows - 1;
        if (debug)
            std::cout << " kernel_col_lower " << kernel_col_lower << " kernel_col_upper " << kernel_col_upper
                      << " kernel_row_lower " << kernel_row_lower << " kernel_row_upper " << kernel_row_upper
                      << std::endl;
        for (int col = col_lower; col <= col_upper; col++) {
            int col_center = col + ncols_half - 1;
            if (debug)
                std::cout << "col " << col << " col_center " << col_center << std::endl;
            for (int row = row_lower; row <= row_upper; row++) {
                int row_center = row + nrows_half - 1;
                if (debug)
                    std::cout << "row " << row << " row_center " << row_center << std::endl;
                double sum;
                switch (convolution_type) {
                    case WB_morphology_types::Convolution_type::NUMERIC:
                        sum = 0.0;
                        break;
                    case WB_morphology_types::Convolution_type::ERODE:
                        sum = INT32_MAX;
                        break;
                    case WB_morphology_types::Convolution_type::DILATE:
                        sum = 0.0;
                        break;
                    case WB_morphology_types::Convolution_type::UNDEFINED:
                        break;
                    default:
                        sum = 0.0;
                        break;
                }
                for (int j = kernel_col_lower; j <= kernel_col_upper; j++) {
                    for (int i = kernel_row_lower; i <= kernel_row_upper; i++) {
                        double kernel_val = get(i, j);
                        double image_val = src->get(col + j, row + i);
                        switch (convolution_type) {
                            case WB_morphology_types::Convolution_type::NUMERIC:
                                sum += kernel_val * image_val;
                                break;
                            case WB_morphology_types::Convolution_type::ERODE:
                                if (kernel_val > 0)
                                    sum = std::min(sum, image_val);
                                break;
                            case WB_morphology_types::Convolution_type::DILATE:
                                if (kernel_val > 0)
                                    sum = std::max(sum, image_val);
                                break;
                            default:
                                break;
                        }
                        if (debug)
                            std::cout << "sum += kernel[" << i << "," << j << "] " << kernel_val << " * image["
                                      << col + j << "," << row + i << "] " << image_val << " = " << sum << std::endl;
                    }
                    if (debug)
                        std::cout << std::endl;
                }
                if (debug)
                    std::cout << "buf[" << col_center << "," << row_center << "] = " << sum << std::endl;
                out->set(col_center, row_center, sum);
            }
        }
        return out;
    }
}
/**
 * @brief
 * @param src
 * @param convolution_type
 * @param errors
 * @return
 */
Image *Kernel::convolve_morphological(Image *src, WB_morphology_types::Convolution_type convolution_type,
                                      Errors &errors) const {
    return Kernel::convolve(src, src->get_depth(), convolution_type, errors);
}
/**
 * base convolution, if convolution numeric, error if CV_8U input depth
 * @brief
 * @param src
 * @param errors
 * @return
 */
Image *Kernel::convolve_numeric(Image *src, Errors &errors) const {
    // output image is Image_depth::CV_32F if either the image and kernel are Image_depth::CV_32F, else it is
    // Image_depth::CV_32S
    Image_depth out_depth =
            (src->get_depth() == Image_depth::CV_32F || get_depth() == Image_depth::CV_32F ? Image_depth::CV_32F
                                                                                           : Image_depth::CV_32S);
    return Kernel::convolve(src, out_depth, WB_morphology_types::Convolution_type::NUMERIC, errors);
}
/**
 * @brief
 * @param ncols
 * @param nrows
 * @param buf_32S
 * @return
 */
Kernel *Kernel::create_32S(int ncols, int nrows, const pixel_32S *buf_32S) {
    auto *kernel = new Kernel(ncols, nrows, Image_depth::CV_32S);
    const pixel_32S *buf_ptr = buf_32S;
    for (int col = 0; col < ncols; col++)
        for (int row = 0; row < nrows; row++)
            kernel->set_32S(col, row, *buf_ptr++);
    return kernel;
}
/**
 * @brief
 * @param ncols
 * @param nrows
 * @param buf_32F
 * @return
 */
Kernel *Kernel::create_32F(int ncols, int nrows, const pixel_32F *buf_32F) {
    auto *kernel = new Kernel(ncols, nrows, Image_depth::CV_32F);
    for (int i = 0; i < kernel->get_npixels(); i++) {
        kernel->buf_32F[i] = buf_32F[i];
    }
    return kernel;
}
/**
 * @brief
 * @param ncols
 * @param sigma_x
 * @return
 */
Kernel *Kernel::create_gaussian_x(int ncols, double sigma_x) {
    auto *gaussian_x = new Kernel(1, ncols, Image_depth::CV_32F);
    double fact1 = 1.0 / (sigma_x * sqrt(2 * M_PI));
    double denom1 = 2 * sigma_x * sigma_x;
    double sum = 0.0;
    for (int col = 0; col < ncols; col++) {
        double x = col - ncols / 2.0;
        double value = fact1 * exp(-((x * x) / denom1));
        gaussian_x->set(0, col, value);
        sum += value;
    }
    for (int col = 0; col < ncols; col++) {
        double value = gaussian_x->get(0, col);
        gaussian_x->set(0, col, value / sum);
    }
    return gaussian_x;
}
/**
 * @brief
 * @param nrows
 * @param sigma_y
 * @return
 */
Kernel *Kernel::create_gaussian_y(int nrows, double sigma_y) {
    auto *gaussian_y = new Kernel(nrows, 1, Image_depth::CV_32F);
    double fact1 = 1.0 / (sigma_y * sqrt(2 * M_PI));
    double denom1 = 2 * sigma_y * sigma_y;
    double sum = 0.0;
    for (int row = 0; row < nrows; row++) {
        double y = nrows / 2.0 - row;
        double value = fact1 * exp(-((y * y) / denom1));
        gaussian_y->set(row, 0, value);
        sum += value;
    }
    for (int row = 0; row < nrows; row++) {
        double value = gaussian_y->get(row, 0);
        gaussian_y->set(row, 0, value / sum);
    }
    return gaussian_y;
}
/**
 * @brief
 * @param structuring_element_type
 * @param ncols
 * @param nrows
 * @param thickness
 * @return
 */
Kernel *Kernel::create_structuring_element(WB_morphology_types::Structuring_element_type structuring_element_type,
                                           int ncols, int nrows, int thickness) {
    auto *kernel = new Kernel(ncols, nrows, Image_depth::CV_8U);
    for (int col = 0; col < ncols; col++) {
        for (int row = 0; row < nrows; row++) {
            switch (structuring_element_type) {
                case WB_morphology_types::Structuring_element_type::RECTANGLE:
                    kernel->set_8U(col, row, 1);
                    break;
                case WB_morphology_types::Structuring_element_type::CROSS: {
                    // TODO: check ncols, nrows
                    // double Image_header::to_x(int col) const { return col - col_offset; }
                    // double Image_header::to_y(int row) const { return row_offset - row; }
                    double x = col - ncols / 2.0;
                    double y = nrows / 2.0 - row;
                    if (std::abs(x) <= thickness / 2.0 || std::abs(y) <= thickness / 2.0)
                        kernel->set_8U(col, row, 1);
                    break;
                }
                case WB_morphology_types::Structuring_element_type::ELLIPSE:
                    // TODO: check ncols, nrows
                    // if (in_ellipse(col, row))
                    //    kernel->set_8U(col, row, 1);
                    break;
                default:
                    break;
            }
        }
    }
    return kernel;
}
/**
 * Enlarge the allocated memory of an n-tuple list.
 * for gaussian_kernel
 * @brief
 * @param n_tuple
 */
void Kernel::enlarge_ntuple_list(ntuple_list n_tuple) {
    /* check parameters */
    if (n_tuple == nullptr || n_tuple->values == nullptr || n_tuple->max_size == 0)
        wb_utils::error_exit("enlarge_ntuple_list: invalid n-tuple.");

    /* duplicate number of tuples */
    n_tuple->max_size *= 2;

    /* realloc memory */
    n_tuple->values = (double *) realloc((void *) n_tuple->values, n_tuple->dim * n_tuple->max_size * sizeof(double));
    if (n_tuple->values == nullptr)
        wb_utils::error_exit("not enough memory.");
}
/**
 * Compute a Gaussian kernel of length 'kernel->dim',
 * standard deviation 'sigma', and centered at value 'mean'.
 * For example, if mean=0.5, the Gaussian will be centered
 * in the middle pixel between values 'kernel->values[0]'
 * and 'kernel->values[1]'.
 * from this, not using, just for interest.
 * https://www.ipol.im/pub/art/2012/gjmr-lsd/article.pdf
 * @brief
 * @param kernel
 * @param sigma
 * @param mean
 */
void Kernel::gaussian_kernel(ntuple_list kernel, double sigma, double mean) {
    double sum = 0.0;
    double val;
    unsigned int i;

    /* check parameters */
    if (kernel == nullptr || kernel->values == nullptr)
        wb_utils::error_exit("gaussian_kernel: invalid n-tuple 'kernel'.");
    if (sigma <= 0.0)
        wb_utils::error_exit("gaussian_kernel: 'sigma' must be positive.");

    /* compute Gaussian kernel */
    if (kernel->max_size < 1)
        enlarge_ntuple_list(kernel);
    kernel->size = 1;
    for (i = 0; i < kernel->dim; i++) {
        val = ((double) i - mean) / sigma;
        kernel->values[i] = exp(-0.5 * val * val);
        sum += kernel->values[i];
    }

    /* normalization */
    if (sum >= 0.0)
        for (i = 0; i < kernel->dim; i++)
            kernel->values[i] /= sum;
}
