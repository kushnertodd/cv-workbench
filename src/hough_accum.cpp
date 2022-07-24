//
// Created by kushn on 6/27/2022.
//

#include <cassert>
#include <iostream>
#include "image.hpp"
#include "polar_line.hpp"
#include "hough_accum.hpp"
#include "line_segment.hpp"

extern bool debug;

Hough_accum::~Hough_accum() {
  delete[] hough_cos;
  delete[] hough_sin;
  delete rho_theta_counts;
}

Hough_accum::Hough_accum() = default;

Hough_accum::Hough_accum(int m_theta_inc, int m_nrhos, int m_rows, int m_cols) :
    theta_inc(m_theta_inc),
    nrhos(m_nrhos),
    nthetas(max_theta / theta_inc),
    nbins(nrhos * nthetas),
    rows(m_rows),
    cols(m_cols) {

  // allocate cosine table
  hough_cos = new double[nthetas];
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    hough_cos[theta_index] = std::cos(deg_to_rad(theta_index_to_theta(theta_index)));
  }

  // allocate sine table
  hough_sin = new double[nthetas];
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    hough_sin[theta_index] = std::sin(deg_to_rad(theta_index_to_theta(theta_index)));
  }

  // accumulator
  rho_theta_counts = new int[nbins];
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < nrhos; rho_index++)
      set(rho_index, theta_index, 0);
  }
}

int Hough_accum::choose_threshold(cv_enums::CV_threshold_type threshold_type) const {
  if (threshold_type == cv_enums::CV_threshold_type::FIXED) {
    return 40000; //bounds.max_value * 0.55; //0.90;
  } else if (threshold_type == cv_enums::CV_threshold_type::PERCENTAGE) {
    return wb_utils::round_double_to_int(stats.bounds.max_value * 0.85);
  } else return -1;
}

/**
 * Clips a polar line against a window and returns a line segment from the endpoints
 * There are two main cases based on the angle of the line, because there is a potential
 * singularity clipping the other way:
 *
 * - case 1: 0 < theta < pi/4 and 3*pi/4 < theta < pi
 *   must clip against the window top and bottom first
 *
 *   In case 1, there are 7 subcases where clip points are to the left, inside,
 *   or to the right of the window:
 *
 *  1.1  1.2    1.3 1.4 1.5    1.6 1.7
 *   |   \       /  |   \       /  |
 * ..+....+..+==+===+====+==+..+...+..
 *   |     \ I /    |     \ I /    |
 *   |      \I/     |      \I/     |
 *   |       +      |       +      |
 *   |      /I\     |      /I\     |
 *   |     / I \    |     / I \    |
 * ..+....+..+==+===+====+==+..+...+..
 *   |   /      \   |   /       \  |
 *
 *   This shows the position of the clip point in each subcase:
 *   case          1.1  1.2    1.3    1.4    1.5    1.6   1.7
 *   upper point  left left   inside inside inside right right
 *   lower point  left inside left   inside right inside right
 *
 *   This shows the intersection points that make up the resulting line segment, or none:
 *   case          1.1  1.2    1.3    1.4    1.5    1.6   1.7
 *   first point   none left   top    top    top   right none
 *   second point  none bottom left   bottom right bottom none
 *
 * - case 2: pi/4 < theta < 3*pi/4
 *   must clip against the window left and right first
 *
 *   In case 2, there are 7 subcases where clip points are above, inside,
 *   or below the window:
 *
 *      .     .
 * 2.1 -+-----+-
 * 2.2 \.     ./
 *      +     +
 *      .\   /.
 *      +==+==+
 *      I/   \I
 *      +     +
 * 2.3 /I     I\
 * 2.4 -+-----+-
 * 2.5 \I     I/
 *      +     +
 *      I\   /I
 *      +==+==+
 *      ./   \.
 *      +     + 
 * 2.6 /.     .\
 * 2.7 -+-----+-
 *      .     .
 *
 *   This shows the position of the clip point in each subcase:
 *   case          2.1   2.2    2.3     2.4    2.5    2.6    2.7
 *   upper point  above above  inside  inside inside below  below
 *   lower point  above inside above   inside below  inside below
 *
 *   This shows the intersection points that make up the resulting line segment, or none:
 *   case          2.1  2.2    2.3    2.4    2.5    2.6   2.7
 *   first point   none top    left   left   left   bottom none
 *   second point  none right  top    right  bottom right  none
 *
 * @param line Polar line to clip against window
 * @return line segment of endpoint on the window, or nullptr if none -- the latter won't occur for Hough lines
 */
