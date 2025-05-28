#ifndef SRC__LINE_SEGMENT_HPP_
#define SRC__LINE_SEGMENT_HPP_

#include <list>
#include "point.hpp"
#include "wb_log.hpp"
/**
 * @brief
 */
class Line_segment {
    friend class Image;
    Point point1;
    Point point2;

public:
    ~Line_segment();
    Line_segment();
    Line_segment(const Point &m_point1, const Point &m_point2);
    Line_segment(const double x1, double y1, double x2, double y2);
    void init(const Point &m_point1, const Point &m_point2);
    void log(std::list<WB_log_entry> &log_entries) const;
    std::string to_string() const;
};

#endif // SRC__LINE_SEGMENT_HPP_
