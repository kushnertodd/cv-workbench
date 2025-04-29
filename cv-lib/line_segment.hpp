#ifndef SRC__LINE_SEGMENT_HPP_
#define SRC__LINE_SEGMENT_HPP_

#include <list>
#include "pixel.hpp"
#include "point.hpp"
#include "wb_log.hpp"
/**
 * @brief
 */
class Line_segment {
    Point point1;
    Point point2;

public:
    Line_segment();
    Line_segment(const Point &m_point1, const Point &m_point2);
    void init(const Point &m_point1, const Point &m_point2);
    std::string to_string() const;
};

#endif // SRC__LINE_SEGMENT_HPP_
