//
// Created by kushn on 7/5/2022.
//

#include <sstream>
#include <iostream>
#include "line_segment.hpp"

extern bool debug;

Line_segment::~Line_segment() {
  return;
  if (point1 != nullptr)
    delete point1;
  if (point2 != nullptr)
    delete point2;
  for (Point *point: line_points)
    if (point != nullptr)
      delete point;
}
Line_segment::Line_segment() {}

Line_segment::Line_segment(int min_row, int min_col, int max_row, int max_col) :
    point1(new Point(min_row, min_col)),
    point2(new Point(max_row, max_col)) {
  if (debug)
    std::cout << "Line_segment::Line_segment min_row " << min_row
              << " min_col " << min_col << " max_row " << max_row
              << " max_col " << max_col << std::endl;
  plotLine();
}

Line_segment::Line_segment(Point *point1, Point *point2) :
    point1(new Point(point1)),
    point2(new Point(point2)) {
  if (debug)
    std::cout << "Line_segment::Line_segment point1 (" <<
              point1->to_string()
              << ") point2 ("
              << point2->to_string() << ")" << std::endl;
  plotLine();
}

/**
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 * This fills in line segment points with Bresenham's line algorithm
 */
void Line_segment::add(int x, int y) {
  if (debug && false)
    std::cout << "Line_segment::add x " << x << " y " << y << std::endl;
  add(new Point(y, x));
}

void Line_segment::add(Point *point) {
  if (debug && false)
    std::cout << "Line_segment::add point (" << point->to_string() << ")" << std::endl;
  line_points.push_back(point);
}

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
  int x0 = point1->col;
  int y0 = point1->row;
  int x1 = point2->col;
  int y1 = point2->row;
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

std::string Line_segment::to_string() {
  std::ostringstream os;
  os << "point 1 " << point1->to_string()
     << " point 2 " << point2->to_string();
  return os.str();
}


