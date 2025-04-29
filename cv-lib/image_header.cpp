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
    ncomponents(m_ncomponents), depth(m_depth), ncols(m_ncols), nrows(m_nrows), npixels(nrows * row_stride),
    row_stride(ncols * ncomponents) {
    if (debug)
        std::cout << "Image_header::Image_header: " << to_string() << std::endl;
    image_frame.init(m_ncols, m_nrows);
}
/**
 * @brief
 * @param image_header
 */
Image_header::Image_header(const Image_header &image_header) :
    Image_header(image_header.ncols, image_header.nrows, image_header.ncomponents, image_header.depth) {}
void Image_header::read(FILE *fp, Errors &errors) {
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
 * @param x
 * @return
 */
int Image_header::to_col(double x) const { return image_frame.to_col(x); }
/**
 * @brief
 * @param pixel
 * @param x
 * @param y
 */
void Image_header::to_pixel(Pixel &pixel, double x, double y);
{
    image_frame.to_pixel(pixel, x, y);
}
/**
 * @brief
 * @param y
 * @return
 */
int Image_header::to_row(double y) const { return image_frame.to_row(y); }
/**
 * @brief
 * @param pixel
 * @param point
 */
void Image_header::to_pixel(Pixel &pixel, Point &point) const { image_frame.to_pixel(pixel, point); }
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
 * @param fp
 * @param errors
 */
void Image_header::write(FILE *fp, Errors &errors) const {
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
    os << prefix << std::setw(20) << std::left << "ncols " << ncols << std::endl
       << prefix << std::setw(20) << std::left << "nrows " << nrows << std::endl
       << prefix << std::setw(20) << std::left << "ncomponents " << ncomponents << std::endl
       << prefix << std::setw(20) << std::left << "depth " << WB_image_depth::to_string(depth) << std::endl
       << prefix << std::setw(20) << std::left << "row_stride " << row_stride << std::endl
       << prefix << std::setw(20) << std::left << "npixels " << npixels << std::endl;
    return os.str();
}
