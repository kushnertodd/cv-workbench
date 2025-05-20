#include <iostream>
// #include <memory>
// #include "errors.hpp"
#include "image.hpp"
#include "one_pass_mean.hpp"
// #include "wb_filename.hpp"
// #include "wb_utils.hpp"

bool debug = false;

int main(int argc, char **argv) {
    /*
      if (argc < 2)
        wb_utils::error_exit("usage: image-mean in-filename");
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
    */
    int ncols = 4;
    int nrows = 4;
    int window_ncols = 3;
    int window_nrows = 3;
    Image *test_image = new Image(ncols, nrows, 1, Image_depth::CV_32F);
    Image *output_image = new Image(ncols, nrows, 1, Image_depth::CV_32F);
    for (int col = 0; col < ncols; col++) {
        for (int row = 0; row < nrows; row++) {
            test_image->set(col, row, row * ncols + col);
        }
    }
    One_pass_mean opm(test_image, window_nrows, window_ncols);
    for (int col = 0; col <= ncols - window_ncols; col++) {
        for (int row = 0; row <= nrows - window_nrows; row++) {
            output_image->set(col + opm.get_col_delta(), row + opm.get_row_delta(), opm.get_mean());
            opm.col_right();
        }
        opm.row_down();
    }
    std::cout << "test image: " << std::endl << std::endl;
    std::cout << test_image->to_string() << std::endl;
    std::cout << std::endl;
    std::cout << "mean image: " << std::endl << std::endl;
    std::cout << output_image->to_string() << std::endl;
    Errors errors;
    test_image->write_text("image-mean-test.txt", "\t", errors);
    errors.check_exit("test image text write failed");
    output_image->write_text("image-mean-out.txt", "\t", errors);
    errors.check_exit("output image text write failed");
}
