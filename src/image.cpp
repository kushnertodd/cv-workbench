//
// Created by kushn on 6/11/2022.
//

#include <cassert>
#include <csetjmp>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "jpeglib.h"
#include "cv_data_format.hpp"
#include "cv_data_type.hpp"
#include "cv_image_depth.hpp"
#include "cv_repository_type.hpp"
#include "image.hpp"
#include "image_header.hpp"
#include "wb_utils.hpp"

extern bool debug;

Image::~Image() {
  delete[] buf_8U;
  delete[] buf_32S;
  delete[] buf_32F;
}

Image::Image(int m_rows, int m_cols, int m_components, CV_image_depth::depth m_depth) :
    image_header(m_rows, m_cols, m_components, m_depth),
    buf_8U(nullptr),
    buf_32F(nullptr),
    buf_32S(nullptr),
    next_pixel(0) {
  if (debug)
    std::cout << "Image::Image: " << to_string() << std::endl;
  init();
}

Image::Image(Image_header &m_image_header) :
    image_header(m_image_header),
    buf_8U(nullptr),
    buf_32F(nullptr),
    buf_32S(nullptr),
    next_pixel(0) {
  if (debug)
    std::cout << "Image::Image: " << to_string() << std::endl;
  init();
}

void Image::add_8U(const pixel_8U *src, int count, Errors &errors) {
  if (next_pixel + count > get_npixels())
    errors.add("Image::add_8U", "", "adding "
        + wb_utils::int_to_string(count) + " pixels at position " +
        wb_utils::int_to_string(next_pixel)
        + " too large for buffer length "
        + wb_utils::int_to_string(get_npixels()));
  for (int i = 0; i < count; i++) {
    switch (get_depth()) {
      case CV_image_depth::depth::CV_8U:
        buf_8U[next_pixel++] = src[i];
        break;

      case CV_image_depth::depth::CV_32S:
        buf_32S[next_pixel++] = src[i];
        break;

      case CV_image_depth::depth::CV_32F:
        buf_32F[next_pixel++] = src[i];
        break;

      default:
        break;
    }
  }
}

void Image::add_32F(const pixel_32F *src, int count, Errors &errors) {
  if (next_pixel + count > get_npixels())
    errors.add("Image::add_32F", "", "adding "
        + wb_utils::int_to_string(count) + " pixels at position " +
        wb_utils::int_to_string(next_pixel)
        + " too large for buffer length "
        + wb_utils::int_to_string(get_npixels()));
  for (int i = 0; i < count; i++) {
    switch (get_depth()) {
      case CV_image_depth::depth::CV_8U:
        errors.add("Image::add_32F", "", "cannot update to 8U buffer");
        break;

      case CV_image_depth::depth::CV_32S:
        buf_32S[next_pixel++] = wb_utils::round_float_to_int(src[i]);
        break;

      case CV_image_depth::depth::CV_32F:
        buf_32F[next_pixel++] = src[i];
        break;

      default:
        break;
    }
  }
}

void Image::add_32S(pixel_32S *src, int count, Errors &errors) {
  if (debug)
    std::cout << "Image::add_32S src " << src << " count " << count << " " << to_string() << std::endl;
  if (next_pixel + count > get_npixels())
    errors.add("Image::add_32S", "", "adding "
        + wb_utils::int_to_string(count) + " pixels at position " +
        wb_utils::int_to_string(next_pixel)
        + " too large for buffer length "
        + wb_utils::int_to_string(get_npixels()));
  for (int i = 0; i < count; i++) {
    switch (get_depth()) {
      case CV_image_depth::depth::CV_8U:
        errors.add("Image::add_32S", "", "cannot update to 8U buffer");
        break;

      case CV_image_depth::depth::CV_32S:
        buf_32S[next_pixel++] = src[i];
        break;

      case CV_image_depth::depth::CV_32F:
        buf_32F[next_pixel++] = wb_utils::int_to_float(src[i]);
        break;

      default:
        break;
    }
  }
}

bool Image::check_grayscale(Errors &errors) const {
  if (get_components() != 1) {
    errors.add("Image::check_grayscale", "", "image not grayscale");
    return false;
  }
  return true;
}
/***
 * Not really what want. Doesn't copy contents.
 * @param image
 * @param depth
 * @return
 */
