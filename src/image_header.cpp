//
// Created by kushn on 6/14/2022.
//

#include "image_header.hpp"

Image_header::Image_header(int m_rows, int m_cols, int m_components, Cv_image_depth_enum m_depth) :
    rows(m_rows),
    cols(m_cols),
    components(m_components),
    depth(m_depth),
    row_stride(cols * components),
    npixels(rows * row_stride) {}

Image_header *Image_header::read_header(FILE *fp, string path, Errors &errors) {
  int rows;
  size_t newLen;
  newLen = fread(&rows, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    errors.add("Image_header::read_header: missing image rows in '" + path + "'");
    return nullptr;
  }

  int cols;
  newLen = fread(&cols, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    errors.add("Image_header::read_header: missing image cols in '" + path + "'");
    return nullptr;
  }

  int components;
  newLen = fread(&components, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    errors.add("Image_header::read_header: missing image components in '" + path + "'");
    return nullptr;
  }

  int depth;
  newLen = fread(&depth, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    errors.add("Image_header::read_header: missing image depth in '" + path + "'");
    return nullptr;
  }
  return new Image_header(rows, cols, components, (Cv_image_depth_enum) depth);

}

void Image_header::write_header(FILE *fp, string path, Errors &errors) {
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

}