//
// Created by kushn on 6/14/2022.
//

#include <iostream>
#include <sstream>
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "image_header.hpp"

extern bool debug;

Image_header::Image_header(int m_rows, int m_cols, int m_components, cv_enums::CV_image_depth m_depth) :
    rows(m_rows),
    cols(m_cols),
    components(m_components),
    depth(m_depth),
    row_stride(cols * components),
    npixels(rows * row_stride) {
  if (debug)
    cout << "Image_header::Image_header: " << to_string() << endl;
}

Image_header::Image_header(Image_header *image_header) :
    Image_header(image_header->rows,
                 image_header->cols,
                 image_header->components,
                 image_header->depth) {
}

Image_header::Image_header(Image_header &image_header) :
    Image_header(image_header.rows,
                 image_header.cols,
                 image_header.components,
                 image_header.depth) {
}
Image_header *Image_header::read_header(FILE *fp, string path, Errors &errors) {
  int rows;
  if (!File_utils::read_int(fp, rows)) {
    errors.add("Image_header::read_header: missing image rows in '" + path + "'");
    return nullptr;
  }

  int cols;
  if (!File_utils::read_int(fp, cols)) {
    errors.add("Image_header::read_header: missing image cols in '" + path + "'");
    return nullptr;
  }

  int components;
  if (!File_utils::read_int(fp, components)) {
    errors.add("Image_header::read_header: missing image components in '" + path + "'");
    return nullptr;
  }

  int depth;
  if (!File_utils::read_int(fp, depth)) {
    errors.add("Image_header::read_header: missing image depth in '" + path + "'");
    return nullptr;
  }
  return new Image_header(rows, cols, components, ( cv_enums::CV_image_depth) depth);

}

void Image_header::write_header(FILE *fp, string path, Errors &errors) {
  if (debug)
    cout << "Image_header::write_header  path '" << path << "' " << to_string() << endl;
  fwrite(&rows, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image_header::write_header: cannot write image rows to '" + path + "'");
  }
  fwrite(&cols, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image_header::write_header: cannot write image cols to '" + path + "'");
  }
  fwrite(&components, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image_header::write_header: cannot write image components to '" + path + "'");
  }
  fwrite(&depth, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image_header::write_header: cannot write image depth to '" + path + "'");
  }
}

string Image_header::to_string() {
  ostringstream os;
  os << "rows " << rows
     << " cols " << cols
     << " components " << components
     << " depth " << depth << " " << Workbench_utils::image_depth_enum_to_string(depth)
     << " row_stride " << row_stride
     << " npixels " << npixels;
  return os.str();
}