/*
Image *Image::clone_image(Image *image, CV_image_depth::depth depth) {
  if (debug)
    std::cout << "Image::clone: depth " << depth << " " << image->to_string() << std::endl;
  auto *new_image = new Image(image->get_rows(),
                              image->get_cols(),
                              image->get_components(),
                              depth);
  return new_image;
}
*/

void Image::draw_line_segment(const Line_segment &line_segment, double value) const {
  if (debug)
    std::cout << "Hough::draw_lines; line_segment (" << line_segment.to_string()
              << ") value " << value << std::endl;
  for (Point point: line_segment.line_points) {
    set(point, value);
  }
}

void Image::draw_line_segments(std::list<Line_segment> &line_segments, double value) const {
  for (const Line_segment &line_segment: line_segments) {
    draw_line_segment(line_segment, value);
  }
}

double Image::get(int row, int col) const {
  int index;
  switch (get_depth()) {
    case CV_image_depth::depth::CV_8U:
      index = row_col_to_index(row, col);
      return buf_8U[index];

    case CV_image_depth::depth::CV_32S:
      index = row_col_to_index(row, col);
      return (pixel_32F) buf_32S[index];

    case CV_image_depth::depth::CV_32F:
      index = row_col_to_index(row, col);
      return buf_32F[index];

    default:
      return 0.0;
  }
}

double Image::get(Point &point) const {
  return get(point.row, point.col);
}

pixel_8U Image::get_8U(int row, int col) const {
  int index = row_col_to_index(row, col);
  return buf_8U[index];
}

pixel_32F Image::get_32F(int row, int col) const {
  int index = row_col_to_index(row, col);
  return buf_32F[index];
}

pixel_32S Image::get_32S(int row, int col) const {
  int index = row_col_to_index(row, col);
  return buf_32S[index];
}

int Image::get_cols() const { return image_header.cols; }

int Image::get_components() const { return image_header.components; }

CV_image_depth::depth Image::get_depth() const { return image_header.depth; }

int Image::get_npixels() const { return image_header.npixels; }

int Image::get_row_stride() const { return image_header.row_stride; }

int Image::get_rows() const { return image_header.rows; }

double Image::get_scaled(int row, int col, double lower_in,
                         double upper_in, double lower_out,
                         double upper_out) const {
  double pixel_in = get(row, col);
  double pixel_out = scale_pixel(pixel_in, lower_in,
                                 upper_in, lower_out, upper_out);
  return pixel_out;
}

void Image::get_stats(Variance_stats &stats) const {
  for (int row = 0; row < get_rows(); row++) {
    for (int col = 0; col < get_cols(); col++) {
      double value = get(row, col);
      stats.update(value);
    }
  }
}

void Image::init() {
  int size = get_npixels();
  switch (get_depth()) {
    case CV_image_depth::depth::CV_8U:
      buf_8U = new pixel_8U[size];
      for (int i = 0; i < size; i++)
        buf_8U[i] = 0;
      break;

    case CV_image_depth::depth::CV_32S:
      buf_32S = new pixel_32S[size];
      for (int i = 0; i < size; i++)
        buf_32S[i] = 0;
      break;

    case CV_image_depth::depth::CV_32F:
      buf_32F = new pixel_32F[size];
      for (int i = 0; i < size; i++)
        buf_32F[i] = 0.0;
      break;

    default:
      break;
  }
}

