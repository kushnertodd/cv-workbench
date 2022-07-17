#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "errors.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "hough_accum.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"

Variance_stats variance_stats;

void error_exit(std::string message) {
  printf("%s\n", message.c_str());
  exit(0);
}

void stat_8U(pixel_8U *buf_8U, int rows, int cols) {
}

void stat_32S(Image *in_image, Hough &hough) {
}

void stat_32F(pixel_32F *buf_32F, int rows, int cols) {
}

bool debug = true;
int main(int argc, char **argv) {
  if (argc < 5)
    error_exit("usage: image-polar image-in-filename image-out-filename theta_index rho_index");
  std::string image_in_filename = argv[1];
  std::string image_out_filename = argv[2];
  std::string theta_index_str = argv[3];
  std::string rho_str = argv[4];

  int theta_index;
  if (!wb_utils::string_to_int(theta_index_str, theta_index)) {
    std::cout << "image-polar invalid theta_index value '" + theta_index_str + "'" << std::endl;
    exit(0);
  }
  double rho;
  if (!wb_utils::string_to_real(rho_str, rho)) {
    std::cout << "image-polar invalid rho_index value '" + rho_str + "'" << std::endl;
    exit(0);
  }
  Errors errors;
  Image *in_image = Image::read_jpeg(image_in_filename, errors);
  errors.check_exit("image-polar: reading " + image_in_filename);
  if (in_image != nullptr)
    in_image->check_grayscale(errors);
  Hough hough(in_image, 3);
  int rho_index = hough.accum->rho_to_index(rho);
  Polar_line polar_line(rho_index, rho, theta_index,
                        hough.accum->get_cos(theta_index), hough.accum->get_sin(theta_index),0);
  Line_segment line_segment; if (!hough.accum->clip_window(line_segment,polar_line)) {
    std::cout << "failed clipping (" << theta_index << ", " << rho
              << " against image " << in_image->to_string() << std::endl;
    exit(0);
  }
  in_image->draw_line_segment(line_segment, 0);
  in_image->write_jpeg(image_out_filename, errors);
  errors.check_exit("image-polar: writing " + image_out_filename);
}