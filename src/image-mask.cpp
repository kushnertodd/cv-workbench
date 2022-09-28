#include <memory>
#include "errors.hpp"
#include "kernel.hpp"
#include "wb_filename.hpp"
#include "wb_utils.hpp"

bool debug = false;

/**
 * This is a program to copy a sub-image of an image to a new file.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  if (argc < 11)
    wb_utils::error_exit(
        "usage: image-mask out-filename rows cols theta-degrees height width-left value-left width-center value-center width-right value-right");
  int rows;
  int cols;
  int theta_degrees;
  int height;
  int width_left;
  double value_left;
  int width_center;
  double value_center;
  int width_right;
  double value_right;
  int ct=1;
  std::string out_filename = argv[ct++];
  if (!wb_utils::string_to_int(argv[ct++], rows))
    wb_utils::error_exit("invalid rows");
  if (!wb_utils::string_to_int(argv[ct++], cols))
    wb_utils::error_exit("invalid cols");
  if (!wb_utils::string_to_int(argv[ct++], theta_degrees))
    wb_utils::error_exit("invalid theta-degrees");
  if (!wb_utils::string_to_int(argv[ct++], height))
    wb_utils::error_exit("invalid height");
  if (!wb_utils::string_to_int(argv[ct++], width_left))
    wb_utils::error_exit("invalid width-left");
  if (!wb_utils::string_to_double(argv[ct++], value_left))
    wb_utils::error_exit("invalid value-left");
  if (!wb_utils::string_to_int(argv[ct++], width_center))
    wb_utils::error_exit("invalid width-center");
  if (!wb_utils::string_to_double(argv[ct++], value_center))
    wb_utils::error_exit("invalid value-center");
  if (!wb_utils::string_to_int(argv[ct++], width_right))
    wb_utils::error_exit("invalid width-right");
  if (!wb_utils::string_to_double(argv[ct++], value_right))
    wb_utils::error_exit("invalid value-right");

  Kernel *mask = Kernel::create_linear_mask(
      rows,
      cols,
      theta_degrees,
      height,
      width_left,
      value_left,
      width_center,
      value_center,
      width_right,
      value_right);
  Errors errors;
  std::unique_ptr<WB_filename> wb_out_filename(WB_filename::create_wb_filename(out_filename, errors));
  errors.check_exit("invalid out-filename");
  mask->write_text(out_filename, "\t", errors);
  errors.check_exit(out_filename + " kernel write failed");
}
