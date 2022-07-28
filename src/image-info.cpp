#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "cv_data_format.hpp"
#include "cv_data_type.hpp"
#include "cv_image_depth.hpp"
#include "cv_repository_type.hpp"
#include "errors.hpp"
#include "file_utils.hpp"
#include "histogram.hpp"
#include "image.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

//

bool debug = false;

int main(int argc, char **argv) {

  if (argc < 2)
    wb_utils::error_exit("usage: " + std::string(argv[0]) + " filename");
  std::string filename = argv[1];

  std::string prefix;
  std::string suffix;
  bool found;
  bool at_beginning;
  bool at_end;
  wb_utils::string_find(filename, prefix, suffix, ".jpg", at_beginning, at_end);
  bool is_jpeg = at_end;

  int rows;
  int cols;
  int components;
  int depth_int;
  CV_image_depth::Image_depth depth;
  int npixels;
  Errors errors;
  Image *image;
  if (is_jpeg) {
    image = Image::read_jpeg(filename, errors);
    errors.check_exit();
  } else {
    image = Image::read(filename, errors);
  }
  if (errors.error_ct == 0) {
    depth = image->get_depth();
    std::string depth_str = CV_image_depth::to_string(depth);
    Histogram *histogram = Histogram::create_image(image,
                                                   100,
                                                   0.0,
                                                   0.0,
                                                   false,
                                                   false);
    std::cout << "filename " << std::setw(20) << std::left << filename << std::endl;
    std::cout << image->to_string();
    std::cout << histogram->to_string();
    if (errors.error_ct != 0)
      std::cout << errors.to_string() << std::endl;
  }
}

