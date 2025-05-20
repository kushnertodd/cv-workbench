#include <memory>
#include "errors.hpp"
#include "image.hpp"
#include "wb_filename.hpp"
#include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
    if (argc < 6)
        wb_utils::error_exit("usage: image-map in_filename out-filename lower-in upper-in lower-out upper-out");
    std::string in_filename = argv[1];
    std::string out_filename = argv[2];
    std::string lower_in_str = argv[3];
    std::string upper_in_str = argv[4];
    std::string lower_out_str = argv[5];
    std::string upper_out_str = argv[6];
    Errors errors;
    double lower_in;
    double upper_in;
    double lower_out;
    double upper_out;
    if (!wb_utils::string_to_double(lower_in_str, lower_in))
        errors.add("", "", "invalid lower_in: " + lower_in_str);
    if (!wb_utils::string_to_double(upper_in_str, upper_in))
        errors.add("", "", "invalid lower_in: " + upper_in_str);
    if (!wb_utils::string_to_double(lower_out_str, lower_out))
        errors.add("", "", "invalid lower_in: " + lower_out_str);
    if (!wb_utils::string_to_double(upper_out_str, upper_out))
        errors.add("", "", "invalid lower_in: " + upper_out_str);
    errors.check_exit("invalid arguments");
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
        errors.add("", "", in_filename + " image read failed");
    }
    errors.check_exit("invalid filename");
    if (input_image != nullptr) {
        Image *output_image =
                Image::scale_image(input_image, lower_in, upper_in, lower_out, upper_out, input_image->get_depth());
        errors.check_exit("image scale failed");
        if (wb_out_filename->is_jpeg()) {
            output_image->write_jpeg(out_filename, errors);
        } else if (wb_out_filename->is_bin()) {
            output_image->write(out_filename, errors);
        } else {
            errors.add("", "", "invalid out-filename");
        }
        errors.add("", "", out_filename + " image write failed");
    }
}
