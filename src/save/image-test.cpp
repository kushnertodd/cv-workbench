#include <cstring>
#include <iostream>
#include "errors.hpp"
#include "image.hpp"

using namespace std;

bool debug = true;

void test_write() {
  Image *image = Image::create_image_allocated_buffer(2, 2, 1);
  memcpy(image->buf, "test", 4);
  Errors errors;
  image->write_binary("test-image.bin", errors);
  if (errors.error_ct > 0) {
    cout << "image_test.test_write(): there were errors." << endl << errors.to_string();
  }
  system("od -xa test-image.bin");
}

void test_read() {
  Errors errors;
  string binary_image_file = "test-image.bin";
  Image *binary_image = Image::read_binary(binary_image_file, errors);
  if (errors.error_ct > 0) {
    cout << "image_test.read_binary('" << binary_image_file << "'): there were errors." << endl << errors.to_string();
  } else {
    if (debug) {
      cout
          << "Image '" << binary_image_file << "'" << endl
          << "   rows " << binary_image->rows << endl
          << "   cols " << binary_image->cols << endl
          << "   components " << binary_image->components << endl
          << "   buf " << endl;
      for (int i = 0; i < binary_image->npixels; i++) {
        cout << "      " << i << ": '" << binary_image->buf[i] << "'" << endl;
      }
    }
  }

  string jpeg_image_file = "320x240gray.jpg";
  Image *jpeg_image = Image::read_jpeg(jpeg_image_file, errors);
  if (errors.error_ct > 0) {
    cout << "image_test.read_jpeg('" << jpeg_image_file << "'): there were errors." << endl << errors.to_string();
  } else {
    if (debug) {
      cout
          << "Image '" << jpeg_image_file << "'" << endl
          << "   rows " << jpeg_image->rows << endl
          << "   cols " << jpeg_image->cols << endl
          << "   components " << jpeg_image->components << endl
          << "   buf " << endl;
      //for (int i = 0; i < jpeg_image->npixels; i++) {
      for (int i = 0; i < 10; i++) {
        cout << "      " << i << ": '" << jpeg_image->buf[i] << "'" << endl;
      }
    }
  }

  string jpeg_image_file_out = "320x240gray_out.jpg";
  jpeg_image->write_jpeg(jpeg_image_file_out, errors);
  if (errors.error_ct > 0) {
    cout << "image_test.write_jpeg('" << jpeg_image_file_out << "'): there were errors." << endl << errors.to_string();
  }
}

int main() {
  cout << "test_write" << endl;
  test_write();
  cout << "test_read" << endl;
  test_read();
}