Image *Image::read(std::string &path, Errors &errors) {
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == nullptr) {
    errors.add("Image::read", "", "invalid file '" + path + "' " + std::string(strerror(errno)) + "'");
    return nullptr;
  }

  Image_header image_header;
  image_header.read(fp, path, errors);
  if (errors.error_ct != 0)
    return nullptr;
  auto *image = new Image(image_header);

  // Read the data into buffer.
  size_t newLen;

  switch (image_header.depth) {
    case CV_image_depth::depth::CV_8U:
      wb_utils::read_byte_buffer(fp,
                                 image->buf_8U,
                                 image->get_npixels(),
                                 "Image::read",
                                 "",
                                 "cannot read 8U image data in '" + path + "'",
                                 errors);
      if (errors.error_ct != 0)
        return nullptr;
      break;

    case CV_image_depth::depth::CV_32S:
      wb_utils::read_int_buffer(fp,
                                image->buf_32S,
                                image->get_npixels(),
                                "Image::read",
                                "",
                                "cannot read 32S image data in '" + path + "'",
                                errors);
      if (errors.error_ct != 0)
        return nullptr;
      break;

    case CV_image_depth::depth::CV_32F:
      wb_utils::read_float_buffer(fp,
                                  image->buf_32F,
                                  image->get_npixels(),
                                  "Image::read",
                                  "",
                                  "cannot read 32F image data in '" + path + "'",
                                  errors);
      if (errors.error_ct != 0)
        return nullptr;
      break;

    default:
      break;
  }
  fclose(fp);
  return image;
}

// for read_jpeg()
struct my_error_mgr {
  struct jpeg_error_mgr pub;    /* "public" fields */
  jmp_buf setjmp_buffer;    /* for return to caller */
};
typedef struct my_error_mgr *my_error_ptr;

// for read_jpeg()
void my_error_exit(j_common_ptr cinfo) {
  my_error_ptr myerr = (my_error_ptr) cinfo->err;
  (*cinfo->err->output_message)(cinfo);
  longjmp(myerr->setjmp_buffer, 1);
}

