//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HPP_

#include <exception>
#include <string>
#include "bounds.hpp"
#include "errors.hpp"
#include "image_header.hpp"
#include "point.hpp"
#include "wb_defs.hpp"
#include "line_segment.hpp"

class Image_exception {
 private:
  string errmsg;
 public:
  Image_exception(string m_errmsg);
  Image_exception(string m_message, int size, int max_size);
  virtual const char *what() const noexcept;
};

/**
 * Numerically Stable Parallel Computation of (Co-)Variance, Erich Schubert, Michael Gertz
 * https://dbs.ifi.uni-heidelberg.de/files/Team/eschubert/publications/SSDBM18-covariance-authorcopy.pdf
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
 */
class Image {
 public:
  Image_header *image_header;
  Bounds bounds;
  int next_pixel;
  // image stores one buffer per image_header->depth
  pixel_8U *buf_8U;
  // pixel_8S *buf_8S; // unsupported
  // pixel_16U *buf_16U; // unsupported
  // pixel_16S *buf_16S; // unsupported
  pixel_32S *buf_32S; // unused yet
  pixel_32F *buf_32F;
  // pixel_64F *buf_64F; // unsupported
  // pixel_16F *buf_16F; // unsupported

  virtual ~Image();
  Image(int m_rows, int m_cols, int m_components, cv_enums::CV_image_depth m_depth);
  Image(Image_header *image_header);
  static Image *clone_image(Image *image, cv_enums::CV_image_depth depth);
  Image *to_rgb(int components);
  void init();

  int get_rows();
  int get_cols();
  int get_components();
  int get_row_stride();
  int get_npixels();
  cv_enums::CV_image_depth get_depth();

  int row_col_to_index(int row, int col);

  // TODO: add component
  pixel_32F get(int row, int col);
  pixel_32F get(Point *point);
  pixel_8U get_8U(int row, int col);
  pixel_32S get_32S(int row, int col);
  pixel_32S get_32F(int row, int col);

  void set(int row, int col, float value);
  void set(Point *point, float value);
  void set_8U(int row, int col, pixel_8U value);
  void set_32S(int row, int col, pixel_32S value);
  void set_32F(int row, int col, pixel_32F value);

  void add_8U(pixel_8U *src, int count, Errors &errors);
  void add_32S(pixel_32S *src, int count, Errors &errors);
  void add_32F(pixel_32F *src, int count, Errors &errors);

  void draw_line_segments(list<Line_segment *> line_segments, float value);
  void draw_line_segment(Line_segment *line_segment, float value);
  static Image *read_binary(string path, Errors &errors);
  static Image *read_jpeg(string path, Errors &errors);
  void write_binary(string path, Errors &errors);
  void write_jpeg(string path, Errors &errors);

  static float scale_pixel(float in_value, float lower_in,
                           float upper_in, float lower_out,
                           float upper_out);
  float get_scaled(int row, int col, float lower_in,
                   float upper_in, float lower_out,
                   float upper_out);
  static Image *scale_image(Image *image, float lower_in,
                            float upper_in, float lower_out,
                            float upper_out, cv_enums::CV_image_depth depth);
  string to_string();
};

#endif //CV_WORKBENCH_SRC_IMAGE_HPP_
