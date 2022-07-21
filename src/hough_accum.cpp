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
  for (int theta_index = 0; theta_index < nthetas; theta_index++)
    if (rho_theta_accum[theta_index] != nullptr)
      delete rho_theta_accum[theta_index];
}

Hough_accum::Hough_accum(int m_theta_inc, Image *m_image) :
    theta_inc(m_theta_inc),
    image(m_image) {
  nthetas = max_theta / theta_inc;
  max_rho = wb_utils::round_double_to_int(sqrt(get_rows() * get_rows() + get_cols() * get_cols())) + rho_buffer;
  hough_cos = new double[nthetas];
  hough_sin = new double[nthetas];
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
  rho_theta_accum = new int *[nthetas];
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    rho_theta_accum[theta_index] = new int[max_rho];
    for (int rho_index = 0; rho_index < max_rho; rho_index++)
      rho_theta_accum[theta_index][rho_index] = 0;
  }
}

void Hough_accum::add(int theta_index, int rho_index, int value) const {
  assert(theta_index >= 0 && theta_index < nthetas && rho_index >= 0 && rho_index < max_rho);
  rho_theta_accum[theta_index][rho_index] += value;
}

int Hough_accum::choose_threshold(cv_enums::CV_threshold_type threshold_type) const {
  if (threshold_type == cv_enums::CV_threshold_type::FIXED) {
    return 40000; //bounds.max_value * 0.55; //0.90;
  } else if (threshold_type == cv_enums::CV_threshold_type::PERCENTAGE) {
    return wb_utils::round_double_to_int(bounds.max_value * 0.85);
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

double Hough_accum::deg_to_rad(int deg) const {
  double rad = deg * pi / max_theta;
  return rad;
}

void Hough_accum::find_peaks(std::list<Polar_line> &lines, int peak_threshold,
                             bool non_max_suppression) const {
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < max_rho; rho_index++) {
      int count = rho_theta_accum[theta_index][rho_index];
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

int Hough_accum::get_cols() const { return image->image_header.cols; }

double Hough_accum::get_cos(int theta_index) const { return hough_cos[theta_index]; }

int Hough_accum::get_rows() const { return image->image_header.rows; }

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
void Hough_accum::initialize(int image_theshold) {
  for (int row = 0; row < image->get_rows(); row++) {
    for (int col = 0; col < image->get_cols(); col++) {
      double value = image->get(row, col);
      if (std::abs(value) > image_theshold) {
        for (int theta_index = 0; theta_index < nthetas; theta_index++) {
          int rho_index = row_col_theta_to_rho_index(row, col, theta_index);
          add(theta_index, rho_index, wb_utils::round_double_to_int(abs(value)));
        }
      }
    }
  }
  update_stats();
}

bool Hough_accum::read(std::ifstream &ifs, Errors &errors) {
  std::string line;
  while (getline(ifs, line)) {
    std::vector<std::string> values = file_utils::string_split(line);
    for (const std::string &value_str: values) {
      int value;
      if (!wb_utils::string_to_int(value_str, value))
        errors.add("Hough_accum::read", "", "invalid value '" + value_str + "'");
      return false;
    }
  }
  return true;
}

double Hough_accum::rho_index_to_rho(int rho_index) const {
  double rho_offset = max_rho / 2.0;
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

int Hough_accum::rho_to_index(double rho) const {
  double rho_offset = max_rho / 2.0;
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

int Hough_accum::theta_index_to_theta(int theta_index) const {
  int theta = theta_index * theta_inc;
  return theta;
}

void Hough_accum::update_stats() {
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    for (int rho_index = 0; rho_index < max_rho; rho_index++) {
      bounds.update(rho_theta_accum[theta_index][rho_index]);
    }
  }
}

bool Hough_accum::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  ofs << "nthetas " << nthetas << delim
      << " theta_inc " << theta_inc << delim
      << " max_rho " << max_rho << delim
      << bounds.to_string()
      << std::endl;
  ofs << delim;
  for (int rho_index = 0; rho_index < max_rho; rho_index++)
    ofs << rho_index_to_rho(rho_index) << delim;
  ofs << std::endl;
  for (int theta_index = 0; theta_index < nthetas; theta_index++) {
    ofs << theta_index_to_theta(theta_index) << delim;
    for (int rho_index = 0; rho_index < max_rho; rho_index++) {
      ofs << rho_theta_accum[theta_index][rho_index] << delim;
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



