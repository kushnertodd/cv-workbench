//
// Created by kushn on 6/11/2022.
//

#include <cmath>
#include <fstream>
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "hough_accum.hpp"
#include "hough_trig.hpp"
#include "hough.hpp"

using namespace std;

Hough::~Hough() {
  dealloc_accum();
}

Hough::Hough(int m_rows, int m_cols) :
    rows(m_rows),
    cols(m_cols) {
  accum = new Hough_accum(rows, cols);
  //max_rhos = round(sqrt(rows * rows + cols * cols)) + rho_buffer;
  //alloc_accum();
}

void Hough::alloc_accum() {
/*  for (int i = 0; i < nthetas; i++) {
    accum[i] = new int[max_rhos];
    for (int j = 0; j < max_rhos; j++)
      accum[i][j] = 0;
  }*/
}

int Hough::rho_to_index(int rho) {
  return rho + max_rhos / 2;
}

int Hough::index_to_rho(int index) {
  return index - max_rhos / 2;
}

int Hough::theta_rho_to_index(int theta, int rho) {
  return theta * max_rhos + rho;
}

void Hough::assign_accum(int theta, int rho, int value) {
//  accum[theta][rho + max_rhos / 2] += value;
}

void Hough::dealloc_accum() {
//  for (int i = 0; i < nthetas; i++)
//    delete accum[i];
}

int Hough::row_col_to_rho(int row, int col, int theta) {
  int x = col - cols / 2;
  int y = row - rows / 2;
  float cos = Hough_trig::cos(theta);
  float sin = Hough_trig::sin(theta);
  float rho = x * cos + y * sin;
  int rho_round = round(rho);
  return rho_round;
}

void Hough::write(string filename, string delim) {
  ofstream ofs(filename, ofstream::out);
  int max_val = 0;
  if (!ofs)
    throw "Hough:write invalid filename '" + filename + "'";
  for (int rho = 0; rho < max_rhos; rho++)
    ofs << rho << delim;
  ofs << endl;
  for (int theta = 0; theta < nthetas; theta++) {
    ofs << Hough_trig::index_to_deg(theta) << delim;
    for (int rho = 0; rho < max_rhos; rho++) {
//      ofs << accum[theta][rho] << delim;
//      int value = accum[theta][rho];
//      max_val = max(max_val, value);
    }
    ofs << endl;
  }
  ofs.close();
}

void Hough::read(string filename) {
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




