#include <memory>
#include "errors.hpp"
#include "image.hpp"
#include "morphology.hpp"
#include "wb_filename.hpp"
#include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
    if (argc < 4)
        wb_utils::error_exit("usage: image-morph in_filename nrows ncols thickness");
    std::string in_filename = argv[1];
    int nrows;
    if (!wb_utils::string_to_int(argv[2], nrows))
        wb_utils::error_exit("invalid nrows");
    int ncols;
    if (!wb_utils::string_to_int(argv[3], ncols))
        wb_utils::error_exit("invalid ncols");
    int thickness;
    if (!wb_utils::string_to_int(argv[4], thickness))
        wb_utils::error_exit("invalid thickness");

    Errors errors;
    std::unique_ptr<Wb_filename> wb_cross_filename(Wb_filename::create_wb_filename(in_filename, errors));
    errors.check_exit("invalid filename " + in_filename);
    wb_cross_filename->add_suffix(".cross");
    Kernel *cross_structuring_element = Morphology::create_structuring_element_cross(nrows, ncols, thickness);
    cross_structuring_element->write_text(wb_cross_filename->to_text(), "\t", errors);
    errors.check_exit("cross structuring element write failed");

    std::unique_ptr<Wb_filename> wb_rectangle_filename(Wb_filename::create_wb_filename(in_filename, errors));
    wb_rectangle_filename->add_suffix(".rectangle");
    Kernel *rectangle_structuring_element = Morphology::create_structuring_element_rectangle(nrows, ncols);
    rectangle_structuring_element->write_text(wb_rectangle_filename->to_text(), "\t", errors);
    errors.check_exit("rectangle structuring element write failed");

    std::unique_ptr<Wb_filename> wb_ellipse_filename(Wb_filename::create_wb_filename(in_filename, errors));
    wb_ellipse_filename->add_suffix(".ellipse");
    Kernel *ellipse_structuring_element = Morphology::create_structuring_element_ellipse(nrows, ncols);
    ellipse_structuring_element->write_text(wb_ellipse_filename->to_text(), "\t", errors);
    errors.check_exit("ellipse structuring element write failed");

    std::unique_ptr<Wb_filename> wb_in_filename(Wb_filename::create_wb_filename(in_filename, errors));
    errors.check_exit("invalid in-filename");
    Image *in_image = Image::read_jpeg(wb_in_filename->to_jpeg(), errors);
    errors.check_exit("cannot read in-filename");
    in_image->write_text(wb_in_filename->to_text(), "\t", errors);
    errors.check_exit("cannot write text in-filename");

    std::unique_ptr<Wb_filename> wb_dilate_filename(Wb_filename::create_wb_filename(in_filename, errors));
    wb_dilate_filename->add_suffix(".dilate");
    std::unique_ptr<Image> dilate_image(Morphology::dilate(
            in_image, WB_morphology_types::Structuring_element_type::CROSS, nrows, ncols, thickness, errors));
    dilate_image->write_text(wb_dilate_filename->to_text(), "\t", errors);
    errors.check_exit("dilate image text write failed");
    dilate_image->write_jpeg(wb_dilate_filename->to_jpeg(), errors);
    errors.check_exit("dilate image write failed");

    std::unique_ptr<Wb_filename> wb_erode_filename(Wb_filename::create_wb_filename(in_filename, errors));
    wb_erode_filename->add_suffix(".erode");
    std::unique_ptr<Image> erode_image(Morphology::erode(in_image, WB_morphology_types::Structuring_element_type::CROSS,
                                                         nrows, ncols, thickness, errors));
    erode_image->write_text(wb_erode_filename->to_text(), "\t", errors);
    errors.check_exit("erode image write text failed");
    erode_image->write_jpeg(wb_erode_filename->to_jpeg(), errors);
    errors.check_exit("erode image write failed");

    std::unique_ptr<Wb_filename> wb_black_hat_filename(Wb_filename::create_wb_filename(in_filename, errors));
    wb_black_hat_filename->add_suffix(".black_hat");
    std::unique_ptr<Image> black_hat_image(Morphology::black_hat(
            in_image, WB_morphology_types::Structuring_element_type::CROSS, nrows, ncols, thickness, errors));
    black_hat_image->write_text(wb_black_hat_filename->to_text(), "\t", errors);
    errors.check_exit("black hat image write text failed");
    black_hat_image->write_jpeg(wb_black_hat_filename->to_jpeg(), errors);
    errors.check_exit("black hat image write failed");

    std::unique_ptr<Wb_filename> wb_close_filename(Wb_filename::create_wb_filename(in_filename, errors));
    wb_close_filename->add_suffix(".close");
    std::unique_ptr<Image> close_image(Morphology::close(in_image, WB_morphology_types::Structuring_element_type::CROSS,
                                                         nrows, ncols, thickness, errors));
    close_image->write_text(wb_close_filename->to_text(), "\t", errors);
    errors.check_exit("close image write text failed");
    close_image->write_jpeg(wb_close_filename->to_jpeg(), errors);
    errors.check_exit("close image write failed");

    std::unique_ptr<Wb_filename> wb_gradient_filename(Wb_filename::create_wb_filename(in_filename, errors));
    wb_gradient_filename->add_suffix(".gradient");
    std::unique_ptr<Image> gradient_image(Morphology::gradient(
            in_image, WB_morphology_types::Structuring_element_type::CROSS, nrows, ncols, thickness, errors));
    gradient_image->write_text(wb_gradient_filename->to_text(), "\t", errors);
    errors.check_exit("gradient image text write failed");
    gradient_image->write_jpeg(wb_gradient_filename->to_jpeg(), errors);
    errors.check_exit("gradient image write failed");

    std::unique_ptr<Wb_filename> wb_open_filename(Wb_filename::create_wb_filename(in_filename, errors));
    wb_open_filename->add_suffix(".open");
    std::unique_ptr<Image> open_image(Morphology::open(in_image, WB_morphology_types::Structuring_element_type::CROSS,
                                                       nrows, ncols, thickness, errors));
    open_image->write_text(wb_open_filename->to_text(), "\t", errors);
    errors.check_exit("open image text write failed");
    open_image->write_jpeg(wb_open_filename->to_jpeg(), errors);
    errors.check_exit("open image write failed");

    std::unique_ptr<Wb_filename> wb_top_hat_filename(Wb_filename::create_wb_filename(in_filename, errors));
    wb_top_hat_filename->add_suffix(".top_hat");
    std::unique_ptr<Image> top_hat_image(Morphology::top_hat(
            in_image, WB_morphology_types::Structuring_element_type::CROSS, nrows, ncols, thickness, errors));
    top_hat_image->write_text(wb_top_hat_filename->to_text(), "\t", errors);
    errors.check_exit("top hat image text write failed");
    top_hat_image->write_jpeg(wb_top_hat_filename->to_jpeg(), errors);
    errors.check_exit("top hat image write failed");
}
