//
// Created by kushn on 7/5/2022.
//

#ifndef SRC__LINE_SEGMENT_HPP_
#define SRC__LINE_SEGMENT_HPP_

#include <iterator>
#include <list>
#include "point.hpp"
#include "wb_log.hpp"

/**
 * Image line segment
 */
 typedef std::list<Point>::iterator Point_iterator;
class Line_segment {
 private:
  Point point1;
  Point point2;
  std::list<Point> line_points;
 public:
  Line_segment();
  Line_segment(int min_row, int min_col, int max_row, int max_col);
  Line_segment(const Point &m_point1, const Point &m_point2);
  void add(int low, int high);
  void add(const Point &point);
  inline Point_iterator begin() { return line_points.begin(); }
  inline void clear() { line_points.clear(); }
  inline Point_iterator end() { return line_points.end(); }
  void log(std::list<WB_log_entry> &log_entries) const;
  inline int line_length() { return line_points.size();}
  void plotLineLow(int x0, int y0, int x1, int y1);
  void plotLineHigh(int x0, int y0, int x1, int y1);
  void plotLine();
  void set(const Point &m_point1, const Point &m_point2);
  std::string to_string() const;
};

#endif //SRC__LINE_SEGMENT_HPP_
