//
// Created by kushn on 6/14/2022.
//

#include "image_header.hpp"
#include <iomanip>
#include <iostream>
#include "wb_utils.hpp"

extern bool debug;

Image_index::Image_index() = default;
Image_index::Image_index(int m_col, int m_row) : col(m_col), row(m_row) {}
void Image_index::init(int m_col, int m_row) {
    col = m_col;
    row = m_row;
}

Image_point::Image_point() = default;
Image_point::Image_point(double m_x, double m_y) : x(m_x), y(m_y) {}
void Image_point::init(double m_x, double m_y) {
    x = m_x;
    y = m_y;
}

Image_header::Image_header() = default;
/*
 *
 * @param m_rows
 * @param m_ncols
 * @param m_ncomponents
 * @param m_depth
 */
Image_header::Image_header(const int m_nrows, const int m_ncols, const int m_ncomponents, const Image_depth m_depth) :
    ncomponents(m_ncomponents), depth(m_depth), ncols(m_ncols), nrows(m_nrows), npixels(nrows * row_stride),
    row_stride(ncols * ncomponents) {
    if (debug)
        std::cout << "Image_header::Image_header: " << to_string() << std::endl;
}
Image_header::Image_header(const Image_header &image_header) :
    Image_header(image_header.nrows, image_header.ncols, image_header.ncomponents, image_header.depth) {}

void Image_header::read(FILE *fp, Errors &errors) {
    wb_utils::read_int(fp, nrows, "Image_header::read_header", "", "missing image nrows", errors);
    if (!errors.has_error())
        wb_utils::read_int(fp, ncols, "Image_header::read_header", "", "missing image ncols", errors);
    if (!errors.has_error())
        wb_utils::read_int(fp, ncomponents, "Image_header::read_header", "", "missing image ncomponents", errors);
    if (!errors.has_error()) {
        int depth_int;
        wb_utils::read_int(fp, depth_int, "Image_header::read_header", "", "missing image depth", errors);
        if (!errors.has_error())
            depth = static_cast<Image_depth>(depth_int);
    }
}
double Image_header::to_x(int col) { return col - ncols / 2.0; }
double Image_header::to_y(int row) { return nrows / 2.0 - row; }
int Image_header::to_col(double x) { return wb_utils::double_to_int_round(x + ncols / 2.0); }
int Image_header::to_row(double y) { return wb_utils::double_to_int_round(nrows / 2.0 - y); }
void Image_header::to_index(Image_index &image_index, Image_point &image_point) {
    image_index.init(to_col(image_point.x), to_row(image_point.y));
}
void Image_header::to_point(Image_point &image_point, Image_index &image_index) {
    image_point.init(to_x(image_index.col), to_y(image_index.row));
}
void Image_header::write(FILE *fp, Errors &errors) const {
    fwrite(&nrows, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Image_header::write_header", "", "cannot write image nrows");
        return;
    }
    fwrite(&ncols, sizeof(int), 1, fp);
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
        errors.add("Image_headerZZ::write_header", "", "cannot write image depth");
        return;
    }
}
std::string Image_header::to_string(const std::string &prefix) const {
    std::ostringstream os;
    os << prefix << std::setw(20) << std::left << "nrows " << nrows << std::endl
       << prefix << std::setw(20) << std::left << "ncols " << ncols << std::endl
       << prefix << std::setw(20) << std::left << "ncomponents " << ncomponents << std::endl
       << prefix << std::setw(20) << std::left << "depth " << WB_image_depth::to_string(depth) << std::endl
       << prefix << std::setw(20) << std::left << "row_stride " << row_stride << std::endl
       << prefix << std::setw(20) << std::left << "npixels " << npixels << std::endl;
    return os.str();
}
