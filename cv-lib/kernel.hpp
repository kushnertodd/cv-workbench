//
// Created by kushn on 6/16/2022.
//

#ifndef CV_WORKBENCH_SRC_KERNEL_HPP_
#define CV_WORKBENCH_SRC_KERNEL_HPP_

#include "image.hpp"
#include "wb_defs.hpp"
#include "wb_morphology_types.hpp"

/** 'list of n-tuple' data type

    The i component, of the n-tuple number j, of an n-tuple list 'ntl'
    is accessed with:

      ntl->values[ i + j * ntl->dim ]

    The dimension of the n-tuple (n) is:

      ntl->dim

    The number of n-tuples in the list is:

      ntl->size

    The maximum number of n-tuples that can be stored in the
    list with the allocated memory at a given time is given by:

      ntl->max_size

      for gaussian_kernel only
 */
typedef struct ntuple_list_s {
    unsigned int size;
    unsigned int max_size;
    unsigned int dim;
    double *values;
} *ntuple_list;

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

    Kernel(int m_nrows, int m_ncols, Image_depth m_depth);

    Image *convolve_numeric(Image *src, Errors &errors) const;

    Image *convolve_morphological(Image *src,
                                  WB_morphology_types::Convolution_type convolution_type,
                                  Errors &errors) const;

    Image *convolve(Image *src,
                    Image_depth out_depth,
                    WB_morphology_types::Convolution_type convolution_type,
                    Errors &errors) const;

    static Kernel *create_32S(int ncols, int nrows, const pixel_32S *buf_32S);

    static Kernel *create_32F(int ncols, int nrows, const pixel_32F *buf_32F);

    static Kernel *create_gaussian_y(int nrows, double sigma_y);

    static Kernel *create_gaussian_x(int ncols, double sigma_x);

    static Kernel *create_structuring_element(WB_morphology_types::Structuring_element_type structuring_element_type,
                                              int nrows,
                                              int ncols,
                                              int thickness = 0);

    static void gaussian_kernel(ntuple_list kernel, double sigma, double mean);

    static void enlarge_ntuple_list(ntuple_list n_tuple);
};

#endif //CV_WORKBENCH_SRC_KERNEL_HPP_
