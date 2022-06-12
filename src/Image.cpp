//
// Created by kushn on 6/11/2022.
//

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

void Image::add(char *src, int count) {
  if (!allocated)
    throw new Image_exception("Image::add: cannot add to assigned buffer");
  if (next_pos + count > nbytes)
    throw new Image_exception("Image::add", next_pos + count, nbytes);
  memcpy(buf + next_pos, src, count);
  next_pos += count;
}






