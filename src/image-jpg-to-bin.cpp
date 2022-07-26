#include "image.hpp"
#include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
  if (argc < 2)
    wb_utils::error_exit("usage: image-jpg-to-bin filename");
  std::string filename_root = argv[1];
  std::string filename_jpg = filename_root + ".jpg";
  std::string filename_bin = filename_root + ".bin";
  Errors errors;
  Image *image = Image::read_jpeg(filename_jpg, errors);
  errors.check_exit("image-jpg-to-bin: cannot read jpg file");
  image->write(filename_bin, errors);
  errors.check_exit("image-jpg-to-bin: cannot write bin file");
}


