#include "image_header.hpp"
#include <iomanip>
#include <iostream>
#include "wb_utils.hpp"

extern bool debug;

Image_header::Image_header() = default;
/*
 * @brief
 * @param m_ncols
 * @param m_nrows
 * @param m_ncomponents
 * @param m_depth
 */
Image_header::Image_header(const int m_ncols, const int m_nrows, const int m_ncomponents, const Image_depth m_depth) :
    ncomponents(m_ncomponents), depth(m_depth), ncols(m_ncols), nrows(m_nrows), row_stride(ncols * ncomponents),
    npixels(nrows * row_stride) {
    if (debug)
        std::cout << "Image_header::Image_header: " << to_string() << std::endl;
    col_offset = ncols / 2.0;
    row_offset = nrows / 2.0;
}

/**
 * @brief
 * @param image_header
 */
Image_header::Image_header(const Image_header &image_header) :
    Image_header(image_header.ncols, image_header.nrows, image_header.ncomponents, image_header.depth) {}
/**
 * @brief
 * @return
 */
Image_depth Image_header::get_depth() const { return depth; }
/**
 * @brief
 * @return
 */
int Image_header::get_ncols() const { return ncols; }
/**
 * @brief
 * @return
 */
int Image_header::get_ncomponents() const { return ncomponents; }
/**
 * @brief
 * @return
 */
int Image_header::get_npixels() const { return npixels; }
/**
 * @brief
 * @return
 */
int Image_header::get_nrows() const { return nrows; }
/**
 * @brief
 * @return
 */
int Image_header::get_row_stride() const { return row_stride; }
/**
 * @brief
 * @param fp
 * @param errors
 */
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
 * @param x
 * @return
 */
double Image_header::to_col(double x) const { return x + col_offset - 0.5; }
/**
 * @brief
 * @param x
 * @param ncols
 * @return
 */
double Image_header::to_col(double x, int ncols) { return x + ncols / 2.0 - 0.5; }
/**
 * @brief
 * @param pixel
 * @param x
 * @param y
 */
void Image_header::to_pixel(Pixel &pixel, double x, double y) const { pixel.init(to_col(x), to_row(y)); }
/**
 * @brief
 * @param pixel
 * @param point
 */
void Image_header::to_pixel(Pixel &pixel, Point &point) const { to_pixel(pixel, point.x, point.y); }
/**
 * @brief
 * @param point
 * @param col
 * @param row
 */
void Image_header::to_point(Point &point, int col, int row) const { point.init(to_x(col), to_y(row)); }
/**
 * @brief
 * @param point
 * @param pixel
 */
void Image_header::to_point(Point &point, Pixel &pixel) const { to_point(point, pixel.col, pixel.row); }
/**
 * @brief
 * @param y
 * @return
 */
double Image_header::to_row(double y) const { return row_offset - y - 0.5; }
/**
 * @brief
 * @param y
 * @param nrows
 * @return
 */
double Image_header::to_row(double y, int nrows) { return nrows / 2.0 - y - 0.5; }
/**
 * @brief
 * @param prefix
 * @return
 */
std::string Image_header::to_string(const std::string &prefix) const {
    std::ostringstream os{};
    os << prefix << std::setw(20) << std::left << "ncols " << get_ncols() << std::endl
       << prefix << std::setw(20) << std::left << "nrows " << get_nrows() << std::endl
       << prefix << std::setw(20) << std::left << "ncomponents " << ncomponents << std::endl
       << prefix << std::setw(20) << std::left << "depth " << WB_image_depth::to_string(depth) << std::endl
       << prefix << std::setw(20) << std::left << "row_stride " << row_stride << std::endl
       << prefix << std::setw(20) << std::left << "npixels " << npixels << std::endl;
    return os.str();
}
/**
 * @brief
 * @param col
 * @return
 */
double Image_header::to_x(int col) const {
    double x = col - col_offset + 0.5;
    return x;
}
/**
 * @brief
 * @param col
 * @param ncols
 * @return
 */
double Image_header::to_x(int col, int ncols) {
    double x = col - ncols / 2.0 + 0.5;
    return x;
}
/**
 * @brief
 * @param row
 * @return
 */
double Image_header::to_y(int row) const {
    double y = row_offset - row - 0.5;
    return y;
}
/**
 * @brief
 * @param row
 * @param nrows
 * @return
 */
double Image_header::to_y(int row, int nrows) {
    double y = nrows / 2.0 - row - 0.5;
    return y;
}
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
