#include <iostream>
//#include <memory>
//#include "errors.hpp"
#include "image.hpp"
#include "one_pass_mean.hpp"
//#include "wb_filename.hpp"
//#include "wb_utils.hpp"

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
  int rows = 4;
  int cols = 4;
  int window_rows = 3;
  int window_cols = 3;
  Image *test = new Image(rows, cols, 1, WB_image_depth::Image_depth::CV_32F);
  Image *out = new Image(rows, cols, 1, WB_image_depth::Image_depth::CV_32F);
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      test->set(row, col, row * cols + col);
    }
  }
  One_pass_mean opm(test, window_rows, window_cols);
  for (int row = 0; row <= rows - window_rows; row++) {
    for (int col = 0; col <= cols - window_cols; col++) {
      out->set(row + opm.row_delta, col + opm.col_delta, opm.get_mean());
      opm.col_right();
    }
    opm.row_down();
  }
  std::cout << "test image: " << std::endl << std::endl;
  std::cout << test->to_string() << std::endl;
  std::cout << std::endl;
  std::cout << "mean image: " << std::endl << std::endl;
  std::cout << out->to_string() << std::endl;
  Errors errors;
  test->write_text("image-mean-test.txt", "\t", errors);
  errors.check_exit("test image text write failed");
  out->write_text("image-mean-out.txt", "\t", errors);
  errors.check_exit("output image text write failed");
}


