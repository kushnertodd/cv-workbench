//#include <cmath>
#include <cstdio>
#include <cstdlib>
//#include <fstream>      // std::ofstream
#include <iostream>
#include <vector>
#include "variance_stats.hpp"
//#include "file_utils.hpp"
//#include "hough_theta.hpp"
#include "hough.hpp"
//#include "wb_utils.hpp"
#include "wb_defs.hpp"
#include "hough_trig.hpp"

using namespace std;


/*
string depth_to_string(Cv_image_depth_enum depth) {
  if (depth == CV_8U) return string("CV_8U");
  else if (depth == CV_32S) return string("CV_32S");
  else if (depth == CV_32F) return string("CV_32F");
  else return "invalid depth";
}
*/

Variance_stats variance_stats;

void error_exit(string message) {
  printf("%s\n", message.c_str());
  exit(0);
}

/*
void read_int(FILE *fp, string name, int &var) {
  int newLen = fread(&var, sizeof(int), 1, fp);
  if (ferror(fp) != 0 || newLen != 1) {
    error_exit("Image_header::read_header: missing value " + name);
  }
}
*/

/*
class Hough_class {
 public:
  string hough_filename;
  static const int theta_inc = 3;
  static const int nthetas = 180 / theta_inc;
  static const int rho_buffer = 10;
  int *accum[nthetas];
  int max_rhos;
  int rows;
  int cols;

  ~Hough_class() {
    dealloc_accum();
  }

  Hough_class(int m_rows, int m_cols) :
      rows(m_rows),
      cols(m_cols) {
    max_rhos = round(sqrt(rows * rows + cols * cols)) + rho_buffer;
    alloc_accum();
  }

  int index_to_theta_deg(int index) {
    return index * theta_inc;
  }

  float index_to_theta_cos(int index) {
    return hough_cos[index];
  }

  float index_to_theta_sin(int index) {
    return hough_sin[index];
  }

  void alloc_accum() {
    for (int i = 0; i < nthetas; i++) {
      accum[i] = new int[max_rhos];
      for (int j = 0; j < max_rhos; j++)
        accum[i][j] = 0;
    }
  }

  int rho_to_index(int rho) {
    return rho + max_rhos / 2;
  }

  int index_to_rho(int index) {
    return index - max_rhos / 2;
  }

  int theta_rho_to_index(int theta, int rho) {
    return theta * max_rhos + rho;
  }

  void assign_accum(int theta, int rho, int value) {
    accum[theta][rho + max_rhos / 2] += value;
  }

  void dealloc_accum() {
    for (int i = 0; i < nthetas; i++)
      delete accum[i];
  }

  int row_col_to_rho(int row, int col, int theta) {
    int x = col - cols / 2;
    int y = row - rows / 2;
    float cos = index_to_theta_cos(theta);
    float sin = index_to_theta_sin(theta);
    float rho = x * cos + y * sin;
    int rho_round = round(rho);
    return rho_round;
  }

  void write(string filename, string delim = "\t") {
    ofstream ofs(filename, ofstream::out);
    int max_val = 0;
    if (!ofs)
      throw "Hough:write invalid filename '" + filename + "'";
    for (int rho = 0; rho < max_rhos; rho++)
      ofs << rho << delim;
    ofs << endl;
    for (int theta = 0; theta < nthetas; theta++) {
      ofs << index_to_theta_deg(theta) << delim;
      for (int rho = 0; rho < max_rhos; rho++) {
        ofs << accum[theta][rho] << delim;
        int value = accum[theta][rho];
        max_val = max(max_val, value);
      }
      ofs << endl;
    }
    ofs.close();
  }

  void read(string filename) {
    ifstream ifs(filename, ofstream::in);
    if (!ifs)
      throw "Hough:read invalid filename '" + filename + "'";
    string line;
    while (getline(ifs, line)) {
      vector<string> values = File_utils::string_split(line);
      for (string value_str: values) {
        int value;
        if (!Workbench_utils::string_to_int(value_str, value))
          throw "Hough::read: invalid value '" + value_str + "'";
      }
    }
    ifs.close();
  }

};
*/

void stat_8U(pixel_8U *buf_8U, int rows, int cols) {
}

void stat_32S(pixel_32S *buf_32S, int rows, int cols, string filename) {
  Hough hough(rows, cols);
  int pos = 0;
/*
  int hist[2000];
  for (int i = 0; i < 2000; i++) hist[i] = 0;
  int min_val = INT32_MAX;
  int max_val = INT32_MIN;
  for (int i = 0; i < rows * cols; i++) {
    min_val = min(min_val, buf_32S[i]);
    max_val = max(max_val, buf_32S[i]);
  }
*/
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      int index = row * cols + col;
      int value = buf_32S[index];
      static const int min_value = -100;
      static const int max_value = 100;
      //hist[value - min_val]++;
      if (value < min_value || value > max_value) {
        for (int theta = 0; theta < hough_trig.nthetas; theta++) {
          hough.assign_accum(theta, hough.row_col_to_rho(row, col, theta),
                             abs(value));
        }
      }
    }
  }

/*
  ofstream o("hist.txt");
  for (int i = 0; i < 2000; i++) o << i << " " << hist[i] << endl;
  o.close();
*/
  string hough_filename = filename + ".hough.txt";
  hough.write(hough_filename);
}

void stat_32F(pixel_32F *buf_32F, int rows, int cols) {
}


Hough_trig hough_trig(3);
bool debug = true;
int main(int argc, char **argv) {

  if (argc < 2)
    error_exit("usage: image-hough filename");
  string filename = argv[1];

  FILE *fp = fopen(filename.c_str(), "r");
  if (fp == NULL) {
    error_exit("cannot open file '" + filename + "'");
  }

/*
  int rows;
  if (!File_utils::read_int(fp, rows))
    error_exit("missing image rows");
  int cols;
  if (!File_utils::read_int(fp, cols))
    error_exit("missing image cols");
  int components;
  if (!File_utils::read_int(fp, components))
    error_exit("missing image components");
  int depth;
  if (!File_utils::read_int(fp, depth))
    error_exit("missing image depth");
*/

  Errors errors;
  Image_header* image_header =
      Image_header::read_header(fp, filename, errors);
  if (image_header == nullptr) {
    error_exit(errors.to_string());
  }


  int rows = image_header->rows;
  int cols = image_header->cols;
  int components = image_header->components;
  int depth = image_header->depth;
    int npixels = rows * cols * components;

  pixel_32S *buf_32S;
  int newLen;
//  int hist[2000];
//  int min_val = INT32_MAX;
//  int max_val = INT32_MIN;
  switch (depth) {
    case CV_8U:
      break;

    case CV_32S:
      buf_32S = new pixel_32S[npixels];
      for (int i = 0; i < rows * cols; i++) buf_32S[i] = 0;
      newLen = fread(buf_32S, sizeof(pixel_32S), npixels, fp);
      if (ferror(fp) != 0 || newLen != npixels) {
        error_exit("Image::read_binary: cannot read 32S image data in '" + filename + "'");
      }

/*
      for (int i = 0; i < rows * cols; i++) {
        min_val = min(min_val, buf_32S[i]);
        max_val = max(max_val, buf_32S[i]);
      }
      for (int i = 0; i < rows * cols; i++) hist[buf_32S[i] - min_val]++;
*/
      stat_32S(buf_32S, rows, cols, filename);
      break;

    case CV_32F:
      break;

    default:
      break;
  }
  fclose(fp);
}