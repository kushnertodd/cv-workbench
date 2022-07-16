#include <cstdio>
#include <cstdlib>
#include <fstream>      // std::ofstream
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

std::string hist_filename;
std::string hist_diff_filename;

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

void write_gp_script(std::string filename) {
  std::string script_filename = filename + ".hist.gp";
  std::ofstream ofs (script_filename, std::ofstream::out);
  ofs << "set style data histograms" << std::endl;
  ofs << "plot './"<<hist_filename<<"' using 2:xtic(1)" << std::endl;
  ofs << "pause -1 \"Hit any key to continue\"" << std::endl;
  ofs.close();
  std::string script_diff_filename = filename + ".hist-diff.gp";
  std::ofstream ofs_diff (script_diff_filename, std::ofstream::out);
  ofs_diff << "set style data histograms" << std::endl;
  ofs_diff << "plot './"<<hist_diff_filename<<"' using 2:xtic(1)" << std::endl;
  ofs_diff << "pause -1 \"Hit any key to continue\"" << std::endl;
  ofs_diff.close();
}

void stat_8U(pixel_8U *buf_8U, int rows, int cols) {
  int pos = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      variance_stats.update(buf_8U[pos++]);
    }
  }
  int min_value = variance_stats.bounds.min_value;
  int max_value = variance_stats.bounds.max_value;
  int hist_len = max_value + 1 - min_value;
  int* histogram = new int[hist_len];
  for (int i = 0; i < hist_len; i++) histogram[i] = 0;
  pos = 0;
  //cout << "data: " << std::endl;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      //cout << (int) buf_8U[pos] << std::endl;
      histogram[buf_8U[pos++] - min_value]++;
    }
  }
  //cout << "end data: " << std::endl;
  //cout << "histogram: " << std::endl;
  std::ofstream ofs (hist_filename, std::ofstream::out);
  for (int i = 0; i < hist_len; i++)  {
    ofs << i + min_value << " " << histogram[i] << std::endl;
  }
  ofs.close();
  //cout << "end histogram: " << std::endl;
  delete histogram;
}

const int nbins = 50;
void stat_32S(pixel_32S *buf_32S, int rows, int cols) {
  int pos = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      variance_stats.update(buf_32S[pos++]);
    }
  }
  int min_value = -30; //variance_stats.get_min_value();
  int max_value = 30; // variance_stats.get_max_value();
  //int hist_len = max_value + 1 - min_value;
  int hist_len = nbins;
  int* histogram = new int[hist_len];
  for (int i = 0; i < hist_len; i++) histogram[i] = 0;
  pos = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      //histogram[buf_32S[pos++] - min_value]++;
      float val = buf_32S[pos++];
      int bin = (val < min_value ? 0 : (val > max_value ? 99 : nbins * (val - min_value) / (max_value - min_value)));
      histogram[bin]++;
    }
  }
  std::ofstream ofs (hist_filename, std::ofstream::out);
  for (int i = 0; i < hist_len; i++)  {
    int val = min_value + i * (max_value - min_value) / nbins;
    ofs << val << " " << histogram[i] << std::endl;
  }
  ofs.close();
  int* histogram_diff = new int[hist_len];
  for (int i = 0; i < hist_len - 1; i++) histogram_diff[i] = histogram[i + 1] - histogram[i];
  histogram_diff[hist_len - 1] = 0;
  std::ofstream ofs_diff (hist_diff_filename, std::ofstream::out);
  for (int i = 0; i < hist_len; i++)  {
    int val = min_value + i * (max_value - min_value) / nbins;
    ofs_diff << val << " " << histogram_diff[i] << std::endl;
  }
  ofs_diff.close();
  delete histogram;
  delete histogram_diff;
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
  hist_filename = filename + ".hist.txt";
  hist_diff_filename = filename + ".hist-diff.txt";

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
  //     << depth_to_string(( CV_image_depth) depth)
  //     << " npixels " << npixels << std::endl;

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
    //printf("ferror(fp) %d newLen %d sizeof(pixel_32S) %d npixels %d\n",
    //       ferror(fp),
    //       newLen,
    //       sizeof(pixel_32S),
    //       npixels);
    if (ferror(fp) != 0 || newLen != npixels) {
      error_exit("Image::read: cannot read 32S image data in '" + filename + "'");
    }
    stat_32S(buf_32S, rows, cols);
    break;

  case CV_32F:
    buf_32F = new pixel_32F[npixels];
    newLen = fread(buf_32F, sizeof(pixel_32F), npixels, fp);
    //printf("ferror(fp) %d newLen %d sizeof(pixel_32F) %d npixels %d\n",
    //       ferror(fp),
    //       newLen,
    //       sizeof(pixel_32F),
    //       npixels);
    if (ferror(fp) != 0 || newLen != npixels) {
      error_exit("Image::read: cannot read 32F image data in '" + filename + "'");
    }
    stat_32F(buf_32F, rows, cols);
    break;

  default:
    break;
  }
  fclose(fp);
  write_gp_script(filename);
  //cout << variance_stats.to_string();
}


