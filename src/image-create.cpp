#include <cstring>
#include <iostream>
#include "errors.hpp"
#include "image.hpp"
#include "wb_utils.hpp"
#include "wb_defs.hpp"
#include "file_utils.hpp"

using namespace std;

bool debug = true;

void error_exit(string message) {
  printf("%s\n", message.c_str());
  exit(0);
}

int main(int argc, char **argv) {

  if (argc < 5)
    error_exit("usage: image-dump image-file rows cols depth data-file");
  string data_file = argv[1];
  int rows;
  if (!Workbench_utils::string_to_int(string(argv[2]), rows))
    error_exit("invalid rows value: '" + string(argv[2]) + "'");
  int cols;
  if (!Workbench_utils::string_to_int(string(argv[3]), cols))
    error_exit("invalid cols value: '" + string(argv[3]) + "'");
  string depth_str = argv[4];
  Cv_image_depth_enum depth = Workbench_utils::string_to_image_depth_enum(depth_str);
  if (depth == UNDEFINED_IMAGE_DEPTH)
    error_exit("invalid depth value: '" + depth_str + "'");
  string image_file = argv[5];

//  FILE *fp_image = fopen(image_file.c_str(), "w");
//  if (fp_image == NULL) {
//    error_exit("cannot open image file '" + image_file + "'");
//  }

  string data = File_utils::read_file(data_file);
  vector<string> tokens = File_utils::string_split(data);
  Errors errors;

  if (depth == CV_8U) {
    Image *image_8U = new Image(rows, cols, 1, depth);
    vector<int> values;
    for (string token: tokens) {
      //cout << "token '" << token<< "'" << endl;
      int value;
      if (Workbench_utils::string_to_int(token, value))
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
//      cout << i << ": " << buf_8U[i] << endl;
    image_8U->add_8U(buf_8U, size, errors);
    image_8U->write_binary(image_file, errors);
  } else if (depth == CV_32S) {
    Image *image_32S = new Image(rows, cols, 1, depth);
    vector<int> values;
    for (string token: tokens) {
      int value;
      if (Workbench_utils::string_to_int(token, value))
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
    image_32S->write_binary(image_file, errors);
  } else if (depth == CV_32F) {
    Image *image_32F = new Image(rows, cols, 1, depth);
    vector<float> values;
    for (string token: tokens) {
      double value;
      if (Workbench_utils::string_to_real(token, value))
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
    image_32F->write_binary(image_file, errors);
  }

  if (errors.error_ct > 0) {
    cout << "image_test.test_write(): there were errors." << endl << errors.toString();
  }
}

