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
#include "file_utils.hpp"
#include "image.hpp"
#include "jpeglib.h"
#include "wb_utils.hpp"

Image::~Image() {
  delete[] buf_8U;
  delete[] buf_32S;
  delete[] buf_32F;
}

Image::Image() = default;

Image::Image(int m_rows, int m_cols, int m_components,
             WB_image_depth::Image_depth m_depth, double value) :
    image_header(m_rows, m_cols, m_components, m_depth),
    buf_8U{},
    buf_32F{},
    buf_32S{},
    next_pixel(0) {
  init(value);
}

Image::Image(Image &image) :
    image_header(image.get_rows(), image.get_cols(), image.get_components(), image.get_depth()),
    buf_8U{},
    buf_32F{},
    buf_32S{},
    next_pixel(0) {
  int size = get_npixels();
  switch (get_depth()) {
    case WB_image_depth::Image_depth::CV_8U:
      buf_8U = new pixel_8U[size];
      for (int i = 0; i < size; i++)
        buf_8U[i] = image.buf_8U[i];
      break;
    case WB_image_depth::Image_depth::CV_32S:
      buf_32S = new pixel_32S[size];
      for (int i = 0; i < size; i++)
        buf_32S[i] = image.buf_32S[i];
      break;
    case WB_image_depth::Image_depth::CV_32F:
      buf_32F = new pixel_32F[size];
      for (int i = 0; i < size; i++)
        buf_32F[i] = image.buf_32F[i];
      break;
    default:
      break;
  }
}

Image::Image(Image_header &m_image_header, double value) :
    image_header(m_image_header),
    buf_8U(nullptr),
    buf_32F(nullptr),
    buf_32S(nullptr),
    next_pixel(0) {
  init(value);
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
      case WB_image_depth::Image_depth::CV_8U:
        buf_8U[next_pixel++] = src[i];
        break;
      case WB_image_depth::Image_depth::CV_32S:
        buf_32S[next_pixel++] = src[i];
        break;
      case WB_image_depth::Image_depth::CV_32F:
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
      case WB_image_depth::Image_depth::CV_8U:
        errors.add("Image::add_32F", "", "cannot update_input_value to 8U buffer");
        break;
      case WB_image_depth::Image_depth::CV_32S:
        buf_32S[next_pixel++] = wb_utils::float_to_int_round(src[i]);
        break;
      case WB_image_depth::Image_depth::CV_32F:
        buf_32F[next_pixel++] = src[i];
        break;
      default:
        break;
    }
  }
}

void Image::add_32S(pixel_32S *src, int count, Errors &errors) {
  if (next_pixel + count > get_npixels()) {
    errors.add("Image::add_32S", "", "adding "
        + wb_utils::int_to_string(count) + " pixels at position " +
        wb_utils::int_to_string(next_pixel)
        + " too large for buffer length "
        + wb_utils::int_to_string(get_npixels()));
    return;
  }
  if (get_depth() == WB_image_depth::Image_depth::CV_8U) {
    errors.add("Image::add_32S", "", "cannot update_input_value to 8U buffer");
    return;
  }
  for (int i = 0; i < count; i++) {
    switch (get_depth()) {
      case WB_image_depth::Image_depth::CV_8U:
        break;
      case WB_image_depth::Image_depth::CV_32S:
        buf_32S[next_pixel++] = src[i];
        break;
      case WB_image_depth::Image_depth::CV_32F:
        buf_32F[next_pixel++] = wb_utils::int_to_float(src[i]);
        break;
      default:
        break;
    }
  }
}

bool Image::check_color(int component, const std::string &module, Errors &errors) const {
  if (component >= get_components()) {
    errors.add(module, "", "image does not have enough components");
    return false;
  }
  return true;
}

