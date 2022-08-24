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
#include "line_segment.hpp"
#include "wb_log.hpp"
#include "point.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"

/**
 * Numerically Stable Parallel Computation of (Co-)Variance, Erich Schubert, Michael Gertz
 * https://dbs.ifi.uni-heidelberg.de/files/Team/eschubert/publications/SSDBM18-covariance-authorcopy.pdf
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
 */
class Image {
 public:
  Image_header image_header;
  int next_pixel{};
  // image stores one buffer per image_header->depth
  pixel_8U *buf_8U{};
  // pixel_8S *buf_8S; // unsupported
  // pixel_16U *buf_16U; // unsupported
  // pixel_16S *buf_16S; // unsupported
  pixel_32F *buf_32F{};
  pixel_32S *buf_32S{};
  // pixel_64F *buf_64F; // unsupported
  // pixel_16F *buf_16F; // unsupported

  virtual ~Image();
  Image();
  Image(int m_rows, int m_cols, int m_components, WB_image_depth::Image_depth m_depth, double value = 0.0);
  Image(Image &image);
  explicit Image(Image_header &image_header, double value = 0.0);

  // TODO: add component
  void add_8U(const pixel_8U *src, int count, Errors &errors);
  void add_32F(const pixel_32F *src, int count, Errors &errors);
  void add_32S(pixel_32S *src, int count, Errors &errors);

  bool check_grayscale(std::string module, Errors &errors) const;
  static Image *clone(Image *image, WB_image_depth::Image_depth depth, Errors &errors);
  static Image *combine(Image *image1, Image *image2, double scale1, double scale2, double offset,
                        Errors &errors);
  void copy(Image *image, Errors &errors) const;

  void draw_line_segment(const Line_segment &line_segment, double value) const;
  void draw_line_segment(int row1, int col1, int row2, int col2, double value) const;
  void draw_line_segments(std::list<Line_segment> &line_segments, double value) const;
  void draw_rectangle(int row1, int col1, int row2, int col2, double value) const;
  void draw_rectangle_filled(int row1, int col1, int row2, int col2, double value) const;

  // TODO: add component
  double get(int row, int col) const;
  double get(Point &point) const;
  pixel_8U get_8U(int row, int col) const;
  pixel_32F get_32F(int row, int col) const;
  pixel_32S get_32S(int row, int col) const;

  int get_cols() const;
  int get_components() const;
  WB_image_depth::Image_depth get_depth() const;
  int get_npixels() const;
  int get_row_stride() const;
  int get_rows() const;
  double get_scaled(int row, int col, double lower_in,
                    double upper_in, double lower_out,
                    double upper_out) const;
  void get_stats(Variance_stats &stats) const;
  void init(double value = 0.0);

  void log(std::list<WB_log_entry> &log_entries) const;

  static Image *read(std::string &path, Errors &errors);
  static Image *read(FILE *fp, Errors &errors);
  static Image *read_text(const std::string &path, Errors &errors);
  static Image *read_text(std::ifstream &ifs, Errors &errors);

  static Image *read_jpeg(const std::string &path, Errors &errors);
  int row_col_to_index(int row, int col) const;
  static Image *scale_image(Image *image, double lower_in,
                            double upper_in, double lower_out,
                            double upper_out, WB_image_depth::Image_depth depth);
  static double scale_pixel(double in_value, double lower_in,
                            double upper_in, double lower_out,
                            double upper_out);
  static Image *subtract(Image *src_image, Image *subtract_image, Errors &errors);

  // TODO: add component
  void set(int row, int col, double value) const;
  void set(Point &point, double value) const;
  void set_8U(int row, int col, pixel_8U value) const;
  void set_32F(int row, int col, pixel_32F value) const;
  void set_32S(int row, int col, pixel_32S value) const;

  Image *to_rgb(int components) const;
  std::string to_string(const std::string &prefix = "") const;
  void write(const std::string &path, Errors &errors) const;
  void write(FILE *fp, Errors &errors) const;
  void write_text(const std::string &path, const std::string &delim, Errors &errors) const;
  void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
  void write_jpeg(const std::string &path, Errors &errors) const;
};

#endif //CV_WORKBENCH_SRC_IMAGE_HPP_
