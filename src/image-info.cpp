#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "errors.hpp"
#include "file_utils.hpp"
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
  if (is_jpeg) {
    Errors errors;
    Image *in_image = Image::read_jpeg(filename, errors);
    errors.check_exit("reading " + filename);
    rows = in_image->get_rows();
    cols = in_image->get_cols();
    components = in_image->get_components();
    depth = in_image->get_depth();
  } else {
    FILE *fp = fopen(filename.c_str(), "r");
    if (fp == NULL) {
      wb_utils::error_exit(filename + ": cannot open");
    }

    if (!file_utils::read_int(fp, rows))
      wb_utils::error_exit(filename + ": cannot read rows");
    if (!file_utils::read_int(fp, cols))
      wb_utils::error_exit(filename + ": cannot read cols");
    if (!file_utils::read_int(fp, components))
      wb_utils::error_exit(filename + ": cannot read components");
    if (!file_utils::read_int(fp, depth_int))
      wb_utils::error_exit(filename + ": cannot read depth");
    fclose(fp);
    depth = static_cast<cv_enums::CV_image_depth>(depth_int);
  }
  std::string depth_str = wb_utils::image_depth_enum_to_string(depth);

  npixels = rows * cols * components;
  std::cout << "image " << filename <<  ":" << std::endl;
  std::cout << "    rows       " << std::setw(20) << std::right << rows << std::endl;
  std::cout << "    cols       " << std::setw(20) << std::right << cols << std::endl;
  std::cout << "    components " << std::setw(20) << std::right << components << std::endl;
  std::cout << "    depth int  " << std::setw(20) << std::right << depth_int << std::endl;
  std::cout << "    depth      " << std::setw(20) << std::right << depth_str << std::endl;
  std::cout << "    npixels    " << std::setw(20) << std::right << npixels << std::endl;
  return 0;
}


