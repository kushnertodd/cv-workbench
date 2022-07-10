#include <cstdio>
#include <cstdlib>
#include <iostream>
//#include <sstream>
#include "hough_accum.hpp"

//

enum CV_image_depth {
  CV_8U,
  CV_8S,
  CV_16U,
  CV_16S,
  CV_32S,
  CV_32F,
  CV_64F,
  CV_16F,
  UNDEFINED_IMAGE_DEPTH
};
std::string depth_to_string( CV_image_depth depth) {
  if (depth == CV_8U) return "CV_8U";
  else if (depth == CV_32S) return "CV_32S";
  else if (depth == CV_32F) return "CV_32F";
  else return "invalid depth";
}

typedef unsigned char pixel_8U;
typedef int pixel_32S;
typedef float pixel_32F;

void error_exit(std::string message) {
  printf("%s\n", message.c_str());
  exit(0);
}

void read_int(FILE *fp, std::string name, int &var) {
  int cols;
  int newLen = fread(&var, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    error_exit("Image_header::read_header: missing value " + name);
  }
}

bool debug = true;

int main(int argc, char **argv) {

  if (argc < 2)
    error_exit("usage: image-dump filename");
  std::string filename = argv[1];

  FILE *fp = fopen(filename.c_str(), "r");
  if (fp == NULL) {
    error_exit("cannot open file '" + filename + "'");
  }

  int rows;
  read_int(fp, "rows", rows);
  int cols;
  read_int(fp, "cols", cols);
  int components;
  read_int(fp, "components", components);
  int depth;
  read_int(fp, "depth", depth);

  int npixels = rows * cols * components;
  std::cout << "rows " << rows << " cols " << cols << " components " << components << " depth "
       << depth_to_string(( CV_image_depth) depth)
       << " npixels " << npixels << std::endl;
  fclose(fp);
}


