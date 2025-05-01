#include "line_segment.hpp"
#include <iostream>
#include <sstream>

extern bool debug;
/**
 * @brief
 */
Line_segment::Line_segment() = default;
/**
 * @brief
 * @param m_point1
 * @param m_point2
 */
Line_segment::Line_segment(const Point &m_point1, const Point &m_point2) :
    Line_segment(m_point1.col, m_point1.row, m_point2.col, m_point1.row) {}
/**
 * @brief
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 */
Line_segment::Line_segment(const double x1, double y1, double x2, double y2) {
    point1.init(x1, y1);
    point2.init(x2, y2);
    init(point1, point2);
}
/**
 * @brief
 * @param m_point1
 * @param m_point2
 */
void Line_segment::init(const Point &m_point1, const Point &m_point2) {
    point1 = m_point1;
    point2 = m_point2;
}
/**
 * @brief
 * @param log_entries
 */
void Line_segment::log(std::list<WB_log_entry> &log_entries) const {
    WB_log_entry log_entry_start_y("start y", wb_utils::int_to_string(point1.y));
    log_entries.push_back(log_entry_start_y);
    WB_log_entry log_entry_start_x("start x", wb_utils::int_to_string(point1.x));
    log_entries.push_back(log_entry_start_x);
    WB_log_entry log_entry_end_y("end y", wb_utils::int_to_string(point2.y));
    log_entries.push_back(log_entry_end_y);
    WB_log_entry log_entry_end_x("end x", wb_utils::int_to_string(point2.x));
    log_entries.push_back(log_entry_end_x);
}
/**
 * @brief
 * @return
 */
std::string Line_segment::to_string() const {
    std::ostringstream os;
    os << "point1 (" << point1.to_string() << ") point2 (" << point2.to_string() << ")";
    return os.str();
}
