#include <cstring>
#include <iostream>
#include "errors.hpp"
#include "image.hpp"
#include "hough_accum.hpp"

//

bool debug = true;

int main(int argc, char **argv) {
  Errors errors;

  Image *image_8U = new Image(3, 2, 1, cv_enums::CV_8U);
  pixel_8U buf_8U[20];
  memcpy(buf_8U, "test..", 6);
  image_8U->add_8U(buf_8U, 6, errors);
  image_8U->write("image-test-8U.bin", errors);

  Image *image_32S = new Image(3, 2, 1, cv_enums::CV_32S);
  pixel_32S buf_32S[20];
  for (int i = 0; i < 6; i++)
    buf_32S[i] = i;
  image_32S->add_32S(buf_32S, 6, errors);
  image_32S->write("image-test-32S.bin", errors);

  Image *image_32F = new Image(3, 2, 1, cv_enums::CV_32F);
  pixel_32F buf_32F[20];
  for (int i = 0; i < 6; i++)
    buf_32F[i] = i;
  image_32F->add_32F(buf_32F, 6, errors);
  image_32F->write("image-test-32F.bin", errors);

  errors.check_exit("image_test.test_write(): there were errors.");

  printf("od -xa image-test-8U.bin\n");
  system("od -xa image-test-8U.bin");
  printf("od -xa image-test-32S.bin\n");
  system("od -xa image-test-32S.bin");
  printf("od -xa image-test-32F.bin\n");
  system("od -xa image-test-32F.bin");
  system("od -xa image-test-32F.bin");
  system("od -xa image-test-32F.bin");
}

