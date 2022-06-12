//
// Created by kushn on 6/11/2022.
//

#include <csetjmp>
#include <cstdio>
#include <cstring>
#include <sstream>
#include "jpeglib.h"
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
  if (ferror(fp) != 0 || newLen != sizeof(int)) {
    errors.add("Filesystem_data_source_descriptor::read_image: missing image rows in '" + path + "'");
    return nullptr;
  }
  int cols;
  newLen = fread(&cols, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != sizeof(int)) {
    errors.add("Filesystem_data_source_descriptor::read_image: missing image cols in '" + path + "'");
    return nullptr;
  }
  int components;
  newLen = fread(&components, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != sizeof(int)) {
    errors.add("Filesystem_data_source_descriptor::read_image: missing image components in '" + path + "'");
    return nullptr;
  }
  Image *image = Image::create_image_allocated_buffer(rows, cols, components);

  // Read the data into buffer.
  newLen = fread(image->buf, sizeof(char), image->nbytes, fp);
  if (ferror(fp) != 0 || newLen != sizeof(char) * image->nbytes) {
    errors.add("Filesystem_data_source_descriptor::read_image: cannot read image data in '" + path + "'");
    return nullptr;
  }
  fclose(fp);
  return image;
}

struct my_error_mgr {
  struct jpeg_error_mgr pub;    /* "public" fields */
  jmp_buf setjmp_buffer;    /* for return to caller */
};
typedef struct my_error_mgr *my_error_ptr;

void my_error_exit(j_common_ptr cinfo) {
  my_error_ptr myerr = (my_error_ptr) cinfo->err;
  (*cinfo->err->output_message)(cinfo);
  longjmp(myerr->setjmp_buffer, 1);
}

#define READ_BINARY    "rb"
Image *Image::read_jpeg(string path, Errors &errors) {
  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;
  JSAMPARRAY buffer;
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == nullptr) {
    errors.add("Filesystem_data_source_descriptor::read_jpeg: invalid file '" + path + "'");
    return nullptr;
  }
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  if (setjmp(jerr.setjmp_buffer)) {
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);
    errors.add("Filesystem_data_source_descriptor::read_jpeg: jpeg read error in '" + path + "'");
    return nullptr;
  }
  /* Step 1: allocate and initialize JPEG decompression object */
  jpeg_create_decompress(&cinfo);
  /* Step 2: specify data source (eg, a file) */
  jpeg_stdio_src(&cinfo, fp);
  /* Step 3: read file parameters with jpeg_read_header() */
  (void) jpeg_read_header(&cinfo, TRUE);
  /* Step 4: set parameters for decompression */
  /* Step 5: Start decompressor */
  (void) jpeg_start_decompress(&cinfo);
  /* JSAMPLEs per row in output buffer */
  Image *image = Image::create_image_allocated_buffer(cinfo.output_height, cinfo.output_width, cinfo.num_components);
  /* Make a one-row-high sample array that will go away when done with image */
  buffer = (*cinfo.mem->alloc_sarray)
      ((j_common_ptr) & cinfo, JPOOL_IMAGE, image->row_stride, 1);
  /* Step 6: while (scan lines remain to be read) */
  while (cinfo.output_scanline < cinfo.output_height) {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
    image->add((char *)buffer[0], image->row_stride);
  }
  /* Step 7: Finish decompression */
  (void) jpeg_finish_decompress(&cinfo);
  /* Step 8: Release JPEG decompression object */
  jpeg_destroy_decompress(&cinfo);
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