bool Image::check_grayscale(const std::string &module, Errors &errors) const {
  if (get_components() != 1) {
    errors.add(module, "", "image not grayscale");
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
Image *Image::clone(Image *image, WB_image_depth::Image_depth depth, Errors &errors) {
  auto *new_image = new Image(image->get_rows(),
                              image->get_cols(),
                              image->get_components(),
                              depth);
  new_image->copy(image, errors);
  return new_image;
}

/**
 * return linear combination of input images:
 * pixel_32F output-pixel = image1-pixel * scale1 + image2-pixel * scale2 + offset;
 * grayscale only
 * @param image1
 * @param image2
 * @param scale1
 * @param scale2
 * @param offset
 * @param errors
 * @return
 */
Image *Image::combine(Image *input1, Image *input2, double scale1, double scale2, double offset,
                      Errors &errors) {
  int rows1 = input1->get_rows();
  int cols1 = input1->get_cols();

  int rows2 = input2->get_rows();
  int cols2 = input2->get_cols();

  int rows_out = std::min(rows1, rows2);
  int cols_out = std::min(cols1, cols2);
  WB_image_depth::Image_depth depth1 = input1->get_depth();
  WB_image_depth::Image_depth depth2 = input2->get_depth();
  WB_image_depth::Image_depth depth;
  if (depth1 == WB_image_depth::Image_depth::CV_32F
      || depth2 == WB_image_depth::Image_depth::CV_32F)
    depth = WB_image_depth::Image_depth::CV_32F;
  else if (depth1 == WB_image_depth::Image_depth::CV_32S
      || depth2 == WB_image_depth::Image_depth::CV_32S)
    depth = WB_image_depth::Image_depth::CV_32S;
  else
    depth = WB_image_depth::Image_depth::CV_8U;
  auto *output = new Image(rows_out, cols_out, 1, depth);
  int row_origin1 = (rows1 - rows_out) / 2;
  int col_origin1 = (cols1 - cols_out) / 2;
  int row_origin2 = (rows2 - rows_out) / 2;
  int col_origin2 = (cols2 - cols_out) / 2;

  for (int row = 0; row < rows_out; row++)
    for (int col = 0; col < cols_out; col++) {
      double pixel1 = input1->get(row + row_origin1 + input1->get_min_row(), col + col_origin1);
      double pixel2 = input2->get(row + row_origin2 + input2->get_min_row(), col + col_origin2);
      double value = pixel1 * scale1 + pixel2 * scale2 + offset;
      output->set(row, col, value);
    }
  return output;
}

// copies CV_32S and CV_32F to CV_8U with truncation to 0..255
void Image::copy(Image *image, Errors &errors) const {
  if (get_npixels() != image->get_npixels()) {
    errors.add("Image::copy", "", "images not the same size ");
    return;
  }
  if (get_depth() != image->get_depth()) {
    errors.add("Image::copy", "", "images not the same depth ");
    return;
  }
  if (get_depth() == WB_image_depth::Image_depth::CV_8U &&
      image->get_depth() == WB_image_depth::Image_depth::CV_32S) {
    errors.add("Image::copy", "", "cannot copy CV_32S image to CV_8U image ");
    return;
  }
  if (get_depth() == WB_image_depth::Image_depth::CV_8U &&
      image->get_depth() == WB_image_depth::Image_depth::CV_32F) {
    errors.add("Image::copy", "", "cannot copy CV_32F image to CV_8U image ");
    return;
  }
  if (get_depth() == WB_image_depth::Image_depth::UNDEFINED
      || image->get_depth() == WB_image_depth::Image_depth::UNDEFINED) {
    errors.add("Image::copy", "", "cannot copy images of undefined depth ");
    return;
  }
  switch (get_depth()) {
    case WB_image_depth::Image_depth::CV_8U:
      for (int i = 0; i < get_npixels(); i++)
        buf_8U[i] = image->buf_8U[i];
      break;
    case WB_image_depth::Image_depth::CV_32S:
      switch (image->get_depth()) {
        case WB_image_depth::Image_depth::CV_8U:
          for (int i = 0; i < get_npixels(); i++)
            buf_32S[i] = image->buf_8U[i];
          break;
        case WB_image_depth::Image_depth::CV_32S:
          for (int i = 0; i < get_npixels(); i++)
            buf_32S[i] = image->buf_32S[i];
          break;
        case WB_image_depth::Image_depth::CV_32F:
          for (int i = 0; i < get_npixels(); i++)
            buf_32S[i] = wb_utils::float_to_int_round(image->buf_32F[i]);
          break;
        default:
          break;
      }
      break;
    case WB_image_depth::Image_depth::CV_32F:
      switch (image->get_depth()) {
        case WB_image_depth::Image_depth::CV_8U:
          for (int i = 0; i < get_npixels(); i++)
            buf_32F[i] = image->buf_8U[i];
          break;
        case WB_image_depth::Image_depth::CV_32S:
          for (int i = 0; i < get_npixels(); i++)
            buf_32F[i] = wb_utils::int_to_float(image->buf_32S[i]);
          break;
        case WB_image_depth::Image_depth::CV_32F:
          for (int i = 0; i < get_npixels(); i++)
            buf_32F[i] = image->buf_32F[i];
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void Image::draw_line_segment(const Line_segment &line_segment, double value, int component) const {
  for (Point point: line_segment.line_points)
    set(point, value, component);
}

void Image::draw_line_segment(int row1, int col1, int row2, int col2, double value, int component) const {
  Line_segment line_segment(row1, col1, row2, col2);
  for (Point point: line_segment.line_points)
    set(point, value, component);
}

void Image::draw_line_segments(std::list<Line_segment> &line_segments, double value, int component) const {
  for (const Line_segment &line_segment: line_segments)
    draw_line_segment(line_segment, value, component);
}

void Image::draw_rectangle(int row1, int col1, int row2, int col2, double value, int component) const {
  Line_segment line_segment1(row1, col1, row1, col2);
  Line_segment line_segment2(row1, col2, row2, col2);
  Line_segment line_segment3(row2, col2, row2, col1);
  Line_segment line_segment4(row2, col1, row1, col1);
  draw_line_segment(line_segment1, value, component);
  draw_line_segment(line_segment2, value, component);
  draw_line_segment(line_segment3, value, component);
  draw_line_segment(line_segment4, value, component);
}

void Image::draw_rectangle_filled(int row1, int col1, int row2, int col2, double value, int component) const {
  int row_min = std::min(row1, row2);
  int col_min = std::min(col1, col2);
  int row_max = std::max(row1, row2);
  int col_max = std::max(col1, col2);
  for (int row = row_min; row <= row_max; row++)
    for (int col = col_min; col <= col_max; col++)
      set(row, col, value, component);
}

double Image::get(int row, int col, int component) const {
  int index;
  switch (get_depth()) {
    case WB_image_depth::Image_depth::CV_8U:
      index = row_col_to_index(row, col, component);
      return buf_8U[index];
    case WB_image_depth::Image_depth::CV_32S:
      index = row_col_to_index(row, col, component);
      return (pixel_32F) buf_32S[index];
    case WB_image_depth::Image_depth::CV_32F:
      index = row_col_to_index(row, col, component);
      return buf_32F[index];
    default:
      return 0.0;
  }
}

double Image::get(Point &point, int component) const {
  return get(point.row, point.col, component);
}

pixel_8U Image::get_8U(int row, int col, int component) const {
  int index = row_col_to_index(row, col, component);
  return buf_8U[index];
}

pixel_32F Image::get_32F(int row, int col, int component) const {
  int index = row_col_to_index(row, col, component);
  return buf_32F[index];
}

pixel_32S Image::get_32S(int row, int col, int component) const {
  int index = row_col_to_index(row, col, component);
  return buf_32S[index];
}

double Image::get_scaled(int row, int col, double lower_in,
                         double upper_in, double lower_out,
                         double upper_out, int component) const {
  double pixel_in = get(row, col, component);
  double pixel_out = scale_pixel(pixel_in, lower_in,
                                 upper_in, lower_out, upper_out);
  return pixel_out;
}

/**
 * get image min/max value, mean, std dev, etc.
 * graysacle only
 * @param stats
 */
void Image::get_stats(Variance_stats &stats) const {
  for (int row = get_min_row(); row < get_rows(); row++)
    for (int col = get_min_col(); col < get_cols(); col++) {
      double value = get(row, col);
      stats.update(value);
    }
}

void Image::init(double value) {
  int size = get_npixels();
  switch (get_depth()) {
    case WB_image_depth::Image_depth::CV_8U: {
      int int_value = wb_utils::double_to_int(value);
      buf_8U = new pixel_8U[size];
      for (int i = 0; i < size; i++)
        buf_8U[i] = int_value;
      break;
    }
    case WB_image_depth::Image_depth::CV_32S: {
      int int_value = wb_utils::double_to_int(value);
      buf_32S = new pixel_32S[size];
      for (int i = 0; i < size; i++)
        buf_32S[i] = int_value;
      break;
    }
    case WB_image_depth::Image_depth::CV_32F: {
      float float_value = wb_utils::double_to_float(value);
      buf_32F = new pixel_32F[size];
      for (int i = 0; i < size; i++)
        buf_32F[i] = float_value;
      break;
    }
    default:
      break;
  }
}

void Image::log(std::list<WB_log_entry> &log_entries) const {
  Variance_stats stats;
  get_stats(stats);
  WB_log_entry log_entry_rows("rows", wb_utils::int_to_string(get_rows()));
  log_entries.push_back(log_entry_rows);
  WB_log_entry log_entry_cols("cols", wb_utils::int_to_string(get_cols()));
  log_entries.push_back(log_entry_cols);
  WB_log_entry log_entry_components("components", wb_utils::int_to_string(get_components()));
  log_entries.push_back(log_entry_components);
  WB_log_entry log_entry_depth("depth", WB_image_depth::to_string(get_depth()));
  log_entries.push_back(log_entry_depth);
  WB_log_entry log_entry_count("pixel count", wb_utils::int_to_string(get_npixels()));
  log_entries.push_back(log_entry_count);
  WB_log_entry log_entry_mean("pixel mean", wb_utils::double_to_string(stats.get_mean()));
  log_entries.push_back(log_entry_count);
  WB_log_entry
      log_entry_standard_deviation("pixel standard deviation", wb_utils::double_to_string(stats.get_standard_deviation()));
  log_entries.push_back(log_entry_standard_deviation);
  WB_log_entry log_entry_min_value("min pixel value", wb_utils::double_to_string(stats.get_min_value()));
  log_entries.push_back(log_entry_min_value);
  WB_log_entry log_entry_max_value("max pixel value", wb_utils::double_to_string(stats.get_max_value()));
  log_entries.push_back(log_entry_max_value);
}

Image *Image::read(std::string &path, Errors &errors) {
  FILE *fp = file_utils::open_file_read(path, errors);
  if (fp) {
    Image *image = Image::read(fp, errors);
    fclose(fp);
    return image;
  }
  return nullptr;
}

Image *Image::read(FILE *fp, Errors &errors) {
  Image_header image_header;
  image_header.read(fp, errors);
  if (errors.has_error())
    return nullptr;
  auto *image = new Image(image_header);

  // Read the data into buffer.
  switch (image_header.get_depth()) {
    case WB_image_depth::Image_depth::CV_8U:
      wb_utils::read_byte_buffer(fp,
                                 image->buf_8U,
                                 image->get_npixels(),
                                 "Image::read",
                                 "",
                                 "cannot read 8U image data",
                                 errors);
      if (errors.has_error()) {
        delete image;
        return nullptr;
      }
      break;
    case WB_image_depth::Image_depth::CV_32S:
      wb_utils::read_int_buffer(fp,
                                image->buf_32S,
                                image->get_npixels(),
                                "Image::read",
                                "",
                                "cannot read 32S image data",
                                errors);
      if (errors.has_error()) {
        delete image;
        return nullptr;
      }
      break;
    case WB_image_depth::Image_depth::CV_32F:
      wb_utils::read_float_buffer(fp,
                                  image->buf_32F,
                                  image->get_npixels(),
                                  "Image::read",
                                  "",
                                  "cannot read 32F image data",
                                  errors);
      if (errors.has_error()) {
        delete image;
        return nullptr;
      }
      break;
    case WB_image_depth::Image_depth::UNDEFINED:
    default:
      return nullptr;
      break;
  }
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
    errors.add("Image::read_jpeg", "", "jpeg read error");
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
  auto *image =
      new Image(cinfo.output_height, cinfo.output_width, cinfo.num_components, WB_image_depth::Image_depth::CV_8U);
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

Image *Image::read_text(const std::string &path, Errors &errors) {
  std::ifstream ifs = file_utils::open_file_read_text(path, errors);
  if (ifs) {
    Image *image = read_text(ifs, errors);
    ifs.close();
    return image;
  }
  return nullptr;
}

/**
 * convert tab-delimited file to image
 * grayscale only
 * @param ifs
 * @param errors
 * @return
 */
Image *Image::read_text(std::ifstream &ifs, Errors &errors) {
  int rows = 0;
  int cols = 0;
  bool first = true;
  std::string line;
  std::vector<std::vector<std::string>> lines;
  while (getline(ifs, line)) {
    std::vector<std::string> values = wb_utils::string_split(line);
    if (first) {
      first = false;
      cols = (int) values.size();
      lines.push_back(values);
    } else if (values.size() != cols) {
      std::ostringstream os;
      os << "invalid image file: initial column length " << cols
         << " row " << rows << " column length " << values.size();
      errors.add("Image::read_text", "", os.str());
      return nullptr;
    } else
      lines.push_back(values);
    rows++;
  }
  auto *image = new Image(rows, cols, 1, WB_image_depth::Image_depth::CV_32S);
  pixel_32S *buf_ptr = image->buf_32S;
  for (const std::vector<std::string> &row_values: lines)
    for (const std::string &value_str: row_values) {
      int value;
      if (wb_utils::string_to_int(value_str, value))
        *buf_ptr++ = value;
      else {
        errors.add("Image::read_text", "", "invalid value '" + value_str + "'");
        delete image;
        return nullptr;
      }
    }
  return image;
}

void Image::reset_subimage() {
  image_header.set_min_row(0);
  image_header.set_min_col(0);
  image_header.set_max_row(0);
  image_header.set_max_col(0);
}

int Image::row_col_to_index(int row, int col, int component) const {
  assert(component <= get_components());
  assert(row >= get_min_row());
  assert(row <= get_max_row());
  assert(col >= get_min_col());
  assert(col <= get_max_col());
  return row * get_row_stride() + col * get_components() + component;
}

/***
 * preconditions not checked:
 *   lower_in < lower_out
 *   upper_in < upper_out
 *   lower_out >= pixel_8U_MIN
 *   upper_out <= pixel_8U_MAX
 * scales all components
 * @param image
 * @param lower_in
 * @param upper_in
 * @param lower_out
 * @param upper_out
 * @return
 */
Image *Image::scale_image(Image *image, double lower_in,
                          double upper_in, double lower_out,
                          double upper_out, WB_image_depth::Image_depth depth) {
  auto *convert_image = new Image(image->get_rows(),
                                  image->get_cols(),
                                  image->get_components(),
                                  depth);
  for (int row = image->get_min_row(); row < image->get_rows(); row++)
    for (int col = image->get_min_col(); col < image->get_cols(); col++)
      for (int component = 0; component < image->get_components(); component++){
      double value = image->get_scaled(row, col, lower_in,
                                       upper_in, lower_out, upper_out, component);
      convert_image->set(row, col, value);
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

// -> CV_8U may lose precision/overflow
void Image::set(int row, int col, double value, int component) const {
  assert(component <= get_components());
  switch (get_depth()) {
    case WB_image_depth::Image_depth::CV_8U:
      buf_8U[row_col_to_index(row, col, component)] = wb_utils::double_to_int_round(value);
      break;
    case WB_image_depth::Image_depth::CV_32S:
      buf_32S[row_col_to_index(row, col, component)] = wb_utils::double_to_int_round(value);
      break;
    case WB_image_depth::Image_depth::CV_32F:
      buf_32F[row_col_to_index(row, col, component)] = wb_utils::double_to_float(value);
      break;
    default:
      break;
  }
}

void Image::set(Point &point, double value, int component) const {
  set(point.row, point.col, value, component);
}

void Image::set_8U(int row, int col, pixel_8U value, int component) const {
  buf_8U[row_col_to_index(row, col, component)] = value;
}

void Image::set_32F(int row, int col, pixel_32F value, int component) const {
  buf_32F[row_col_to_index(row, col, component)] = value;
}

void Image::set_32S(int row, int col, pixel_32S value, int component) const {
  buf_32S[row_col_to_index(row, col, component)] = value;
}

void Image::set_subimage(int min_row,
                         int min_col,
                         int max_row,
                         int max_col,
                         Errors &errors) {
  if (min_row < 0)
    errors.add("Image::set_subimage", "", "min_row outside image");
  if (min_row > max_row)
    errors.add("Image::set_subimage", "", "min_row over max_row");
  if (min_row >= image_header.get_rows())
    errors.add("Image::set_subimage", "", "max_row outside image");

  if (min_col < 0)
    errors.add("Image::set_subimage", "", "min_col outside image");
  if (min_col > max_col)
    errors.add("Image::set_subimage", "", "min_col over max_col");
  if (min_col >= image_header.get_cols())
    errors.add("Image::set_subimage", "", "max_col outside image");

  if (!errors.has_error()) {
    image_header.set_min_row(min_row);
    image_header.set_min_col(min_col);
    image_header.set_max_row(max_row);
    image_header.set_max_col(max_col);
  }
}

// subtracts image without underflow checking for CV_8U images
Image *Image::subtract(Image *src_image, Image *subtract_image, Errors &errors) {
  return Image::combine(src_image, subtract_image, 1.0, -1.0, 0.0, errors);
}

/**
 * convert grayscale image to rgb
 * preconditions:
 *   components = 1
 * @param component
 * @return
 */
Image *Image::to_rgb(int component) const {
  Image_header new_image_header(get_rows(),
                                get_cols(),
                                3,
                                get_depth());
  auto *new_image = new Image(new_image_header);
  for (int i = 0; i < new_image->get_npixels(); i++)
    switch (image_header.get_depth()) {
      case WB_image_depth::Image_depth::CV_8U:
        new_image->buf_8U[i * 3 + component] = buf_8U[i];
        break;
      case WB_image_depth::Image_depth::CV_32S:
        new_image->buf_32S[i * 3 + component] = buf_32S[i];
        break;
      case WB_image_depth::Image_depth::CV_32F:
        new_image->buf_32F[i * 3 + component] = buf_32F[i];
        break;
      default:
        break;
    }
  return new_image;
}

std::string Image::to_string(const std::string &prefix) const {
  std::ostringstream os;
  os << prefix << image_header.to_string(prefix + "    ");
  return os.str();
}

void Image::write(const std::string &path, Errors &errors) const {
  FILE *fp = file_utils::open_file_write(path, errors);
  if (fp) {
    write(fp, errors);
    fclose(fp);
  }
}

void Image::write(FILE *fp, Errors &errors) const {
  image_header.write(fp, errors);
  if (errors.has_error())
    return;
  // Write the data from the buffer.
  size_t newLen;
  switch (get_depth()) {
    case WB_image_depth::Image_depth::CV_8U:
      for (int row = get_min_row(); row < get_rows() && !errors.has_error(); row++) {
        for (int col = get_min_col(); col < get_cols() && !errors.has_error(); col++) {
          pixel_8U value = get_8U(row, col);
          newLen = fwrite(&value, sizeof(pixel_8U), 1, fp);
          if (ferror(fp) != 0 || newLen != 1)
            errors.add("Image::write", "", "cannot write 32F image data");
        }
      }
      break;
    case WB_image_depth::Image_depth::CV_32S:
      for (int row = get_min_row(); row < get_rows() && !errors.has_error(); row++) {
        for (int col = get_min_col(); col < get_cols() && !errors.has_error(); col++) {
          pixel_32S value = get_32S(row, col);
          newLen = fwrite(&value, sizeof(pixel_32S), 1, fp);
          if (ferror(fp) != 0 || newLen != 1)
            errors.add("Image::write", "", "cannot write 32F image data");
        }
      }
      break;
    case WB_image_depth::Image_depth::CV_32F:
      for (int row = get_min_row(); row < get_rows() && !errors.has_error(); row++) {
        for (int col = get_min_col(); col < get_cols() && !errors.has_error(); col++) {
          pixel_32F value = get_32F(row, col);
          newLen = fwrite(&value, sizeof(pixel_32F), 1, fp);
          if (ferror(fp) != 0 || newLen != 1)
            errors.add("Image::write", "", "cannot write 32F image data");
        }
      }
      break;
    default:
      break;
  }
}

void Image::write_jpeg(const std::string &path, Errors &errors) const {
  if (get_depth() != WB_image_depth::Image_depth::CV_8U) {
    errors.add("Image::write_jpeg", "", "cannot write "
        + WB_image_depth::to_string(get_depth())
        + " image");
    return;
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
  if ((outfile = fopen(path.c_str(), "wb")) == nullptr)
    errors.add("Image::write_jpeg", "", "invalid file '" + path + "'");
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
    row_pointer[0] = (JSAMPROW) &buf_8U[cinfo.next_scanline * get_row_stride() + get_min_col()];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  /* Step 6: Finish compression */
  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  fclose(outfile);
  /* Step 7: release JPEG compression object */
  jpeg_destroy_compress(&cinfo);
}

void Image::write_text(const std::string &path, const std::string &delim, Errors &errors) const {
  std::ofstream ofs = file_utils::open_file_write_text(path, errors);
  if (ofs) {
    write_text(ofs, "\t", errors);
    ofs.close();
  }
}

void Image::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  for (int row = get_min_row(); row < get_rows(); row++) {
    for (int col = get_min_col(); col < get_cols(); col++) {
      double value = get(row, col);
      ofs << value << delim;
    }
    ofs << std::endl;
  }
  ofs.close();
}

