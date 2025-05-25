#include <memory>
#include "errors.hpp"
#include "image.hpp"
#include "pearsons_correlation.hpp"
#include "wb_filename.hpp"
#include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
    if (argc < 4)
        wb_utils::error_exit("usage: image-corr in-image in-pattern out-image");
    std::string in_image_filename = argv[1];
    std::string in_pattern_filename = argv[2];
    std::string out_image_filename = argv[3];
    Errors errors;
    std::unique_ptr<Wb_filename> wb_in_image_filename(Wb_filename::create_wb_filename(in_image_filename, errors));
    errors.check_exit("invalid in-image");
    std::unique_ptr<Wb_filename> wb_in_pattern_filename(Wb_filename::create_wb_filename(in_pattern_filename, errors));
    errors.check_exit("invalid in-pattern");
    std::unique_ptr<Wb_filename> wb_out_image_filename(Wb_filename::create_wb_filename(out_image_filename, errors));
    errors.check_exit("invalid out-filename");
    Image *input_image = nullptr;
    if (wb_in_image_filename->is_jpeg()) {
        input_image = Image::read_jpeg(in_image_filename, errors);
    } else if (wb_in_image_filename->is_bin()) {
        input_image = Image::read(in_image_filename, errors);
    } else {
        errors.add("", "", "invalid in-image");
    }
    errors.check_exit("invalid in-image");
    Image *in_pattern = nullptr;
    if (wb_in_pattern_filename->is_jpeg()) {
        in_pattern = Image::read_jpeg(in_pattern_filename, errors);
    } else if (wb_in_pattern_filename->is_bin()) {
        in_pattern = Image::read(in_pattern_filename, errors);
    } else {
        errors.add("", "", "invalid in-pattern");
    }
    errors.check_exit("invalid in-pattern");
    if (input_image != nullptr && in_pattern != nullptr) {
        Pearsons_correlation pearsons_correlation(input_image, in_pattern);
        Image *output_image = pearsons_correlation.correlate();
        std::string out_image_bin_filename = wb_out_image_filename->to_bin();
        output_image->write(out_image_bin_filename, errors);
        errors.check_exit(out_image_bin_filename + " image write failed");
        std::string out_image_text_filename = wb_out_image_filename->to_text();
        output_image->write_text(out_image_text_filename, "\t", errors);
        errors.check_exit(out_image_text_filename + " image write failed");
    }
}