Image *Image::read_jpeg(const std::string &path, Errors &errors) {
  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;
  JSAMPARRAY buffer;
  FILE *fp = fopen(path.c_str(), "r");
  if (fp == nullptr) {
    errors.add("Image::read_jpeg", "", "invalid file '" + path + "'");
    return nullptr;
  }
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  if (setjmp(jerr.setjmp_buffer)) {
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);
    errors.add("Image::read_jpeg", "", "jpeg read error in '" + path + "'");
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
  auto *image = new Image(cinfo.output_height, cinfo.output_width, cinfo.num_components, CV_image_depth::depth::CV_8U);
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

int Image::row_col_to_index(int row, int col) const {
  assert(row >= 0 && row < get_rows() && col >= 0 && col < get_cols());
  return row * get_row_stride() + col;
}

/***
 * preconditions not checked:
 *   lower_in < lower_out
 *   upper_in < upper_out
 *   lower_out >= pixel_8U_MIN
 *   upper_out <= pixel_8U_MAX
 * @param image
 * @param lower_in
 * @param upper_in
 * @param lower_out
 * @param upper_out
 * @return
 */
Image *Image::scale_image(Image *image, double lower_in,
                          double upper_in, double lower_out,
                          double upper_out, CV_image_depth::depth depth) {
  if (debug)
    std::cout << "Image *Image::scale_image: lower_in " << lower_in
              << " upper_in " << upper_in
              << " lower_out " << lower_out
              << " upper_out " << upper_out << " depth " << CV_image_depth::image_depth_enum_to_string(depth) << std::endl;
  auto *convert_image = new Image(image->get_rows(),
                                  image->get_cols(),
                                  image->get_components(),
                                  depth);
  for (int row = 0; row < image->get_rows(); row++) {
    for (int col = 0; col < image->get_cols(); col++) {
      double value = image->get_scaled(row, col, lower_in,
                                       upper_in, lower_out, upper_out);
      convert_image->set(row, col, value);
    }
  }
  return convert_image;
}

double Image::scale_pixel(double pixel_in,
                          double in_lower,
                          double in_upper,
                          double out_lower,
                          double out_upper) {
  Bounds in_bounds(in_lower, in_upper);
  Bounds out_bounds(out_lower, out_upper);
  double pixel_out = Bounds::map_input_to_output_bounds(pixel_in, in_bounds, out_bounds);
  return pixel_out;
}

void Image::set(int row, int col, double value) const {
  switch (get_depth()) {
    case CV_image_depth::depth::CV_8U:
      buf_8U[row_col_to_index(row, col)] = wb_utils::round_double_to_int(value);
      break;

    case CV_image_depth::depth::CV_32S:
      buf_32S[row_col_to_index(row, col)] = wb_utils::round_double_to_int(value);
      break;

    case CV_image_depth::depth::CV_32F:
      buf_32F[row_col_to_index(row, col)] = wb_utils::double_to_float(value);
      break;

    default:
      break;
  }
}

void Image::set(Point &point, double value) const {
  set(point.row, point.col, value);
}

void Image::set_8U(int row, int col, pixel_8U value) const {
  buf_32F[row_col_to_index(row, col)] = value;
}

void Image::set_32F(int row, int col, pixel_32F value) const {
  buf_32F[row_col_to_index(row, col)] = value;
}

void Image::set_32S(int row, int col, pixel_32S value) const {
  buf_32S[row_col_to_index(row, col)] = value;
}

/**
 * convert grayscale image to rgb
 * preconditions:
 *   components = 1
 * @param component
 * @return
 */
Image *Image::to_rgb(int component) const {
  if (debug)
    std::cout << "Image::clone: component " << component << " " << to_string() << std::endl;
  Image_header new_image_header(get_rows(),
                                get_cols(),
                                3,
                                get_depth());
  auto *new_image = new Image(new_image_header);
  for (int i = 0; i < new_image->get_npixels(); i++) {
    switch (image_header.depth) {
      case CV_image_depth::depth::CV_8U:
        new_image->buf_8U[i * 3 + component] = buf_8U[i];
        break;
      case CV_image_depth::depth::CV_32S:
        new_image->buf_32S[i * 3 + component] = buf_32S[i];
        break;
      case CV_image_depth::depth::CV_32F:
        new_image->buf_32F[i * 3 + component] = buf_32F[i];
        break;
      default:
        break;
    }
  }
  return new_image;
}

std::string Image::to_string(std::string prefix) const {
  std::ostringstream os;
  os << prefix << "image:" << std::endl
   << image_header.to_string(prefix+"    ");
  return os.str();
}

void Image::write(const std::string &path, Errors &errors) const {
  if (debug)
    std::cout << "Image::write path '" << path << "' " << to_string() << std::endl;
  FILE *fp = fopen(path.c_str(), "w");
  if (fp == nullptr) {
    errors.add("Image::write", "", "invalid file '" + path + "'");
  }
  image_header.write(fp, path, errors);
  // Write the data from the buffer.
  size_t newLen;
  switch (get_depth()) {
    case CV_image_depth::depth::CV_8U:
      newLen = fwrite(buf_8U, sizeof(pixel_8U), get_npixels(), fp);
      if (ferror(fp) != 0 || newLen != get_npixels()) {
        errors.add("Image::write", "", "cannot write 8U image data to '" + path + "'");
      }
      break;
    case CV_image_depth::depth::CV_32S:
      newLen = fwrite(buf_32S, sizeof(pixel_32S), get_npixels(), fp);
      if (ferror(fp) != 0 || newLen != get_npixels()) {
        errors.add("Image::write", "", "cannot write 32S image data to '" + path + "'");
      }
      break;
    case CV_image_depth::depth::CV_32F:
      newLen = fwrite(buf_32F, sizeof(pixel_32F), get_npixels(), fp);
      if (ferror(fp) != 0 || newLen != get_npixels()) {
        errors.add("Image::write", "", "cannot write 32F image data to '" + path + "'");
      }
      break;
    default:
      break;
  }
  fclose(fp);
}

void Image::write_jpeg(const std::string &path, Errors &errors) const {
  if (get_depth() != CV_image_depth::depth::CV_8U) {
    errors.add("Image::write_jpeg", "", "cannot write "
        + CV_image_depth::image_depth_enum_to_string(get_depth())
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
  if ((outfile = fopen(path.c_str(), "wb")) == nullptr) {
    errors.add("Image::write_jpeg", "", "invalid file '" + path + "'");
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

void Image::write_text(const std::string &path,  const std::string &delim, Errors &errors) const {
  if (debug)
    std::cout << "Image::write_text path '" << path << "' " << to_string() << std::endl;
  std::ofstream ofs(path, std::ofstream::out);
  if (!ofs) {
    errors.add("Histogram::write_text", "", "invalid file '" + path + "'");
    return;
  }
      for (int row = 0; row < get_rows(); row++){
        for (int col = 0; col < get_cols(); col++) {
          ofs << get(row, col) << delim << std::endl;
        }
      ofs << std::endl;
      }
  ofs.close();
}

