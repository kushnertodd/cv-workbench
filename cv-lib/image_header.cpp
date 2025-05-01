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
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 * This fills in line segment pixels with Bresenham's line algorithm
 * @param image_line_segment
 * @param col1
 * @param row1
 * @param col2
 * @param row2
 */
void Image_header::plot_line_low(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2) {
    int d_col = col2 - col1;
    int d_row = row2 - row1;
    int row_i = 1;
    if (d_row < 0) {
        row_i = -1;
        d_row = -d_row;
    }
    int D = (2 * d_row) - d_col;
    int row = row1;

    for (int x = col1; x <= col2; x++) {
        image_line_segment.add(x, row);
        if (D > 0) {
            row = row + row_i;
            D = D + (2 * (d_row - d_col));
        } else {
            D = D + 2 * d_row;
        }
    }
}
/**
 * @brief
 * @param image_line_segment
 * @param col1
 * @param row1
 * @param col2
 * @param row2
 */
void Image_header::plot_line_high(Image_line_segment &image_line_segment, int col1, int row1, int col2, int row2) {
    int d_col = col2 - col1;
    int d_row = row2 - row1;
    int col_i = 1;
    if (d_col < 0) {
        col_i = -1;
        d_col = -d_col;
    }
    int D = (2 * d_col) - d_row;
    int col = col1;
    for (int row = row1; row <= row2; row++) {
        image_line_segment.add(col, row);
        if (D > 0) {
            col = col + col_i;
            D = D + (2 * (d_col - d_row));
        } else {
            D = D + 2 * d_col;
        }
    }
}
/**
 * @brief
 * @param image_line_segment
 */
void Image_header::plot_line(Image_line_segment &image_line_segment) {
    int col1 = image_line_segment.pixel1.col;
    int row1 = image_line_segment.pixel1.row;
    int col2 = image_line_segment.pixel2.col;
    int row2 = image_line_segment.pixel2.row;
    if (abs(row2 - row1) < abs(col2 - col1)) {
        if (col1 > col2) {
            plot_line_low(image_line_segment, col2, row2, col1, row1);
        } else {
            plot_line_low(image_line_segment, col1, row1, col2, row2);
        }
    } else {
        if (row1 > row2) {
            plot_line_high(image_line_segment, col2, row2, col1, row1);
        } else {
            plot_line_high(image_line_segment, col1, row1, col2, row2);
        }
    }
}
/**
 * @brief
 * TODO: fix
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
/**
 * @brief
 * @param col
 * @return
 */
double Image_header::to_x(int col) const { return col - col_offset; }
/**
 * @brief
 * @param col
 * @param ncols
 * @return
 */
double Image_header::to_x(int col, int ncols) { return col - ncols / 2.0; }
/**
 * @brief
 * @param row
 * @return
 */
double Image_header::to_y(int row) const { return row_offset - row; }
/**
 * @brief
 * @param row
 * @param nrows
 * @return
 */
double Image_header::to_y(int row, int nrows) { return nrows / 2.0 - row; }
/**
 * @brief
 * TODO: fix
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
