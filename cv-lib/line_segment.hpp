//
// Created by kushn on 7/5/2022.
//

#ifndef SRC__LINE_SEGMENT_HPP_
#define SRC__LINE_SEGMENT_HPP_

#include <list>
#include "pixel.hpp"
#include "wb_log.hpp"

class Line_segment {
 public:
  Pixel point1;
  Pixel point2;
  std::list<Pixel> line_points;
  Line_segment();
  Line_segment(int min_row, int min_col, int max_row, int max_col);
  Line_segment(const Pixel &m_point1, const Pixel &m_point2);
  void add(int low, int high);
  void add(const Pixel &pixel);
  void log(std::list<WB_log_entry> &log_entries) const;
  void plotLineLow(int x0, int y0, int x1, int y1);
  void plotLineHigh(int x0, int y0, int x1, int y1);
  void plotLine();
  void set(const Pixel &m_point1, const Pixel &m_point2);
  std::string to_string() const;
};

#endif //SRC__LINE_SEGMENT_HPP_
