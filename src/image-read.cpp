#include <iostream>
#include <memory>
#include "errors.hpp"
#include "image.hpp"
#include "wb_filename.hpp"
#include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
  if (argc < 3)
    wb_utils::error_exit("usage: image-read in-text-filename out-image-filename");
  std::string in_filename = argv[1];
  std::string out_filename = argv[2];
  Errors errors;
  Image *image = Image::read_text(in_filename, errors);
  errors.check_exit("unable to read " + in_filename);
  std::unique_ptr<Wb_filename> wb_filename(Wb_filename::create_wb_filename(out_filename, errors));
  errors.check_exit("invalid out-image-filename " + out_filename);
  if (wb_filename->is_jpeg()) {
    image->write_jpeg(wb_filename->to_jpeg(), errors);
  } else if (wb_filename->is_bin()) {
    image->write(wb_filename->to_bin(), errors);
  } else {
    errors.add("", "", "invalid extension: " + out_filename);
  }
  errors.check_exit("unable to write " + out_filename);
}


