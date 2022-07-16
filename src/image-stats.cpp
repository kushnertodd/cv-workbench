#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "variance_stats.hpp"
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
Variance_stats variance_stats;

void error_exit(std::string message) {
  printf("%s\n", message.c_str());
  exit(0);
}

void read_int(FILE *fp, std::string name, int &var) {
  int newLen = fread(&var, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    error_exit("Image_header::read_header: missing value " + name);
  }
}

void stat_8U(pixel_8U *buf_8U, int rows, int cols) {
  int pos = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      variance_stats.update(buf_8U[pos++]);
    }
  }
}

void stat_32S(pixel_32S *buf_32S, int rows, int cols) {
  int pos = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      variance_stats.update(buf_32S[pos++]);
    }
  }
}

void stat_32F(pixel_32F *buf_32F, int rows, int cols) {
  int pos = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      variance_stats.update(buf_32F[pos++]);
    }
  }
}

bool debug = true;


int main(int argc, char **argv) {

  if (argc < 2)
    error_exit("usage: image-stat filename");
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

  pixel_8U *buf_8U;
  pixel_32S *buf_32S;
  pixel_32F *buf_32F;
  int newLen;
  switch (depth) {
    case CV_8U:
      buf_8U = new pixel_8U[npixels];
      newLen = fread(buf_8U, sizeof(pixel_8U), npixels, fp);
      if (ferror(fp) != 0 || newLen != npixels) {
        error_exit("Image::read: cannot read 8U image data in '" + filename + "'");
      }
      stat_8U(buf_8U, rows, cols);
      break;

    case CV_32S:
      buf_32S = new pixel_32S[npixels];
      newLen = fread(buf_32S, sizeof(pixel_32S), npixels, fp);
      printf("ferror(fp) %d newLen %d sizeof(pixel_32S) %d npixels %d\n",
             ferror(fp),
             newLen,
             sizeof(pixel_32S),
             npixels);
      if (ferror(fp) != 0 || newLen != npixels) {
        error_exit("Image::read: cannot read 32S image data in '" + filename + "'");
      }
      stat_32S(buf_32S, rows, cols);
      break;

    case CV_32F:
      buf_32F = new pixel_32F[npixels];
      newLen = fread(buf_32F, sizeof(pixel_32F), npixels, fp);
      printf("ferror(fp) %d newLen %d sizeof(pixel_32F) %d npixels %d\n",
             ferror(fp),
             newLen,
             sizeof(pixel_32F),
             npixels);
      if (ferror(fp) != 0 || newLen != npixels) {
        error_exit("Image::read: cannot read 32F image data in '" + filename + "'");
      }
      stat_32F(buf_32F, rows, cols);
      break;

    default:
      break;
  }
  fclose(fp);
  std::cout << variance_stats.to_string();
}


