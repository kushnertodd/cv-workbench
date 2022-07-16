//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HPP_

#include <exception>
#include <string>
#include "bounds.hpp"
#include "errors.hpp"
#include "histogram.hpp"
#include "image_header.hpp"
#include "line_segment.hpp"
#include "point.hpp"
#include "wb_defs.hpp"

// for read_jpeg()
struct my_error_mgr {
  struct jpeg_error_mgr pub;    /* "public" fields */
  jmp_buf setjmp_buffer;    /* for return to caller */
};
typedef struct my_error_mgr *my_error_ptr;

/**
 * Numerically Stable Parallel Computation of (Co-)Variance, Erich Schubert, Michael Gertz
 * https://dbs.ifi.uni-heidelberg.de/files/Team/eschubert/publications/SSDBM18-covariance-authorcopy.pdf
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
 */
class Image {
 public:
  Image_header *image_header;
  int next_pixel;
  // image stores one buffer per image_header->depth
  pixel_8U *buf_8U;
  // pixel_8S *buf_8S; // unsupported
  // pixel_16U *buf_16U; // unsupported
  // pixel_16S *buf_16S; // unsupported
  pixel_32F *buf_32F;
  pixel_32S *buf_32S;
  // pixel_64F *buf_64F; // unsupported
  // pixel_16F *buf_16F; // unsupported

  virtual ~Image();
  Image(int m_rows, int m_cols, int m_components, cv_enums::CV_image_depth m_depth);
  explicit Image(Image_header *image_header);

  // TODO: add component
  void add_8U(const pixel_8U *src, int count, Errors &errors);
  void add_32F(const pixel_32F *src, int count, Errors &errors);
  void add_32S(pixel_32S *src, int count, Errors &errors);

  bool check_grayscale(Errors &errors) const;
  static Image *clone_image(Image *image, cv_enums::CV_image_depth depth);
  void create_histogram(Histogram &histogram) const;
  void draw_line_segment(Line_segment *line_segment, float value) const;
  void draw_line_segments(std::list<Line_segment *> &line_segments, float value) const;

  // TODO: add component
  pixel_32F get(int row, int col) const;
  pixel_32F get(Point &point) const;
  pixel_8U get_8U(int row, int col) const;
  pixel_32F get_32F(int row, int col) const;
  pixel_32S get_32S(int row, int col) const;

  int get_cols() const;
  int get_components() const;
  cv_enums::CV_image_depth get_depth() const;
  int get_npixels() const;
  int get_row_stride() const;
  int get_rows() const;
  float get_scaled(int row, int col, float lower_in,
                   float upper_in, float lower_out,
                   float upper_out) const;
  void init();

  static Image *read(std::string &path, Errors &errors);

  static Image *read_jpeg(const std::string &path, Errors &errors);
  int row_col_to_index(int row, int col) const;
  static Image *scale_image(Image *image, float lower_in,
                            float upper_in, float lower_out,
                            float upper_out, cv_enums::CV_image_depth depth);
  static float scale_pixel(float in_value, float lower_in,
                           float upper_in, float lower_out,
                           float upper_out);

  // TODO: add component
  void set(int row, int col, float value) const;
  void set(Point *point, float value) const;
  void set_8U(int row, int col, pixel_8U value) const;
  void set_32F(int row, int col, pixel_32F value) const;
  void set_32S(int row, int col, pixel_32S value) const;

  Image *to_rgb(int components) const;
  std::string to_string() const;
  void write(const std::string &path, Errors &errors) const;
  void write_jpeg(const std::string &path, Errors &errors) const;
};

#endif //CV_WORKBENCH_SRC_IMAGE_HPP_
