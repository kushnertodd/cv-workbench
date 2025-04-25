//
// Created by kushn on 7/5/2022.
//

#include <sstream>
#include <iostream>
#include "wb_utils.hpp"
#include "line_segment.hpp"

extern bool debug;

Line_segment::Line_segment() : Line_segment(0, 0, 0, 0) {
}

Line_segment::Line_segment(int min_row, int min_col, int max_row, int max_col) :
    point1(min_row, min_col),
    point2(max_row, max_col) {
  if (debug)
    std::cout << "Line_segment::Line_segment min_row " << min_row
              << " min_col " << min_col << " max_row " << max_row
              << " max_col " << max_col << std::endl;
  plotLine();
}

Line_segment::Line_segment(const Point &m_point1, const Point &m_point2) :
    point1(m_point1),
    point2(m_point2) {
  if (debug)
    std::cout << "Line_segment::Line_segment point1 (" <<
              point1.to_string()
              << ") point2 ("
              << point2.to_string() << ")" << std::endl;
  plotLine();
}

void Line_segment::add(int x, int y) {
  Point pixel(y, x);
  add(pixel);
}

void Line_segment::add(const Point &pixel) {
  line_points.push_back(pixel);
}

void Line_segment::log(std::list<WB_log_entry> &log_entries) const {
  WB_log_entry log_entry_start_row("start row", wb_utils::int_to_string(point1.row));
  log_entries.push_back(log_entry_start_row);
  WB_log_entry log_entry_start_col("start col", wb_utils::int_to_string(point1.col));
  log_entries.push_back(log_entry_start_col);
  WB_log_entry log_entry_end_row("end row", wb_utils::int_to_string(point2.row));
  log_entries.push_back(log_entry_end_row);
  WB_log_entry log_entry_end_col("end col", wb_utils::int_to_string(point2.col));
  log_entries.push_back(log_entry_end_col);
}

/**
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 * This fills in line segment points with Bresenham's line algorithm
 */

void Line_segment::plotLineLow(int x0, int y0, int x1, int y1) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }
  int D = (2 * dy) - dx;
  int y = y0;

  for (int x = x0; x <= x1; x++) {
    add(x, y);
    if (D > 0) {
      y = y + yi;
      D = D + (2 * (dy - dx));
    } else {
      D = D + 2 * dy;
    }
  }
}

void Line_segment::plotLineHigh(int x0, int y0, int x1, int y1) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }
  int D = (2 * dx) - dy;
  int x = x0;
  for (int y = y0; y <= y1; y++) {
    add(x, y);
    if (D > 0) {
      x = x + xi;
      D = D + (2 * (dx - dy));
    } else {
      D = D + 2 * dx;
    }
  }
}

void Line_segment::plotLine() {
  int x0 = point1.col;
  int y0 = point1.row;
  int x1 = point2.col;
  int y1 = point2.row;
  if (abs(y1 - y0) < abs(x1 - x0)) {
    if (x0 > x1) {
      plotLineLow(x1, y1, x0, y0);
    } else {
      plotLineLow(x0, y0, x1, y1);
    }
  } else {
    if (y0 > y1) {
      plotLineHigh(x1, y1, x0, y0);
    } else {
      plotLineHigh(x0, y0, x1, y1);
    }
  }
}

void Line_segment::set(const Point &m_point1, const Point &m_point2) {
  point1 = m_point1;
  point2 = m_point2;
  plotLine();
}

std::string Line_segment::to_string() const {
  std::ostringstream os;
  os << "pixel 1 " << point1.to_string()
     << " pixel 2 " << point2.to_string();
  return os.str();
}


