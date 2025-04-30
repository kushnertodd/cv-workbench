#include "image_header.hpp"
#include <iomanip>
#include <iostream>
#include "wb_utils.hpp"

extern bool debug;

Image_header::Image_header() = default;
/*
 * @brief
 * @param m_nrows
 * @param m_ncols
 * @param m_ncomponents
 * @param m_depth
 */
Image_header::Image_header(const int m_ncols, const int m_nrows, const int m_ncomponents, const Image_depth m_depth) :
    ncomponents(m_ncomponents), depth(m_depth), npixels(m_nrows * row_stride), row_stride(m_ncols * ncomponents) {
    if (debug)
        std::cout << "Image_header::Image_header: " << to_string() << std::endl;
    image_frame.init(m_ncols, m_nrows);
}
/**
 * @brief
 * @param image_header
 */
Image_header::Image_header(const Image_header &image_header) :
    Image_header(image_header.get_ncols(), image_header.get_nrows(), image_header.ncomponents, image_header.depth) {}
/**
 * @brief
 * TODO: fix
 * @param fp
 * @param errors
 */
void Image_header::read(FILE *fp, Errors &errors) {
    int ncols;
    int nrows;
    wb_utils::read_int(fp, ncols, "Image_header::read_header", "", "missing image ncols", errors);
    if (!errors.has_error())
        wb_utils::read_int(fp, nrows, "Image_header::read_header", "", "missing image nrows", errors);
    if (!errors.has_error())
        wb_utils::read_int(fp, ncomponents, "Image_header::read_header", "", "missing image ncomponents", errors);
    if (!errors.has_error()) {
        int depth_int;
        wb_utils::read_int(fp, depth_int, "Image_header::read_header", "", "missing image depth", errors);
        if (!errors.has_error())
            depth = static_cast<Image_depth>(depth_int);
    }
}
/**
 * @brief
 * @param col
 * @param row
 */
void Image_header::check_pixel_valid(int col, int row) const { image_frame.check_pixel_valid(col, row); }
/**
 * @brief
 * @return
 */
int Image_header::get_ncols() const { return image_frame.get_ncols(); }
/**
 * @brief
 * @return
 */
int Image_header::get_nrows() const { return image_frame.get_nrows(); }
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
bool Image_header::is_pixel_valid(int col, int row) const { return image_frame.is_pixel_valid(col, row); }
/**
 * @brief
 * @param point
 * @param col
 * @param row
 */
void Image_header::to_point(Point &point, int col, int row) const { image_frame.to_point(point, col, row); }
/**
 * @brief
 * @param point
 * @param pixel
 */
void Image_header::to_point(Point &point, Pixel &pixel) const { image_frame.to_point(point, pixel); }
/**
 * @brief
 * @param col
 * @return
 */
double Image_header::to_x(int col) const { return image_frame.to_x(col); }
/**
 * @brief
 * @param row
 * @return
 */
double Image_header::to_y(int row) const { return image_frame.to_y(row); }
/**
 * @brief
 * TODO: fix
 * @param fp
 * @param errors
 */
void Image_header::write(FILE *fp, Errors &errors) const {
    int ncols;
    int nrows;
    fwrite(&ncols, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Image_header::write_header", "", "cannot write image nrows");
        return;
    }
    fwrite(&nrows, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Image_header::write_header", "", "cannot write image ncols");
        return;
    }
    fwrite(&ncomponents, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Image_header::write_header", "", "cannot write image ncomponents");
        return;
    }
    fwrite(&depth, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Image_header::write_header", "", "cannot write image depth");
        return;
    }
}
/**
 * @brief
 * @param prefix
 * @return
 */
std::string Image_header::to_string(const std::string &prefix) const {
    std::ostringstream os;
    os << prefix << std::setw(20) << std::left << "ncols " << get_ncols() << std::endl
       << prefix << std::setw(20) << std::left << "nrows " << get_nrows() << std::endl
       << prefix << std::setw(20) << std::left << "ncomponents " << ncomponents << std::endl
       << prefix << std::setw(20) << std::left << "depth " << WB_image_depth::to_string(depth) << std::endl
       << prefix << std::setw(20) << std::left << "row_stride " << row_stride << std::endl
       << prefix << std::setw(20) << std::left << "npixels " << npixels << std::endl;
    return os.str();
}
