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
#include "wb_utils.hpp"

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
  if (image_header != nullptr) {
    delete image_header;
  }
  if (buf_8U = nullptr) {
    delete[] buf_8U;
  }
  if (buf_32S = nullptr) {
    delete[] buf_32S;
  }
  if (buf_32F = nullptr) {
    delete[] buf_32F;
  }
}

Image::Image(Image_header *m_image_header) :
image_header(m_image_header),
    next_pixel(0) {
  if (debug)
    cout << "Image::Image: " << toString() << endl;
  init();
}
Image::Image(int m_rows, int m_cols, int m_components, Cv_image_depth_enum m_depth) :
next_pixel(0){
  image_header = new Image_header(m_rows, m_cols, m_components, m_depth);
  if (debug)
    cout << "Image::Image: " << toString() << endl;
  init();
}

void Image::init() {
  switch (image_header->depth) {
    case CV_8U:
      buf_8U = new pixel_8U[image_header->npixels];
      for (int i = 0; i < image_header->npixels; i++)
        buf_8U[i] = 0;
      break;

    case CV_32S:
      buf_32S = new pixel_32S[image_header->npixels];
      for (int i = 0; i < image_header->npixels; i++)
        buf_32S[i] = 0;
      break;

    case CV_32F:
      buf_32F = new pixel_32F[image_header->npixels];
      for (int i = 0; i < image_header->npixels; i++)
        buf_32F[i] = 0.0;
      break;

    default:
      break;
  }
}

int Image::get_rows() { return image_header->rows; }
int Image::get_cols() { return image_header->cols; }
int Image::get_components() { return image_header->components; }
int Image::get_row_stride() { return image_header->row_stride; }
int Image::get_npixels() { return image_header->npixels; }
Cv_image_depth_enum Image::get_depth() { return image_header->depth; }

int Image::row_col_to_index(int row, int col) {
  return row * image_header->row_stride + col;
}
pixel_32F Image::get(int row, int col) {
  switch (image_header->depth) {
    case CV_8U:
      return buf_8U[row_col_to_index(row, col)];;
      break;

    case CV_32S:
      return buf_32S[row_col_to_index(row, col)];
      break;

    case CV_32F:
      return buf_32F[row_col_to_index(row, col)];
      break;

    default:
      return 0.0;
      break;
  }
}

void Image::set_8U(int row, int col, pixel_8U value) {
  buf_32F[row_col_to_index(row, col)] = value;
}
pixel_8U Image::get_8U(int row, int col) {
  return buf_32F[row_col_to_index(row, col)];
}
void Image::set_32S(int row, int col, pixel_32S value) {
  buf_32F[row_col_to_index(row, col)] = value;
}
pixel_32S Image::get_32s(int row, int col) {
  return buf_32F[row_col_to_index(row, col)];
}
void Image::set_32F(int row, int col, pixel_32F value) {
  buf_32F[row_col_to_index(row, col)] = value;
}
pixel_32S Image::get_32F(int row, int col) {
  return buf_32F[row_col_to_index(row, col)];
}

void Image::add_8U(pixel_8U *src, int count, Errors &errors) {
  if (next_pixel + count > image_header->npixels)
    errors.add("Image::add_8U: adding "
                   + int_to_string(count) + " pixels at position " +
        int_to_string(next_pixel)
                   + " too large for buffer length "
                   + int_to_string(image_header->npixels));
  for (int i = 0; i < count; i++) {
    switch (image_header->depth) {
      case CV_8U:
        buf_8U[next_pixel++] = src[i];
        break;

      case CV_32S:
        buf_32S[next_pixel++] = src[i];
        break;

      case CV_32F:
        buf_32F[next_pixel++] = src[i];
        break;

      default:
        break;
    }
  }
}

void Image::add_32S(pixel_32S *src, int count, Errors &errors) {
  if (debug)
    cout << "Image::add_32S src " << src << " count " << count << " " << toString() << endl;
  if (next_pixel + count > image_header->npixels)
    errors.add("Image::add_32S: adding "
                   + int_to_string(count) + " pixels at position " +
        int_to_string(next_pixel)
                   + " too large for buffer length "
                   + int_to_string(image_header->npixels));
  for (int i = 0; i < count; i++) {
    switch (image_header->depth) {
      case CV_8U:
        errors.add("Image::add_32S: cannot add to 8U buffer");
        break;

      case CV_32S:
        buf_32S[next_pixel++] = src[i];
        break;

      case CV_32F:
        buf_32F[next_pixel++] = src[i];
        break;

      default:
        break;
    }
  }
}

void Image::add_32F(pixel_32F *src, int count, Errors &errors) {
  if (next_pixel + count > image_header->npixels)
    errors.add("Image::add_32F: adding "
                   + int_to_string(count) + " pixels at position " +
        int_to_string(next_pixel)
                   + " too large for buffer length "
                   + int_to_string(image_header->npixels));
  for (int i = 0; i < count; i++) {
    switch (image_header->depth) {
      case CV_8U:
        errors.add("Image::add_32F: cannot add to 8U buffer");
        break;

      case CV_32S:
        buf_32S[next_pixel++] = src[i];
        break;

      case CV_32F:
        buf_32F[next_pixel++] = src[i];
        break;

      default:
        break;
    }
  }
}

