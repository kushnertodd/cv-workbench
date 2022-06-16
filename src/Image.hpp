//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HPP_

#include <exception>
#include <string>
#include "errors.hpp"
#include "image_header.hpp"
#include "wb_enums.hpp"

using namespace std;

class Image_exception {
 private:
  string errmsg;
 public:
  Image_exception(string m_errmsg);
  Image_exception(string m_message, int size, int max_size);
  virtual const char *what() const noexcept;
};

class Image {
 public:
  Image_header *image_header;
  int next_pixel;
  // image stores one buffer per image_header->depth
  pixel_8U *buf_8U;
  pixel_8S *buf_8S; // unsupported
  pixel_16U *buf_16U; // unsupported
  pixel_16S *buf_16S; // unsupported
  pixel_32S *buf_32S;
  pixel_32F *buf_32F;
  pixel_64F *buf_64F; // unsupported
  pixel_16F *buf_16F; // unsupported

  virtual ~Image();
  Image(int m_rows, int m_cols, int m_components, Cv_image_depth_enum m_depth);
  Image(Image_header *image_header);
  void init();

  int get_rows();
  int get_cols();
  int get_components();
  int get_row_stride();
  int get_npixels();
  Cv_image_depth_enum get_depth();

  void add_8U(pixel_8U *src, int count, Errors &errors);
  void add_32S(pixel_32S *src, int count, Errors &errors);
  void add_32F(pixel_32F *src, int count, Errors &errors);
  static Image *read_binary(string path, Errors &errors);
  static Image *read_jpeg(string path, Errors &errors);
  void write_binary(string path, Errors &errors);
  void write_jpeg(string path, Errors &errors);

};

#endif //CV_WORKBENCH_SRC_IMAGE_HPP_
