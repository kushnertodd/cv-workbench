#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "errors.hpp"
#include "hough.hpp"
#include "hough_accum.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"

Variance_stats variance_stats;

void error_exit(string message) {
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
    error_exit("usage: image-hough image-filename hough-filename");
  string image_filename = argv[1];
  string hough_filename = argv[2];
  Errors errors;
  Image *in_image = Image::read_binary(image_filename, errors);

  Hough hough(in_image, 3);

  Image  *out_image;
  switch (in_image->image_header->depth) {
    case cv_enums::CV_8U:
      break;

    case cv_enums::CV_32S:
      stat_32S(in_image, hough);
      hough.find_lines();
       out_image = Image::scale_image(in_image, -500,
                                255, 0,
                                255, cv_enums::CV_8U);
       if (debug)
         cout << "image-hough: out_image " << out_image->to_string() << endl;
    out_image->draw_line_segments(hough.line_segments, 255);
      hough.write(hough_filename, "\t", errors);
      out_image->write_jpeg(image_filename+".jpg", errors);
      break;

    case cv_enums::CV_32F:
      break;

    default:
      break;
  }
  if (errors.error_ct > 0)
    cout << errors.to_string() << endl;
}