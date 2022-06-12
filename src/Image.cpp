//
// Created by kushn on 6/11/2022.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include "image.hpp"

Image_exception::Image_exception(string m_errmsg) :
    errmsg(m_errmsg) {
}

Image_exception::Image_exception(string message,
                                 int size,
                                 int max_size) {
  ostringstream os;
  os << message << ": cannot allocate " << size <<
     " bytes, max size " <<
     max_size;
  errmsg = os.str();
}

const char *Image_exception::what() const noexcept {
  return errmsg.c_str();
}

 Image::~Image() {
  if (allocated && buf != nullptr) {
    delete[] buf;
  }
}

Image::Image(int m_rows, int m_cols, int m_components) :
    rows(m_rows),
    cols(m_cols),
    components(m_components),
    row_stride(cols * components),
    nbytes(rows * row_stride),
    next_pos(0) {}

Image *Image::create_image_allocated_buffer(int m_rows, int m_cols, int m_components) {
  Image *image = new Image(m_rows, m_cols, m_components);
  image->buf = new char[image->nbytes];
  image->allocated = true;
  return image;
}

Image *Image::create_image_assigned_buffer(int m_rows, int m_cols, int m_components, char *m_buf) {
  Image *image = new Image(m_rows, m_cols, m_components);
  image->buf = m_buf;
  image->allocated = false;
  return image;
}

Image *Image::read_binary(string path, Errors &errors) {
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == nullptr) {
    errors.add("Filesystem_data_source_descriptor::read_image: invalid file '" + path + "'");
    return nullptr;
  }
  int rows;
  size_t newLen;
  newLen = fread(&rows, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Filesystem_data_source_descriptor::read_image: missing image rows in '" + path + "'");
    return nullptr;
  }
  int cols;
  newLen = fread(&cols, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Filesystem_data_source_descriptor::read_image: missing image cols in '" + path + "'");
    return nullptr;
  }
  int components;
  newLen = fread(&components, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Filesystem_data_source_descriptor::read_image: missing image components in '" + path + "'");
    return nullptr;
  }
  Image *image = Image::create_image_allocated_buffer(rows, cols, components);

  // Read the data into buffer.
  newLen = fread(image->buf, sizeof(char), image->nbytes, fp);
  if (ferror(fp) != 0) {
    errors.add("Filesystem_data_source_descriptor::read_image: cannot read image data in '" + path + "'");
    return nullptr;
  }
  fclose(fp);
  return image;
}
void Image::add(char *src, int count) {
  if (!allocated)
    throw new Image_exception("Image::add: cannot add to assigned buffer");
  if (next_pos + count > nbytes)
    throw new Image_exception("Image::add", next_pos + count, nbytes);
  memcpy(buf + next_pos, src, count);
  next_pos += count;
}






