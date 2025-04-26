//
// Created by kushn on 7/5/2022.
//

#include "line_segment.hpp"
#include <iostream>
#include <sstream>

extern bool debug;

Line_segment::Line_segment() = default;
Line_segment::Line_segment(const Point &m_point1, const Point &m_point2) : point1(m_point1), point2(m_point2) {}

void Line_segment::init(const Point &m_point1, const Point &m_point2) {
    point1 = m_point1;
    point2 = m_point2;
}
std::string Line_segment::to_string() const {
    std::ostringstream os;
    os << "point1 (" << point1.to_string() << ") point2 (" << point2.to_string() << ")";
    return os.str();
}
