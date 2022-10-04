#include <memory>
#include "errors.hpp"
#include "image.hpp"
#include "linear_features.hpp"
#include "wb_filename.hpp"
#include "wb_utils.hpp"

bool debug = false;
/**
 * This is a program that performs the same function as the transform-intensity-map operator
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  if (argc < 5)
    wb_utils::error_exit("usage: image-map in_filename out-filename feature_length theta_degrees");
  std::string in_filename = argv[1];
  std::string out_filename = argv[2];
  std::string feature_length_str = argv[3];
  std::string theta_degrees_str = argv[4];
  Errors errors;
  int feature_length;
  int theta_degrees;
  errors.check_exit("invalid arguments");
  std::unique_ptr<WB_filename> wb_in_filename(WB_filename::create_wb_filename(in_filename, errors));
  errors.check_exit("invalid in-filename");
  std::unique_ptr<WB_filename> wb_out_filename(WB_filename::create_wb_filename(out_filename, errors));
  errors.check_exit("invalid out-filename");
  if (!wb_utils::string_to_int(feature_length_str, feature_length))
    wb_utils::error_exit("invalid feature_length");
  if (!wb_utils::string_to_int(theta_degrees_str, theta_degrees))
    wb_utils::error_exit("invalid theta_degrees");
  Image *in_image_ptr = nullptr;
  if (wb_in_filename->is_jpeg())
    in_image_ptr = Image::read_jpeg(in_filename, errors);
  else if (wb_in_filename->is_bin())
    in_image_ptr = Image::read(in_filename, errors);
  else
    errors.add("", "", in_filename + " image read failed");
  errors.check_exit("invalid filename");
  std::unique_ptr<Image> in_image(in_image_ptr);
  std::unique_ptr<Linear_features> linear_features(new Linear_features(in_image.get(),
                                                                          feature_length,
                                                                          theta_degrees));
  errors.check_exit("image scale failed");
  if (wb_out_filename->is_text()) {
    linear_features->get_features()->write_text(out_filename, "\t", errors);
  }else
    errors.add("", "", "invalid out-filename");
  errors.check_exit("image write failed");
}

