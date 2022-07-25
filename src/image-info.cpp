#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
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
  wb_utils::string_find(filename, prefix, suffix, ".jpg", found, at_beginning, at_end);
  bool is_jpeg = at_end;

  int rows;
  int cols;
  int components;
  int depth_int;
  cv_enums::CV_image_depth depth;
  int npixels;
  Errors errors;
  Image *image;
  if (is_jpeg) {
    image = Image::read_jpeg(filename, errors);
    errors.check_exit("reading " + filename);
  } else {
    Image *image = Image::read(filename, errors);
  }
  Histogram *histogram;
  if (errors.error_ct == 0) {
    rows = image->get_rows();
    cols = image->get_cols();
    components = image->get_components();
    depth = image->get_depth();
    std::string depth_str = wb_utils::image_depth_enum_to_string(depth);
    npixels = image->get_npixels();
    std::cout << "image " << filename << ":" << std::endl;
    std::cout << "    rows       " << std::setw(20) << std::right << rows << std::endl;
    std::cout << "    cols       " << std::setw(20) << std::right << cols << std::endl;
    std::cout << "    components " << std::setw(20) << std::right << components << std::endl;
    std::cout << "    depth      " << std::setw(20) << std::right << depth_str << std::endl;
    std::cout << "    npixels    " << std::setw(20) << std::right << npixels << std::endl;
    histogram = Histogram::create_image(image,
                                        100,
                                        0.0,
                                        0.0,
                                        false,
                                        false);
    histogram->write_text("hist.txt", "\t", errors);
  }
  if (errors.error_ct == 0) {
    Histogram::write_gp_script("hist.txt");
  }
  if (errors.error_ct != 0)
    std::cout << errors.to_string() << std::endl;
}


