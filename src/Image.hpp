//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HPP_

#include <exception>
#include <string>
#include "errors.hpp"

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
  int rows;
  int cols;
  int components;
  int row_stride;
  int nbytes;
  int next_pos;
  char *buf;
  bool allocated;

  virtual ~Image();
  Image(int m_rows, int m_cols, int m_components);
  void add(char *src, int count);
  static Image *create_image_allocated_buffer(int m_rows, int m_cols, int m_components);
  static Image *create_image_assigned_buffer(int m_rows, int m_cols, int m_components, char *m_buf);
  static Image *read_binary(string path, Errors &errors);
  static Image *read_jpeg(string path, Errors &errors);
  void write_binary(string path, Errors &errors);
  void write_jpeg(string path, Errors &errors);

};

#endif //CV_WORKBENCH_SRC_IMAGE_HPP_
