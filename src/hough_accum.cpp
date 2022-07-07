//
// Created by kushn on 6/27/2022.
//

#include <iostream>
#include "image.hpp"
#include "polar_line.hpp"
#include "hough_accum.hpp"
#include "line_segment.hpp"

extern bool debug;

Hough_accum::~Hough_accum() {
  if (hough_cos != nullptr)
    delete[] hough_cos;
  if (hough_sin != nullptr)
    delete[] hough_sin;
  for (int theta_index = 0; theta_index < nthetas; theta_index++)
    if (accum[theta_index] != nullptr)
      delete accum[theta_index];
}

Hough_accum::Hough_accum(int m_theta_inc, Image *m_image) :
    theta_inc(m_theta_inc),
    image(m_image) {
  nthetas = max_theta / theta_inc;
  max_rho = round(sqrt(get_rows() * get_rows() + get_cols() * get_cols())) + rho_buffer;
  hough_cos = new float[nthetas];
  hough_sin = new float[nthetas];
  if (debug)
    std::cout << "Hough_accum::Hough_accum theta_inc " << theta_inc
              << " max_theta " << max_theta
              << " nthetas " << nthetas
              << " rows " << get_rows()
              << " cols " << get_cols()
              << " max_rho " << max_rho
              << std::endl;
  // allocate cosine table
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    hough_cos[theta_index] = std::cos(deg_to_rad(theta_index_to_theta(theta_index)));
  }

  // allocate sine table
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    hough_sin[theta_index] = std::sin(deg_to_rad(theta_index_to_theta(theta_index)));
  }

  // accumulator
  accum = new int *[nthetas];
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    accum[theta_index] = new int[max_rho];
    for (int j = 0; j < max_rho; j++)
      accum[theta_index][j] = 0;
  }
}

/**
 * initialize accumulator
 *
 * @param image_theshold
 */
void Hough_accum::initialize(int image_theshold) {
  for (int row = 0; row < image->image_header->rows; row++) {
    for (int col = 0; col < image->image_header->cols; col++) {
      float value = image->get(row, col);
      if (value < -image_theshold || value > image_theshold) {
        for (int theta_index = 0; theta_index < nthetas; theta_index++) {
          int rho_index = row_col_theta_to_rho_index(row, col, theta_index);
          if (debug && false)
            std::cout << "Hough_accum::Hough_accum: value " << value
                      << " image_theshold " << image_theshold
                      << " rho_index " << rho_index
                      << " theta_index " << theta_index
                      << " value " << value
                      << std::endl;
          add(theta_index, rho_index, abs(value));
        }
      }
    }
  }
  update_stats();
}

// accessors
int Hough_accum::get_cols() { return image->image_header->cols; }
int Hough_accum::get_rows() { return image->image_header->rows; }
bool Hough_accum::in_window(Point *point) {
  bool row_valid = point->row >= 0 && point->row < get_rows();
  bool col_valid = point->col >= 0 && point->col < get_cols();
  bool result = row_valid && col_valid;
  return result;
}

float Hough_accum::get_cos(int theta_index) { return hough_cos[theta_index]; }
float Hough_accum::get_sin(int theta_index) { return hough_sin[theta_index]; }
float Hough_accum::deg_to_rad(float deg) {
  float rad = deg * pi / max_theta;
  return rad;
}

float Hough_accum::col_to_x(int col) {
  float col_offset = get_cols() / 2.0;
  float x = col - col_offset;
  return x;
}
float Hough_accum::rho_index_to_rho(int rho_index) {
  float rho_offset = max_rho / 2.0;
  float rho = rho_index - rho_offset;
  return rho;
}
int Hough_accum::rho_theta_col_to_row(int rho_index, int theta_index, int col) {
  float x = col_to_x(col);
  float cos_t = get_cos(theta_index);
  float rho = rho_index_to_rho(rho_index);
  float sin_t = get_sin(theta_index);
  float row_offset = get_rows() / 2.0;
  float row = (x * cos_t - rho) / sin_t + row_offset;
  return round(row);
}
int Hough_accum::rho_theta_row_to_col(int rho_index, int theta_index, int row) {
  float rho = rho_index_to_rho(rho_index);
  float cos_t = get_cos(theta_index);
  float y = row_to_y(row);
  float sin_t = get_sin(theta_index);
  float col_offset = get_cols() / 2.0;
  float col = (rho - y * sin_t) / cos_t + col_offset;
  return round(col);
}
int Hough_accum::rho_to_index(float rho) {
  float rho_offset = max_rho / 2.0;
  int rho_index = round(rho);
  return rho_index;
}
float Hough_accum::row_col_theta_to_rho(int row, int col, int theta_index) {
  float x = col_to_x(col);
  float cos_t = get_cos(theta_index);
  float y = row_to_y(row);
  float sin_t = get_sin(theta_index);
  return x * cos_t + y * sin_t;
}
int Hough_accum::row_col_theta_to_rho_index(int row, int col, int theta_index) {
  float rho = row_col_theta_to_rho(row, col, theta_index);
  int rho_index = rho_to_index(rho);
  return rho_index;
}
float Hough_accum::row_to_y(int row) {
  float row_offset = get_rows() / 2.0;
  float y = row_offset - row;
  return y;
}
int Hough_accum::theta_index_to_theta(int theta_index) {
  int theta = theta_index * theta_inc;
  return theta;
}
int Hough_accum::x_to_col(float x) {
  float col_offset = get_cols() / 2.0;
  int col = round(x + col_offset);
  return col;
}
int Hough_accum::y_to_row(float y) {
  float row_offset = get_rows() / 2.0;
  int row = round(row_offset - y);
  return row;
}

