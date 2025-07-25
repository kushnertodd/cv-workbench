#include "wb_window.hpp"
#include <iostream>
#include <sstream>
#include "polar_trig.hpp"

extern bool debug;

/**
 * @brief
 * @param point_min
 * @param point_max
 */
WB_window::WB_window(Point &point_min, Point &point_max) :
    WB_window(point_min.x, point_min.y, point_max.x, point_max.y) {}
/**
 * @brief
 * @param m_min_x
 * @param m_min_y
 * @param m_max_x
 * @param m_max_y
 */
WB_window::WB_window(double m_min_x, double m_min_y, double m_max_x, double m_max_y) :
    min_x(m_min_x), min_y(m_min_y), max_x(m_max_x), max_y(m_max_y) {}
/**
 * @brief
 * @param point
 */
void WB_window::add(Point &point) {
    for (Point &list_point: intersections) {
        if (point.close(list_point))
            return;
    }
    intersections.push_back(point);
}
/**
 * Clips a polar line against a window and returns a line segment from the endpoints
 * @param line Polar line to clip against window
 * @return line segment of endpoint on the window, or nullptr if none -- the latter won't occur for Hough lines
 */
bool WB_window::clip_window(Polar_line &polar_line, Line_segment &line_segment) {
    // clip left: min_x
    if (!polar_line.singular_sin()) {
        double y_left = polar_line.x_to_y(min_x);
        if (Point left_point(min_x, y_left); inside(left_point))
            add(left_point);
    }
    // clip right: max_x
    if (!polar_line.singular_sin()) {
        double y_right = polar_line.x_to_y(max_x);
        Point right_point(max_x, y_right);
        if (inside(right_point))
            add(right_point);
    }
    // clip top: min_y
    if (!polar_line.singular_cos()) {
        double x_top = polar_line.y_to_x(min_y);
        if (Point top_point(x_top, min_y); inside(top_point))
            add(top_point);
    }
    // clip bottom: max_y
    if (!polar_line.singular_cos()) {
        double x_bottom = polar_line.y_to_x(max_y);
        Point bottom_point(x_bottom, max_y);
        if (inside(bottom_point))
            add(bottom_point);
    }
    // check that exactly two points found
    if (intersections.size() == 2) {
        line_segment.init(intersections[0], intersections[1]);
        return true;
    } else
        return false;
}

bool WB_window::inside(Point &point) const { return inside(point.x, point.y); }
bool WB_window::inside(double x, double y) const {
    if (x < min_x || x > max_x)
        return false;
    if (y < min_y || y > max_y)
        return false;
    return true;
}
/**
 * @brief
 * @return
 */
std::string WB_window::to_string() const {
    std::ostringstream os{};
    os << "(" << min_x << ", " << min_y << ") - (" << max_x << ", " << max_y << ")";
    return os.str();
}
