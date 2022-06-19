#include <cstdio>
#include <cstdlib>
#include <iostream>
//#include <sstream>

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
string depth_to_string(Cv_image_depth_enum depth) {
  if (depth == CV_8U) return "CV_8U";
  else if (depth == CV_32S) return "CV_8U";
  else if (depth == CV_32F) return "CV_8U";
else return "invalid depth";
}

typedef unsigned char pixel_8U;
typedef int pixel_32S;
typedef float pixel_32F;

void error_exit(string message) {
  printf("%s\n", message.c_str());
  exit(0);
}

void read_int(FILE *fp, string name, int& var) {
  int cols;
  int newLen = fread(&var, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    error_exit("Image_header::read_header: missing value " + name);
  }
}

bool debug = true;
int main(int argc, char** argv) {

  if (argc < 2)
    error_exit("usage: image-dump filename");
  string filename = argv[1];

 /*
  *            rows            cols            components      depth
  * 0000000    0002    0000    0002    0000    0001    0000    0000    0000
  *         stx nul nul nul stx nul nul nul soh nul nul nul nul nul nul nul
  * 0000020    6574    7473
  *           t   e   s   t
  */

  FILE *fp = fopen(filename.c_str(), "r");
  if (fp == NULL) {
    error_exit("cannot open file '"+filename+"'");
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
  cout << "rows " << rows << " cols " << cols << " components " << components << " depth " 
       << depth_to_string((Cv_image_depth_enum) depth)
       << " npixels " << npixels << endl;

  pixel_8U *buf_8U;
  pixel_32S *buf_32S;
  pixel_32F *buf_32F;
  int newLen;
  switch (depth) {
  case CV_8U:
    buf_8U = new pixel_8U[npixels];
    newLen = fread(buf_8U, sizeof(pixel_8U), npixels, fp);
      printf("ferror(fp) %d newLen %d sizeof(pixel_8U) %d npixels %d\n", ferror(fp), newLen, sizeof(pixel_8U), npixels);
    if (ferror(fp) != 0 || newLen != sizeof(pixel_8U) * npixels) {
      error_exit("Image::read_binary: cannot read 8U image data in '" + filename + "'");
    }
    for (int i = 0; i < newLen; i++) 
      printf("0x%02x ", buf_8U[i]);
    printf("\n");
      for (int i = 0; i < newLen; i++)
        printf("%4d ", buf_8U[i]);
      printf("\n");
      for (int i = 0; i < newLen; i++)
        printf(" '%-1c' ", buf_8U[i]);
      printf("\n");
    break;

  case CV_32S:
    buf_32S = new pixel_32S[npixels];
    newLen = fread(buf_32S, sizeof(pixel_32S), npixels, fp);
      printf("ferror(fp) %d newLen %d sizeof(pixel_32S) %d npixels %d\n", ferror(fp), newLen, sizeof(pixel_32S), npixels);
    if (ferror(fp) != 0 || newLen != npixels) {
      error_exit("Image::read_binary: cannot read 32S image data in '" + filename + "'");
    }
    for (int i = 0; i < newLen; i++) 
      printf("%8d ", buf_32S[i]);
    printf("\n");
    break;

  case CV_32F:
    buf_32F = new pixel_32F[npixels];
    newLen = fread(buf_32F, sizeof(pixel_32F), npixels, fp);
      printf("ferror(fp) %d newLen %d sizeof(pixel_32F) %d npixels %d\n", ferror(fp), newLen, sizeof(pixel_32F), npixels);
    if (ferror(fp) != 0 || newLen != npixels) {
      error_exit("Image::read_binary: cannot read 32F image data in '" + filename + "'");
    }
    for (int i = 0; i < newLen; i++) 
      printf("%8.2f ", buf_32F[i]);
    printf("\n");
    break;

  default:
    break;
  }
  fclose(fp);

}


