//
// Created by kushn on 6/14/2022.
//

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "wb_utils.hpp"
#include "image_header.hpp"

Image_header::Image_header() = default;

/**
 * Constructor
 * @param m_rows
 * @param m_cols
 * @param m_components
 * @param m_depth
 */
Image_header::Image_header(int m_rows,
                           int m_cols,
                           int m_components,
                           WB_image_depth::Image_depth m_depth) :
    rows(m_rows),
    cols(m_cols),
    components(m_components),
    depth(m_depth),
    min_row(0),
    min_col(0),
    max_row(rows - 1),
    max_col(cols - 1),
    row_stride(cols * components),
    npixels(rows * row_stride),
    nelements(rows * cols) {
}

/**
 * Constructor
 * @param m_rows
 * @param m_cols
 * @param m_components
 * @param m_depth
 */
Image_header::Image_header(int m_rows, int m_cols, int m_components,
                           WB_image_depth::Image_depth m_depth,
                           int m_min_row,
                           int m_min_col,
                           int m_max_row,
                           int m_max_col) :
    rows(m_rows),
    cols(m_cols),
    components(m_components),
    depth(m_depth),
    min_row(m_min_row),
    min_col(m_min_col),
    max_row(m_max_row),
    max_col(m_max_col),
    row_stride(cols * components),
    npixels(rows * row_stride),
    nelements(rows * cols) {
  assert(min_row >= 0);
  assert(min_row <= max_row);
  assert(max_row < rows);
  assert(min_col >= 0);
  assert(min_col <= max_col);
  assert(max_col < cols);
}

/**
 * Constructor
 * @param m_rows
 * @param m_cols
 * @param m_components
 * @param m_depth
 */
Image_header::Image_header(Image_header &image_header) :
    Image_header(image_header.rows,
                 image_header.cols,
                 image_header.components,
                 image_header.depth) {
}

/**
 * Read binary file image header
 * @param fp
 * @param errors
 */
void Image_header::read(FILE *fp, Errors &errors) {
  wb_utils::read_int(fp, rows, "Image_header::read_header", "", "missing image rows", errors);
  if (!errors.has_error())
    wb_utils::read_int(fp, cols, "Image_header::read_header", "", "missing image cols", errors);
  if (!errors.has_error())
    wb_utils::read_int(fp,
                       components,
                       "Image_header::read_header",
                       "",
                       "missing image components",
                       errors);
  if (!errors.has_error()) {
    int depth_int;
    wb_utils::read_int(fp,
                       depth_int,
                       "Image_header::read_header",
                       "",
                       "missing image depth",
                       errors);
    if (!errors.has_error())
      depth = static_cast<WB_image_depth::Image_depth>(depth_int);
  }
}

/**
 * Setter min_row
 * @param m_min_row
 */
void Image_header::set_min_row(int m_min_row) {
  min_row = m_min_row;
}

/**
 * Setter min_col
 * @param m_min_col
 */
void Image_header::set_min_col(int m_min_col) {
  min_col = m_min_col;
}

/**
 * Setter max_row
 * @param m_max_row
 */
void Image_header::set_max_row(int m_max_row) {
  max_row = m_max_row;
}

/**
 * Setter max_col
 * @param m_max_col
 */
void Image_header::set_max_col(int m_max_col) {
  max_col = m_max_col;
}

/**
 * Write binary file image header data
 * @param fp
 * @param errors
 */
void Image_header::write(FILE *fp, Errors &errors) const {
  wb_utils::write_int(fp,
                      rows,
                      "Image_header::write",
                      "",
                      "cannot write image rows",
                      errors);
if (!errors.has_error())
  wb_utils::write_int(fp,
                      cols,
                      "Image_header::write",
                      "",
                      "cannot write image cols",
                      errors);

  if (!errors.has_error())
    wb_utils::write_int(fp,
                        components,
                        "Image_header::write",
                        "",
                        "cannot write image components",
                        errors);
  if (!errors.has_error())
    wb_utils::write_int(fp,
                        static_cast<int>(depth),
                        "Image_header::write",
                        "",
                        "cannot write image depth",
                        errors);
}

/**
 * Convert to information string
 * @param prefix
 * @return
 */
std::string Image_header::to_string(const std::string &prefix) const {
  std::ostringstream os;
  os << prefix << std::setw(20) << std::left << "rows " << rows << std::endl
     << prefix << std::setw(20) << std::left << "cols " << cols << std::endl
     << prefix << std::setw(20) << std::left << "components " << components << std::endl
     << prefix << std::setw(20) << std::left << "depth " << WB_image_depth::to_string(depth) << std::endl
     << prefix << std::setw(20) << std::left << "min_row " << min_row << std::endl
     << prefix << std::setw(20) << std::left << "min_col " << min_col << std::endl
     << prefix << std::setw(20) << std::left << "max_row " << max_row << std::endl
     << prefix << std::setw(20) << std::left << "max_col " << max_col << std::endl
     << prefix << std::setw(20) << std::left << "row_stride " << row_stride << std::endl
     << prefix << std::setw(20) << std::left << "npixels " << npixels << std::endl
  << prefix << std::setw(20) << std::left << "nelements " << nelements << std::endl;
  return os.str();
}
