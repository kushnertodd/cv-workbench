#include <iomanip>
#include <iostream>
#include <memory>
#include "errors.hpp"
#include "histogram.hpp"

bool debug = false;

int main(int argc, char **argv) {

    if (argc < 2)
        wb_utils::error_exit("usage: image-info filename");

    std::string in_filename = argv[1];
    Errors errors;
    std::unique_ptr<Wb_filename> wb_filename(Wb_filename::create_wb_filename(in_filename, errors));
    errors.check_exit("invalid in-filename " + in_filename);
    Image *image = nullptr;
    if (wb_filename->is_jpeg()) {
        image = Image::read_jpeg(in_filename, errors);
    } else if (wb_filename->is_bin()) {
        image = Image::read(in_filename, errors);
    } else {
        errors.add("", "", "invalid filename ext " + in_filename);
    }
    errors.check_exit("read error filename " + in_filename);
    if (image != nullptr) {
        Histogram *histogram = Histogram::create_image(image, 100, 0.0, 0.0, false, false);
        std::cout << "filename " << std::setw(20) << std::left << in_filename << std::endl;
        std::cout << image->to_string();
        std::cout << histogram->to_string();
        if (errors.has_error())
            std::cout << errors.to_string() << std::endl;
    }
}