bool Hough_accum::clip_window(Line_segment &line_segment, Polar_line &line) const {
  if (debug)
    std::cout << "Hough_accum::clip_window line (" << line.to_string() << ")" << std::endl;
  int theta_lower = nthetas / 4;
  int theta_upper = nthetas * 3 / 4;
  // window is in (row, col) coordinates
  int window_left = 0;
  int window_right = get_cols() - 1;
  int window_top = 0;
  int window_bottom = get_rows() - 1;
  if (debug)
    std::cout << "Hough_accum::clip_window"
              << " window_left " << window_left
              << " window_right " << window_right
              << " window_top " << window_top
              << " window_bottom " << window_bottom
              << std::endl;
  if (line.theta_index <= theta_lower || line.theta_index > theta_upper) {
    // case 1: 0 < theta < pi/4 or 3*pi/4 < theta < pi
    // must clip against the window top and bottom first
    int col_at_window_top = rho_theta_row_to_col(line.rho_index, line.theta_index, window_top);
    int col_at_window_bottom = rho_theta_row_to_col(line.rho_index, line.theta_index, window_bottom);
    // get the top or right point
    Point top_point;
    Point bottom_point;
    if (debug)
      std::cout << "Hough_accum::clip_window"
                << " col_at_window_top " << col_at_window_top
                << " col_at_window_bottom " << col_at_window_bottom
                << std::endl;
    if (col_at_window_top < window_left
        && col_at_window_bottom < window_left) {
      // case 1.1: window top and bottom column both to the left of window
      // clipped line invalid -- should not happen with Hough
      if (debug)
        std::cout << "Hough_accum::clip_window case 1.1"
                  << std::endl;
      return false;
    } else if (col_at_window_top < window_left
        && col_at_window_bottom >= window_left
        && col_at_window_bottom <= window_right) {
      // case 1.2: window top column to the left of the window and bottom column inside window
      int row_at_window_left = rho_theta_col_to_row(line.rho_index, line.theta_index, window_left);
      if (debug)
        std::cout << "Hough_accum::clip_window case 1.2"
                  << " row_at_window_left " << row_at_window_left
                  << std::endl;
      top_point.set(row_at_window_left, window_left);
      bottom_point.set(window_bottom, col_at_window_bottom);
    } else if (col_at_window_top >= window_left
        && col_at_window_top <= window_right
        && col_at_window_bottom < window_left) {
      // case 1.3: window top column inside of the window and bottom column to the left of the window
      int row_at_window_left = rho_theta_col_to_row(line.rho_index, line.theta_index, window_left);
      if (debug)
        std::cout << "Hough_accum::clip_window case 1.3"
                  << " row_at_window_left " << row_at_window_left
                  << std::endl;
      top_point.set(window_top, col_at_window_top);
      bottom_point.set(row_at_window_left, window_left);
    } else if (col_at_window_top >= window_left && col_at_window_top <= window_right
        && col_at_window_bottom >= window_left && col_at_window_bottom <= window_right) {
      // case 1.4: window top and bottom columns inside of the window
      if (debug)
        std::cout << "Hough_accum::clip_window case 1.4"
                  << std::endl;
      top_point.set(window_top, col_at_window_top);
      bottom_point.set(window_bottom, col_at_window_bottom);
    } else if (col_at_window_top >= window_left
        && col_at_window_top <= window_right
        && col_at_window_bottom > window_right) {
      // case 1.5: window top column inside of the window and bottom column to the right of the window
      int row_at_window_right = rho_theta_col_to_row(line.rho_index, line.theta_index, window_right);
      if (debug)
        std::cout << "Hough_accum::clip_window case 1.5"
                  << " row_at_window_right " << row_at_window_right
                  << std::endl;
      top_point.set(window_top, col_at_window_top);
      bottom_point.set(row_at_window_right, window_right);
    } else if (col_at_window_top > window_right
        && col_at_window_bottom >= window_left
        && col_at_window_bottom <= window_right) {
      // case 1.6: window top column to the right of the window and bottom column inside of the window
      int row_at_window_right = rho_theta_col_to_row(line.rho_index, line.theta_index, window_right);
      if (debug)
        std::cout << "Hough_accum::clip_window case 1.7"
                  << " row_at_window_right " << row_at_window_right
                  << std::endl;
      top_point.set(row_at_window_right, window_right);
      bottom_point.set(window_bottom, col_at_window_bottom);
    } else if (col_at_window_top > window_right
        && col_at_window_bottom > window_right) {
      // case 1.7: window top and bottom columns to the right of the window
      // clipped line invalid -- should not happen with Hough
      if (debug)
        std::cout << "Hough_accum::clip_window case 1.7"
                  << std::endl;
      return false;
    } else {
      if (debug)
        std::cout << "Hough_accum::clip_window case 1 shouldn't get here"
                  << std::endl;
      return false;
    }
    top_point.check_point_valid(get_rows(), get_cols());
    bottom_point.check_point_valid(get_rows(), get_cols());
    line_segment.set(top_point, bottom_point);
    return true;
  } else {
    // case 2:pi/4 < theta < 3*pi/4
    // must clip against the window left and right first
    int row_at_window_left = rho_theta_col_to_row(line.rho_index, line.theta_index, window_left);
    int row_at_window_right = rho_theta_col_to_row(line.rho_index, line.theta_index, window_right);
    // get the top or right point
    Point left_point;
    Point right_point;
    if (debug)
      std::cout << "Hough_accum::clip_window"
                << " row_at_window_left " << row_at_window_left
                << " row_at_window_right " << row_at_window_right
                << std::endl;
    if (row_at_window_left < window_top
        && row_at_window_right < window_top) {
      // case 2.1: window left and right row both above the window
      // clipped line invalid -- should not happen with Hough
      if (debug)
        std::cout << "Hough_accum::clip_window case 2.1"
                  << std::endl;
      return false;
    } else if (row_at_window_left < window_top
        && row_at_window_right >= window_top
        && row_at_window_right <= window_bottom) {
      // case 2.2: window left row above the window and right row inside window
      int col_at_window_top = rho_theta_row_to_col(line.rho_index, line.theta_index, window_top);
      if (debug)
        std::cout << "Hough_accum::clip_window case 2.2"
                  << " col_at_window_top " << col_at_window_top
                  << std::endl;
      left_point.set(window_top, col_at_window_top);
      right_point.set(row_at_window_right, window_right);
    } else if (row_at_window_left >= window_top
        && row_at_window_left <= window_bottom
        && row_at_window_right < window_top) {
      // case 2.3: window left row inside of the window and right row above the window
      int col_at_window_top = rho_theta_row_to_col(line.rho_index, line.theta_index, window_top);
      if (debug)
        std::cout << "Hough_accum::clip_window case 2.3"
                  << " col_at_window_top " << col_at_window_top
                  << std::endl;
      left_point.set(row_at_window_left, window_left);
      right_point.set(window_top, col_at_window_top);
    } else if (row_at_window_left >= window_top && row_at_window_left <= window_bottom
        && row_at_window_right >= window_top && row_at_window_right <= window_bottom) {
      // case 2.4: window left and right rows inside of the window
      if (debug)
        std::cout << "Hough_accum::clip_window case 2.4"
                  << std::endl;
      left_point.set(row_at_window_left, window_left);
      right_point.set(row_at_window_right, window_right);
    } else if (row_at_window_left >= window_top && row_at_window_left <= window_bottom
        && row_at_window_right > window_bottom) {
      // case 2.5: window left row inside of the window and right row above the window
      int col_at_window_bottom = rho_theta_row_to_col(line.rho_index, line.theta_index, window_bottom);
      if (debug)
        std::cout << "Hough_accum::clip_window case 2.5"
                  << " col_at_window_bottom " << col_at_window_bottom
                  << std::endl;
      left_point.set(row_at_window_left, window_left);
      right_point.set(col_at_window_bottom, window_bottom);
    } else if (row_at_window_left > window_bottom
        && row_at_window_right >= window_top
        && row_at_window_right <= window_bottom) {
      // case 2.6: window left row below the window and right row inside of the window
      int col_at_window_bottom = rho_theta_row_to_col(line.rho_index, line.theta_index, window_bottom);
      if (debug)
        std::cout << "Hough_accum::clip_window case 2.6"
                  << " col_at_window_bottom " << col_at_window_bottom
                  << std::endl;
      left_point.set(window_bottom, col_at_window_bottom);
      right_point.set(row_at_window_right, window_right);
    } else if (row_at_window_left > window_bottom
        && row_at_window_right > window_bottom) {
      // case 2.7: window left and right rows below the windoww
      // clipped line invalid -- should not happen with Hough
      if (debug)
        std::cout << "Hough_accum::clip_window case 2.7"
                  << std::endl;
      return false;
    } else {
      if (debug)
        std::cout << "Hough_accum::clip_window case 2"
                  << " shouldn't get here "
                  << std::endl;
      return false;
    }
    left_point.check_point_valid(get_rows(), get_cols());
    right_point.check_point_valid(get_rows(), get_cols());
    line_segment.set(left_point, right_point);
    return true;
  }
}

