#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include "errors.hpp"
#include "file_utils.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "hough_accum.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"

Variance_stats variance_stats;

void error_exit(const std::string &message) {
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
  if (argc < 3)
    error_exit("usage: image-hough image-filename line-filename");
  std::string image_filename = argv[1];
  std::string line_filename = argv[2];
  Errors errors;
  Image *in_image = Image::read_jpeg(image_filename, errors);
  Hough* hough = Hough::create_image(in_image, 3, 200);

  std::ifstream ifs(line_filename);
  if (!ifs) {
    std::cout << "invalid filename: " << line_filename << std::endl;
    exit(1);
  }
  std::string line;
  while (getline(ifs, line)) {
    std::vector<std::string> fields = file_utils::string_split(line);
    double rho;
    int theta_index;
    if (!wb_utils::string_to_double(fields[0], rho)) {
      std::cout << "invalid line rho: '" << line << "'" << std::endl;
    } else {
      if (!wb_utils::string_to_int(fields[1], theta_index)) {
        std::cout << "invalid line theta_index: '" << line << "'" << std::endl;
      } else {
        int rho_index = hough->hough_accum->rho_to_index(rho);
        Polar_line polar_line(rho_index,
                              rho,
                              theta_index,
                              hough->hough_accum->get_cos(theta_index),
                              hough->hough_accum->get_sin(theta_index),
                              0);
        Line_segment line_segment;
        if (!hough->hough_accum->clip_window(line_segment, polar_line)) {
          errors.add("Operator_hough_draw_line::run", "", "failed clipping (rho, theta_index) against image: "+line);
        } else {
          in_image->draw_line_segment(line_segment, 255);
        }
      }
    }
  }
  in_image->write_jpeg(image_filename+"output.jpg", errors);
  errors.check_exit("image-hough");
}
