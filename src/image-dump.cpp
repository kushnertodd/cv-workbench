#include <iostream>
#include "image.hpp"
#include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
  if (argc < 2)
    wb_utils::error_exit("usage: image-dump in_filename");
  std::string in_filename = argv[1];
  std::string prefix, suffix;
  bool found, at_beginning, at_end;
  wb_utils::string_find(in_filename, prefix, suffix, ".jpg", found, at_beginning, at_end);
  std::cout << "in_filename " << in_filename << std::endl<< " prefix " << prefix<< std::endl << " suffix " << suffix << std::endl;
  std::cout << "    " << (found ? "  " : "no") << " .jpg found" << std::endl;
  wb_utils::string_find(in_filename, prefix, suffix, ".bin", found, at_beginning, at_end);
  std::cout << "    " << (found ? "  " : "no") << " .bin found" << std::endl;

/*
  std::string in_filename_jpg = in_filename_root + ".jpg";
  std::string in_filename_txt = in_filename_root + ".txt";
  Errors errors;
  Image *image = Image::read_jpeg(in_filename_jpg, errors);
  errors.check_exit("image-jpg-to-txt: cannot read jpg file");
  image->write_text(in_filename_txt, errors);
  errors.check_exit("image-jpg-to-txt: cannot write txt file");
*/
}


