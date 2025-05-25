#include <iostream>
#include <memory>
#include "errors.hpp"
#include "image.hpp"
#include "wb_filename.hpp"
#include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
    if (argc < 2)
        wb_utils::error_exit("usage: image-read filename");
    std::string filename = argv[1];
    Errors errors;
    std::unique_ptr<Wb_filename> wb_filename(Wb_filename::create_wb_filename(filename, errors));
    std::string in_filename = wb_filename->to_text();
    Image *input_image = Image::read_text(in_filename, errors);
    errors.check_exit("unable to read " + in_filename);
    std::string out_filename = wb_filename->to_bin();
    input_image->write(out_filename, errors);
    errors.check_exit("unable to write " + out_filename);
}
