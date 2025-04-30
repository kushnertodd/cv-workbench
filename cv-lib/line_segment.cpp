#include "line_segment.hpp"
#include <iostream>
#include <sstream>

extern bool debug;
/**
 * @brief
 */
Line_segment::Line_segment() = default;
Line_segment::Line_segment(const int col1, int row1, int col2, int row2) {
    pixel1.init(col1, row1);
    pixel2.init(col2, row2);
}
/**
 * @brief
 * @param m_point1
 * @param m_point2
 */
void Line_segment::init(const Point &m_point1, const Point &m_point2) {
    pixel1 = m_point1;
    pixel2 = m_point2;
}
/**
 * @brief
 * @return
 */
std::string Line_segment::to_string() const {
    std::ostringstream os;
    os << "point1 (" << pixel1.to_string() << ") point2 (" << pixel2.to_string() << ")";
    return os.str();
}