double Hough_accum::col_to_x(int col) const {
  double col_offset = get_cols() / 2.0;
  double x = col - col_offset;
  return x;
}

Hough_accum *Hough_accum::create_image(Image *image, int theta_inc, int pixel_threshold) {
  int rows = image->get_rows();
  int cols = image->get_cols();
  int nrhos = wb_utils::round_double_to_int(sqrt(rows * rows
                                                     + image->get_cols() * image->get_cols())) + rho_pad;
  auto *hough_accum = new Hough_accum(theta_inc, nrhos, rows, cols);
  hough_accum->initialize(image, pixel_threshold);
  return hough_accum;
}

double Hough_accum::deg_to_rad(int deg) {
  double rad = deg * M_PI / max_theta;
  return rad;
}

void Hough_accum::find_peaks(std::list<Polar_line> &lines, int peak_threshold,
                             bool non_max_suppression) const {
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < nrhos; rho_index++) {
      int count = get(rho_index, theta_index);
      if (count > peak_threshold) {
        if (!non_max_suppression) {
          Polar_line line(rho_index, rho_index_to_rho(rho_index), theta_index, get_cos(theta_index),
                          get_sin(theta_index), count);
          lines.push_back(line);
        }
      }
    }
  }
}

int Hough_accum::get(int rho_index, int theta_index) const {
  int index = rho_theta_to_index(rho_index, theta_index);
  return rho_theta_counts[index];
}

