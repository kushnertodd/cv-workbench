//
// Created by kushn on 6/11/2022.
//

#include <csetjmp>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include "jpeglib.h"
#include "image.hpp"

using namespace std;

extern bool debug;

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

void Image::add(char *src, int count) {
  if (!allocated)
    throw new Image_exception("Image::add: cannot add to assigned buffer");
  if (next_pos + count > nbytes)
    throw new Image_exception("Image::add", next_pos + count, nbytes);
  memcpy(buf + next_pos, src, count);
  next_pos += count;
}

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
    errors.add("Image::read_binary: invalid file '" + path + "'");
    return nullptr;
  }
  int rows;
  size_t newLen;
  newLen = fread(&rows, sizeof(int), 1, fp);

  if (ferror(fp) != 0 || newLen != 1) {
    errors.add("Image::read_binary: missing image rows in '" + path + "'");
    return nullptr;
  }
  int cols;
  newLen = fread(&cols, sizeof(int), 1, fp);

  if (ferror(fp) != 0 || newLen != 1) {
    errors.add("Image::read_binary: missing image cols in '" + path + "'");
    return nullptr;
  }
  int components;
  newLen = fread(&components, sizeof(int), 1, fp);

  if (ferror(fp) != 0 || newLen != 1) {
    errors.add("Image::read_binary: missing image components in '" + path + "'");
    return nullptr;
  }
  Image *image = Image::create_image_allocated_buffer(rows, cols, components);

  // Read the data into buffer.
  newLen = fread(image->buf, sizeof(char), image->nbytes, fp);

  if (ferror(fp) != 0 || newLen != sizeof(char) * image->nbytes) {
    errors.add("Image::read_binary: cannot read image data in '" + path + "'");
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
    errors.add("Image::read_jpeg: invalid file '" + path + "'");
    return nullptr;
  }
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  if (setjmp(jerr.setjmp_buffer)) {
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);
    errors.add("Image::read_jpeg: jpeg read error in '" + path + "'");
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

 void Image::write_binary(string path, Errors &errors){
  FILE *fp = fopen(path.c_str(), "w");
  if (fp == nullptr) {
    errors.add("Image::write_binary: invalid file '" + path + "'");
  }
  fwrite(&rows, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_binary: cannot write image rows to '" + path + "'");
  }
  fwrite(&cols, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_binary: cannot write image cols to '" + path + "'");
  }
  fwrite(&components, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_binary: cannot write image components to '" + path + "'");
  }
  // Write the data from the buffer.
  fwrite(buf, sizeof(char), nbytes, fp);
  if (ferror(fp) != 0) {
    errors.add("Image::write_binary: cannot write image data to '" + path + "'");
  }
  fclose(fp);
}

 void Image::write_jpeg(string path, Errors &errors) {
   int quality = 100; // best
     struct jpeg_compress_struct cinfo;
     struct jpeg_error_mgr jerr;
     /* More stuff */
     FILE * outfile;		/* target file */
     JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
    // int row_stride;		/* physical row width in image buffer */

     /* Step 1: allocate and initialize JPEG compression object */
     cinfo.err = jpeg_std_error(&jerr);
     /* Now we can initialize the JPEG compression object. */
     jpeg_create_compress(&cinfo);
     /* Step 2: specify data destination (eg, a file) */
     if ((outfile = fopen(path.c_str(), "wb")) == NULL) {
     errors.add("Image::write_jpeg: invalid file '" + path + "'");
     }
     jpeg_stdio_dest(&cinfo, outfile);
     /* Step 3: set parameters for compression */
     cinfo.image_width = cols;
     cinfo.image_height = rows;
     cinfo.input_components = 1; // hardcode grayscale for now
     cinfo.in_color_space = JCS_GRAYSCALE; 	/* colorspace of input image */
     jpeg_set_defaults(&cinfo);
     jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
     /* Step 4: Start compressor */
     jpeg_start_compress(&cinfo, TRUE);
     /* Step 5: while (scan lines remain to be written) */
     /*           jpeg_write_scanlines(...); */

     while (cinfo.next_scanline < cinfo.image_height) {
       /* jpeg_write_scanlines expects an array of pointers to scanlines.
        * Here the array is only one element long, but you could pass
        * more than one scanline at a time if that's more convenient.
        */
       row_pointer[0] = (JSAMPROW)&buf[cinfo.next_scanline * row_stride];
       (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
     }
     /* Step 6: Finish compression */
     jpeg_finish_compress(&cinfo);
     /* After finish_compress, we can close the output file. */
     fclose(outfile);
     /* Step 7: release JPEG compression object */
     jpeg_destroy_compress(&cinfo);

}






