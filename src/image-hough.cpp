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
  if (argc < 4)
    error_exit("usage: image-hough image-filename hough-filename");
  std::string image_filename = argv[1];
  std::string hough_filename = argv[2];
  std::string hist_filename = argv[3];
  Errors errors;
  Image *in_image = Image::read(image_filename, errors);

  Hough* hough = Hough::create_image(in_image, 3, 200);
  Histogram *hist;
  Histogram *hist_image;
  Image *out_image;
  Variance_stats stats;
  in_image->get_stats(stats);
  switch (in_image->get_depth()) {
    case cv_enums::CV_8U:
      break;

    case cv_enums::CV_32S:
      //stat_32S(in_image, hough);
      hough->find_lines();
      out_image = Image::scale_image(in_image,
                                     stats.bounds.min_value,
                                     stats.bounds.min_value,
                                     pixel_8U_MIN,
                                     pixel_8U_MAX,
                                     cv_enums::CV_8U);
      if (debug)
        std::cout << "image-hough: out_image " << out_image->to_string() << std::endl;
      out_image->draw_line_segments(hough->line_segments, 0);
      hough->write_text(hough_filename, "\t", errors);
      out_image->write_jpeg(image_filename + ".jpg", errors);
/*
      hist = new Histogram(in_image, 100, hough->hough_accum->bounds.min_value, hough.hough_accum->bounds.max_value);
      for (int theta_index = 0; theta_index < hough.hough_accum->nthetas; theta_index++) {
        for (int rho_index = 0; rho_index < hough.hough_accum->nrhos; rho_index++) {
          hist->update(hough.hough_accum->rho_theta_counts[theta_index][rho_index]);
        }
      }
      hist->write_text(hist_filename, "\t", errors);
      delete hist;
      hist_image = new Histogram(in_image, 100, stats.bounds.min_value, stats.bounds.max_value);
      for (int i = 0; i < in_image->get_npixels(); i++)
        hist_image->update(in_image->buf_32S[i]);
      hist_image->write_text(hist_filename + "image.txt", "\t", errors);
*/
      break;

    case cv_enums::CV_32F:
      break;
  }
  errors.check_exit();
}