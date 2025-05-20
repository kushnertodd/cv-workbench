#include <memory>
#include "errors.hpp"
#include "image.hpp"
#include "wb_filename.hpp"
#include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
    if (argc < 3)
        wb_utils::error_exit("usage: image-copy in_filename out-filename");
    std::string in_filename = argv[1];
    std::string out_filename = argv[2];
    Errors errors;
    std::unique_ptr<Wb_filename> wb_in_filename(Wb_filename::create_wb_filename(in_filename, errors));
    errors.check_exit("invalid in-filename");
    std::unique_ptr<Wb_filename> wb_out_filename(Wb_filename::create_wb_filename(out_filename, errors));
    errors.check_exit("invalid out-filename");
    Image *input_image = nullptr;
    if (wb_in_filename->is_jpeg()) {
        input_image = Image::read_jpeg(in_filename, errors);
    } else if (wb_in_filename->is_bin()) {
        input_image = Image::read(in_filename, errors);
    } else {
        errors.add("", "", "invalid in-filename");
    }
    errors.check_exit("invalid filename");
    if (input_image != nullptr) {
        if (wb_out_filename->is_jpeg()) {
            input_image->write_jpeg(out_filename, errors);
        } else if (wb_out_filename->is_bin()) {
            input_image->write(out_filename, errors);
        } else {
            errors.add("", "", "invalid out-filename");
        }
        errors.add("", "", out_filename + " image write failed");
    }
}