int Hough_accum::get_cols() const { return cols; }

double Hough_accum::get_cos(int theta_index) const { return hough_cos[theta_index]; }

int Hough_accum::get_rows() const { return rows; }

double Hough_accum::get_sin(int theta_index) const { return hough_sin[theta_index]; }

bool Hough_accum::in_window(Point &point) const {
  bool row_valid = point.row >= 0 && point.row < get_rows();
  bool col_valid = point.col >= 0 && point.col < get_cols();
  bool result = row_valid && col_valid;
  return result;
}

/**
 * initialize accumulator
 *
 * @param image_theshold
 */
void Hough_accum::initialize(Image *image, int image_theshold) {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      double value = std::abs(image->get(row, col));
      if (value > image_theshold) {
        for (int theta_index = 0; theta_index < nthetas; theta_index++) {
          int rho_index = row_col_theta_to_rho_index(row, col, theta_index);
          update(rho_index, theta_index, wb_utils::round_double_to_int(value));
        }
      }
    }
  }
  update_stats();
}

Hough_accum *Hough_accum::read(FILE *fp, const std::string &path, Errors &errors) {
  int theta_inc;
  int nrhos;
  int rows;
  int cols;
  int nbins;
  wb_utils::read_int(fp,
                     theta_inc,
                     "Hough_accum::read",
                     "",
                     "missing hough accumulator theta_inc in '" + path + "'",
                     errors);
  if (errors.error_ct == 0)
    wb_utils::read_int(fp, nrhos, "Hough_accum::read", "", "missing hough accumulator nrhos in '" + path + "'", errors);
  if (errors.error_ct == 0)
    wb_utils::read_int(fp, rows, "Hough_accum::read", "", "missing hough accumulator rows in '" + path + "'", errors);
  if (errors.error_ct == 0)
    wb_utils::read_int(fp, cols, "Hough_accum::read", "", "missing hough accumulator cols in '" + path + "'", errors);
  if (errors.error_ct != 0)
    return nullptr;
  else {
    auto *hough_accum = new Hough_accum(theta_inc, nrhos, rows, cols);
    wb_utils::read_int_buffer(fp,
                              hough_accum->rho_theta_counts,
                              hough_accum->nbins,
                              "Hough_accum::read",
                              "",
                              "cannot read hough accumulator data in '" + path + "'",
                              errors);
    if (errors.error_ct != 0) {
      delete hough_accum;
      return nullptr;
    }
    hough_accum->update_stats();
    return hough_accum;
  }
}