Image *Image::read_binary(string path, Errors &errors) {
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == nullptr) {
    errors.add("Image::read_binary: invalid file '" + path + "'");
    return nullptr;
  }

  Image_header *image_header = Image_header::read_header(fp, path, errors);
  Image *image = new Image(image_header);

  // Read the data into buffer.
  int newLen;

  switch (image_header->depth) {
    case CV_8U:
      newLen = fread(image->buf_8U, sizeof(pixel_8U), image_header->npixels, fp);
      if (ferror(fp) != 0 || newLen != sizeof(pixel_8U) * image_header->npixels) {
        errors.add("Image::read_binary: cannot read 8U image data in '" + path + "'");
        return nullptr;
      }
      break;

    case CV_32S:
      newLen = fread(image->buf_32S, sizeof(pixel_32S), image_header->npixels, fp);
      if (ferror(fp) != 0 || newLen != sizeof(pixel_32S) * image_header->npixels) {
        errors.add("Image::read_binary: cannot read 32S image data in '" + path + "'");
        return nullptr;
      }
      break;

    case CV_32F:
      newLen = fread(image->buf_32F, sizeof(pixel_32F), image_header->npixels, fp);
      if (ferror(fp) != 0 || newLen != sizeof(pixel_32F) * image_header->npixels) {
        errors.add("Image::read_binary: cannot read 32F image data in '" + path + "'");
        return nullptr;
      }
      break;

    default:
      break;
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
  Image *image = new Image(cinfo.output_height, cinfo.output_width, cinfo.num_components, CV_8U);
  /* Make a one-row-high sample array that will go away when done with image */
  buffer = (*cinfo.mem->alloc_sarray)
      ((j_common_ptr) &cinfo, JPOOL_IMAGE, image->get_row_stride(), 1);
  /* Step 6: while (scan lines remain to be read) */
  while (cinfo.output_scanline < cinfo.output_height) {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
    image->add_8U((pixel_8U *) buffer[0], image->get_row_stride(), errors);
  }
  /* Step 7: Finish decompression */
  (void) jpeg_finish_decompress(&cinfo);
  /* Step 8: Release JPEG decompression object */
  jpeg_destroy_decompress(&cinfo);
  fclose(fp);
  return image;
}

void Image::write_binary(string path, Errors &errors) {
  if (debug)
    cout << "Image::write_binary path '" << path << "' " << toString() << endl;
  FILE *fp = fopen(path.c_str(), "w");
  if (fp == nullptr) {
    errors.add("Image::write_binary: invalid file '" + path + "'");
  }
  image_header->write_header(fp, path, errors);
  // Write the data from the buffer.
  int newLen;
  switch (image_header->depth) {
    case CV_8U:
      newLen = fwrite(buf_8U, sizeof(pixel_8U), image_header->npixels, fp);
      if (ferror(fp) != 0) {
        errors.add("Image::write_binary: cannot write 8U image data to '" + path + "'");
      }
      break;
    case CV_32S:
      newLen = fwrite(buf_32S, sizeof(pixel_32S), image_header->npixels, fp);
      if (ferror(fp) != 0) {
        errors.add("Image::write_binary: cannot write 32S image data to '" + path + "'");
      }
      break;
    case CV_32F:
      newLen = fwrite(buf_32F, sizeof(pixel_32F), image_header->npixels, fp);
      if (ferror(fp) != 0) {
        errors.add("Image::write_binary: cannot write 32F image data to '" + path + "'");
      }
      break;
    default:
      break;
  }
  fclose(fp);
}

void Image::write_jpeg(string path, Errors &errors) {
  if (get_depth() != CV_8U) {
    errors.add("Image::write_jpeg: cannot write "
                   + image_depth_enum_to_string(get_depth())
                   + " image");
  }
  int quality = 100; // best
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  /* More stuff */
  FILE *outfile;        /* target file */
  JSAMPROW row_pointer[1];    /* pointer to JSAMPLE row[s] */
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
  cinfo.image_width = get_cols();
  cinfo.image_height = get_rows();
  cinfo.input_components = 1; // hardcode grayscale for now
  cinfo.in_color_space = JCS_GRAYSCALE;    /* colorspace of input image */
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
    row_pointer[0] = (JSAMPROW) &buf_8U[cinfo.next_scanline * get_row_stride()];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  /* Step 6: Finish compression */
  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  fclose(outfile);
  /* Step 7: release JPEG compression object */
  jpeg_destroy_compress(&cinfo);
}

string Image::toString() {
  ostringstream os;
  os << image_header->toString()
     << " next_pixel " << next_pixel;
  return os.str();
}




