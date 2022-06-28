//
// Created by kushn on 6/27/2022.
//

#include "hough_accum.hpp"

Hough_accum::~Hough_accum() {
  dealloc_accum();
}

Hough_accum::Hough_accum(int m_rows, int m_cols) :
    rows(m_rows),
    cols(m_cols) {
  max_rhos = round(sqrt(rows * rows + cols * cols)) + rho_buffer;
  alloc_accum();
}

void Hough_accum::alloc_accum() {
  accum = new int *[hough_trig.nthetas];
  for (int i = 0; i < hough_trig.nthetas; i++) {
    accum[i] = new int[max_rhos];
    for (int j = 0; j < max_rhos; j++)
      accum[i][j] = 0;
  }
}

int Hough_accum::rho_to_index(int rho) {
  return rho + max_rhos / 2;
}

int Hough_accum::index_to_rho(int index) {
  return index - max_rhos / 2;
}

int Hough_accum::theta_rho_to_index(int theta, int rho) {
  return theta * max_rhos + rho;
}

void Hough_accum::assign_accum(int theta, int rho, int value) {
  accum[theta][rho + max_rhos / 2] += value;
}

void Hough_accum::dealloc_accum() {
  for (int i = 0; i < hough_trig.nthetas; i++)
    delete accum[i];
}

int Hough_accum::row_col_to_rho(int row, int col, int theta) {
  int x = col - cols / 2;
  int y = row - rows / 2;
  float cos = hough_trig.cos(theta);
  float sin = hough_trig.sin(theta);
  float rho = x * cos + y * sin;
  int rho_round = round(rho);
  return rho_round;
}

void Hough_accum::write(string filename, string delim) {
  ofstream ofs(filename, ofstream::out);
  int max_val = 0;
  if (!ofs)
    throw "Hough:write invalid filename '" + filename + "'";
  for (int rho = 0; rho < max_rhos; rho++)
    ofs << rho << delim;
  ofs << endl;
  for (int theta = 0; theta < hough_trig.nthetas; theta++) {
    ofs << hough_trig.index_to_deg(theta) << delim;
    for (int rho = 0; rho < max_rhos; rho++) {
      ofs << accum[theta][rho] << delim;
      int value = accum[theta][rho];
      max_val = max(max_val, value);
    }
    ofs << endl;
  }
  ofs.close();
}

void Hough_accum::read(string filename) {
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