// NRFPT
Hough_accum *Hough_accum::read_text(std::ifstream &ifs, Errors &errors) {
  auto *hough_accum = new Hough_accum();
  std::string line;
  while (getline(ifs, line)) {
    std::vector<std::string> values = file_utils::string_split(line);
    for (const std::string &value_str: values) {
      int value;
      if (!wb_utils::string_to_int(value_str, value))
        errors.add("Hough_accum::read", "", "invalid value '" + value_str + "'");
      return nullptr;
    }
  }
  return hough_accum;
}

double Hough_accum::rho_index_to_rho(int rho_index) const {
  double rho_offset = nrhos / 2.0;
  double rho = rho_index - rho_offset;
  return rho;
}
// can have a singularity if theta ~= , 180, sin ~= 0
int Hough_accum::rho_theta_col_to_row(int rho_index, int theta_index, int col) const {
  double x = col_to_x(col);
  double cos_t = get_cos(theta_index);
  double rho = rho_index_to_rho(rho_index);
  double sin_t = get_sin(theta_index);
  double row_offset = get_rows() / 2.0;
  double row = (x * cos_t - rho) / sin_t + row_offset;
  return wb_utils::round_double_to_int(row);
}

// can have a singularity if theta ~= 90, cos ~= 0
int Hough_accum::rho_theta_row_to_col(int rho_index, int theta_index, int row) const {
  double rho = rho_index_to_rho(rho_index);
  double cos_t = get_cos(theta_index);
  double y = row_to_y(row);
  double sin_t = get_sin(theta_index);
  double col_offset = get_cols() / 2.0;
  double col = (rho - y * sin_t) / cos_t + col_offset;
  return wb_utils::round_double_to_int(col);
}

int Hough_accum::rho_theta_to_index(int rho_index, int theta_index) const {
  assert(rho_index >= 0 && rho_index < nrhos && theta_index >= 0 && theta_index < nthetas);
  return theta_index * nrhos + rho_index;
}

int Hough_accum::rho_to_index(double rho) const {
  double rho_offset = nrhos / 2.0;
  int rho_index = wb_utils::round_double_to_int(rho + rho_offset);
  return rho_index;
}

double Hough_accum::row_col_theta_to_rho(int row, int col, int theta_index) const {
  double x = col_to_x(col);
  double cos_t = get_cos(theta_index);
  double y = row_to_y(row);
  double sin_t = get_sin(theta_index);
  double rho = x * cos_t + y * sin_t;
  return rho;
}

int Hough_accum::row_col_theta_to_rho_index(int row, int col, int theta_index) const {
  double rho = row_col_theta_to_rho(row, col, theta_index);
  int rho_index = rho_to_index(rho);
  return rho_index;
}

double Hough_accum::row_to_y(int row) const {
  double row_offset = get_rows() / 2.0;
  double y = row_offset - row;
  return y;
}

void Hough_accum::set(int rho_index, int theta_index, int value) const {
  int index = rho_theta_to_index(rho_index, theta_index);
  rho_theta_counts[index] = value;
}

int Hough_accum::theta_index_to_theta(int theta_index) const {
  int theta = theta_index * theta_inc;
  return theta;
}

void Hough_accum::update(int rho_index, int theta_index, int value) const {
  int index = rho_theta_to_index(rho_index, theta_index);
  rho_theta_counts[index] += value;
}

void Hough_accum::update_stats() {
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < nrhos; rho_index++) {
      stats.update(get(rho_index, theta_index));
    }
  }
}

bool Hough_accum::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  for (int rho_index = 0; rho_index < nrhos; rho_index++)
    ofs << rho_index_to_rho(rho_index) << delim;
  ofs << std::endl;
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    ofs << theta_index_to_theta(theta_index) << delim;
    for (int rho_index = 0; rho_index < nrhos; rho_index++) {
      ofs << get(rho_index, theta_index) << delim;
    }
    ofs << std::endl;
  }
  return true;
}

int Hough_accum::x_to_col(double x) const {
  double col_offset = get_cols() / 2.0;
  int col = wb_utils::round_double_to_int(x + col_offset);
  return col;
}

int Hough_accum::y_to_row(double y) const {
  double row_offset = get_rows() / 2.0;
  int row = wb_utils::round_double_to_int(row_offset - y);
  return row;
}



