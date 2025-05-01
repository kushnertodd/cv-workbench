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
    Pixel pixel1;
    Pixel pixel2;

public:
    std::list<Pixel> line_pixels;
    Line_segment();
    Line_segment(const int col1, int row1, int col2, int row2);
    void init(const Point &m_point1, const Point &m_point2);
    std::string to_string() const;
};

#endif // SRC__LINE_SEGMENT_HPP_
