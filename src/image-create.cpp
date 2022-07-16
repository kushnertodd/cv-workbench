#include <cstring>
#include <iostream>
#include "errors.hpp"
#include "image.hpp"
#include "wb_utils.hpp"
#include "wb_defs.hpp"
#include "file_utils.hpp"
#include "hough_accum.hpp"

//

bool debug = true;

void error_exit(std::string message) {
  printf("%s\n", message.c_str());
  exit(0);
}



int main(int argc, char **argv) {

  if (argc < 5)
    error_exit("usage: image-dump image-file rows cols depth data-file");
  std::string data_file = argv[1];
  int rows;
  if (!wb_utils::string_to_int(std::string(argv[2]), rows))
    error_exit("invalid rows value: '" + std::string(argv[2]) + "'");
  int cols;
  if (!wb_utils::string_to_int(std::string(argv[3]), cols))
    error_exit("invalid cols value: '" + std::string(argv[3]) + "'");
  std::string depth_str = argv[4];
  cv_enums::CV_image_depth depth = wb_utils::string_to_image_depth_enum(depth_str);
  if (depth == cv_enums::UNDEFINED_IMAGE_DEPTH)
    error_exit("invalid depth value: '" + depth_str + "'");
  std::string image_file = argv[5];

//  FILE *fp_image = fopen(image_file.c_str(), "w");
//  if (fp_image == NULL) {
//    error_exit("cannot open image file '" + image_file + "'");
//  }

  std::string data = file_utils::read_file(data_file);
  std::vector<std::string> tokens = file_utils::string_split(data);
  Errors errors;

  if (depth == cv_enums::CV_8U) {
    Image *image_8U = new Image(rows, cols, 1, depth);
    std::vector<int> values;
    for (std::string token: tokens) {
      //cout << "token '" << token<< "'" << std::endl;
      int value;
      if (wb_utils::string_to_int(token, value))
        values.push_back(value);
      else
        error_exit("invalid integer data value: '" + token + "'");
    }
    int size = values.size();
    pixel_8U buf_8U[size];
    int pos = 0;
    for (int value: values) {
      buf_8U[pos++] = value;
    }
//    for (int i = 0; i < size; i++)
//      cout << i << ": " << buf_8U[i] << std::endl;
    image_8U->add_8U(buf_8U, size, errors);
    image_8U->write(image_file, errors);
  } else if (depth == cv_enums::CV_32S) {
    Image *image_32S = new Image(rows, cols, 1, depth);
    std::vector<int> values;
    for (std::string token: tokens) {
      int value;
      if (wb_utils::string_to_int(token, value))
        values.push_back(value);
      else
        error_exit("invalid data value: '" + token + "'");
    }
    int size = values.size();
    pixel_32S buf_32S[size];
    int pos = 0;
    for (int value: values) {
      buf_32S[pos++] = value;
    }
    image_32S->add_32S(buf_32S, size, errors);
    image_32S->write(image_file, errors);
  } else if (depth == cv_enums::CV_32F) {
    Image *image_32F = new Image(rows, cols, 1, depth);
    std::vector<float> values;
    for (std::string token: tokens) {
      double value;
      if (wb_utils::string_to_real(token, value))
        values.push_back(value);
      else
        error_exit("invalid data value: '" + token + "'");
    }
    int size = values.size();
    pixel_32F buf_32F[size];
    int pos = 0;
    for (int value: values) {
      buf_32F[pos++] = value;
    }
    image_32F->add_32F(buf_32F, size, errors);
    image_32F->write(image_file, errors);
  }
  errors.check_exit("image_test.test_write(): there were errors.");
}

