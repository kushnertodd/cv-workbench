#include <iostream>
#include <memory>
#include "errors.hpp"
#include "image.hpp"
#include "wb_filename.hpp"
#include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
  if (argc < 2)
    wb_utils::error_exit("usage: image-dump in-filename");
  std::string in_filename = argv[1];
  Errors errors;
  std::unique_ptr<Wb_filename> wb_filename(Wb_filename::create_wb_filename(in_filename, errors));
  errors.check_exit("invalid in-filename");
  Image *image = nullptr;
  if (wb_filename->is_jpeg()) {
    image = Image::read_jpeg(in_filename, errors);
  } else if (wb_filename->is_bin()) {
    image = Image::read(in_filename, errors);
  } else {
    errors.add("", "", "invalid filename");
  }
  errors.check_exit("invalid filename");
  if (image != nullptr) {
    std::cout << image->to_string() << std::endl;
    std::string text_filename = wb_filename->to_text();
    image->write_text(text_filename, "\t", errors);
    errors.check_exit("image text write failed");
  }
}