void Hough_accum::add(int theta_index, int rho_index, int value) {
  accum[theta_index][rho_index] += value;
}

Line_segment *Hough_accum::clip_window(Polar_line *line) {
  if (debug)
    std::cout << "Hough_accum::clip_window line " << line->to_string() << std::endl;
  Line_segment *line_segment = nullptr;
  int theta_lower = nthetas / 4;
  int theta_upper = nthetas * 3 / 4;
  // theta < 45 || theta > 135
  if (line->theta_index < theta_lower || line->theta_index > theta_upper) {

    Point *point_left = new Point(0, rho_theta_row_to_col(line->rho_index,
                                                          line->theta_index,
                                                          0));
    Point *point_right = new Point(get_rows() - 1, rho_theta_row_to_col(line->rho_index,
                                                                        line->theta_index,
                                                                        get_rows() - 1));
    if (debug)
      std::cout << "Hough_accum::clip_window "
                << "point_left (" << point_left->to_string()
                << ") point_right (" << point_right->to_string()
                << ")" << std::endl;
    if (in_window(point_left) && in_window(point_right)) {
      line_segment = new Line_segment(point_left, point_right);
      line_segment->plotLine();
      std::cout << "Hough_accum::clip_window "
                << "line_segment (" << line_segment->to_string() << std::endl;
    }

  } else {
    // theta = 45..135
    Point *point_top = new Point(rho_theta_col_to_row(line->rho_index,
                                                      line->theta_index,
                                                      0), 0);
    Point *point_bottom = new Point(rho_theta_col_to_row(line->rho_index,
                                                         line->theta_index,
                                                         get_cols() - 1), get_cols() - 1);
    if (debug)
      std::cout << "Hough_accum::clip_window "
                << "point_top (" << point_top->to_string()
                << "point_bottom (" << point_bottom->to_string()
                << std::endl;
    if (in_window(point_top) && in_window(point_bottom)) {
      line_segment = new Line_segment(point_top, point_bottom);
      line_segment->plotLine();
      if (debug)
        std::cout << "Hough_accum::clip_window "
                  << "line_segment (" << line_segment->to_string() << std::endl;
    }

  }
  return line_segment;
}

int Hough_accum::choose_threshold(cv_enums::CV_threshold_type threshold_type) {
  if (threshold_type == cv_enums::CV_threshold_type::FIXED) {
    return bounds.max_value * 0.99;//0.40; // for all
  } else if (threshold_type == cv_enums::CV_threshold_type::PERCENTAGE) {
    return bounds.max_value * 0.85;
  } else return -1;
}

void Hough_accum::find_peaks(list<Polar_line *> &lines, int peak_threshold,
                             bool non_max_suppression) {
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < max_rho; rho_index++) {
      int count = accum[theta_index][rho_index];
      int rho = rho_index_to_rho(rho_index);
      if (count > peak_threshold) {
        if (!non_max_suppression) { //maximum(theta_index, rho_index)) {
          Polar_line *line = new Polar_line(rho_index, rho, theta_index, get_cos(theta_index),
                                            get_sin(theta_index), count);
          lines.push_back(line);
          if (debug) {
            cout << "Hough_accum::find_peaks: line " << line->to_string()
                 << endl;
          }
        }
      }
    }
  }
}

bool Hough_accum::maximum(int theta_index, int rho_index) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int check_rho = rho_index + i;
      if (check_rho >= 0 && check_rho < max_rho) {
        int check_theta = theta_index + j;
        if (check_theta >= 0 && check_theta < nthetas) {
          if (accum[check_theta][check_rho] > accum[theta_index][rho_index]) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

void Hough_accum::update_stats() {
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < max_rho; rho_index++) {
      bounds.update(accum[theta_index][rho_index]);
    }
  }
}

bool Hough_accum::read(ifstream &ifs, Errors &errors) {
  string line;
  while (getline(ifs, line)) {
    vector<string> values = File_utils::string_split(line);
    for (string value_str: values) {
      int value;
      if (!Workbench_utils::string_to_int(value_str, value))
        errors.add("Hough_accum::read: invalid value '" + value_str + "'");
      return false;
    }
  }
  return true;
}

bool Hough_accum::write(ofstream &ofs, string delim, Errors &errors) {
  ofs << "nthetas " << nthetas
      << " theta_inc " << theta_inc
      << " max_rho " << max_rho
      << " hough_cos " << hough_cos
      << " hough_sin " << hough_sin
      << bounds.to_string()
      << endl;
  ofs << delim;
  for (int rho = 0; rho < max_rho; rho++)
    ofs << rho_index_to_rho(rho) << delim;
  ofs << endl;
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    ofs << theta_index_to_theta(theta_index) << delim;
    for (int rho = 0; rho < max_rho; rho++) {
      ofs << accum[theta_index][rho] << delim;
    }
    ofs << endl;
  }
  return true;
}

