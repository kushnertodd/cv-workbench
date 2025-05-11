#include "point.hpp"
#include <cmath>
#include <sstream>

/**
 * @brief
 */
Point::Point() = default;
/**
 * @brief
 * @param m_x
 * @param m_y
 */
Point::Point(double m_x, double m_y) : x(m_x), y(m_y) {}
/**
 * @brief
 * @param point
 */
Point::Point(const Point &point) : Point::Point(point.x, point.y) {}
/**
 * @brief
 * @param point
 * @return
 */
bool Point::close(const Point &point) const { return distance(point) <= close_distance; }
/**
 * @brief
 * @param point
 */
void Point::copy(const Point &point) { init(point.x, point.y); }
/**
 * @brief
 * @param point
 * @return
 */
double Point::distance(const Point &point) const {
    double dx = x - point.x;
    double dy = x - point.y;
    return sqrt(dx * dx + dy * dy);
}
double Point::get_x() const { return x; }
double Point::get_y() const { return y; }
/**
 * @brief
 * @param m_x
 * @param m_y
 */
void Point::init(double m_x, double m_y) {
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
