#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>      // std::ofstream
#include <iostream>
#include "variance_stats.hpp"
#include "hough_theta.hpp"

using namespace std;

enum Cv_image_depth_enum {
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

string hist_filename;
string hist_diff_filename;

string depth_to_string(Cv_image_depth_enum depth) {
  if (depth == CV_8U) return "CV_8U";
  else if (depth == CV_32S) return "CV_32S";
  else if (depth == CV_32F) return "CV_32F";
  else return "invalid depth";
}

typedef unsigned char pixel_8U;
typedef int pixel_32S;
typedef float pixel_32F;
Variance_stats variance_stats;

void error_exit(string message) {
  printf("%s\n", message.c_str());
  exit(0);
}

void read_int(FILE *fp, string name, int &var) {
  int newLen = fread(&var, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    error_exit("Image_header::read_header: missing value " + name);
  }
}

void stat_8U(pixel_8U *buf_8U, int rows, int cols) {
}

const int nthetas = 60;
const int nrhos = 1000;
const int hough_size = nthetas * nrhos;

void stat_32S(pixel_32S *buf_32S, int rows, int cols) {
  int max_rho = sqrt(rows * rows + cols * cols) + 10;
  int min_value = -5;
  int max_value = 5;

  int *hough = new int[hough_size];
  for (int rho = 0; rho < nrhos; rho++)
    for (int theta = 0; theta < nthetas; theta++)
      hough[rho * nthetas + theta] = 0;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      for (int theta = 0; theta < nthetas; theta++) {
        int val = buf_32S[row * cols + col];
        if (val < min_value || val > max_value) {
          int rho = round(hough_cos[theta] * col + hough_sin[theta] * row);
          hough[rho * nthetas + theta]++;
        }
      }
    }
  }
  ofstream ofs(hist_filename, ofstream::out);
  for (int theta = 0; theta < nthetas; theta++) {
    for (int rho = 0; rho < nrhos; rho++) {
      ofs << hough[rho * nthetas + theta] << " ";
    }
    ofs << endl;
  }
  ofs.close();
}

void stat_32F(pixel_32F *buf_32F, int rows, int cols) {
}

bool debug = true;
int main(int argc, char **argv) {

  if (argc < 2)
    error_exit("usage: image-stat filename");
  string filename = argv[1];
  hist_filename = filename + ".hough.txt";

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
  //cout << "rows " << rows << " cols " << cols << " components " << components << " depth "
  //     << depth_to_string((Cv_image_depth_enum) depth)
  //     << " npixels " << npixels << endl;

  pixel_32S *buf_32S;
  int newLen;
  switch (depth) {
    case CV_8U:
      break;

    case CV_32S:
      buf_32S = new pixel_32S[npixels];
      newLen = fread(buf_32S, sizeof(pixel_32S), npixels, fp);
      //printf("ferror(fp) %d newLen %d sizeof(pixel_32S) %d npixels %d\n",
      //       ferror(fp),
      //       newLen,
      //       sizeof(pixel_32S),
      //       npixels);
      if (ferror(fp) != 0 || newLen != npixels) {
        error_exit("Image::read_binary: cannot read 32S image data in '" + filename + "'");
      }
      stat_32S(buf_32S, rows, cols);
      break;

    case CV_32F:
      break;

    default:
      break;
  }
  fclose(fp);
  //cout << variance_stats.to_string();
}


