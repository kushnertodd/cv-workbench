#include "point.hpp"
#include <sstream>

Point::Point() = default;
Point::Point(double m_x, double m_y) : x(m_x), y(m_y) {}
Point::Point(const Point &point) : Point::Point(point.x, point.y) {}
/**
 * @brief
 * @param m_x
 * @param m_y
 */
void Point::init(int m_x, int m_y) {
    x = m_x;
    y = m_y;
}
/**
 * @brief
 * @return
 */
std::string Point::to_string() const {
    std::ostringstream os;
    os << "x " << x << " y " << y;
    return os.str();
}
