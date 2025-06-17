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
    if (!Polar_trig::singular_sin(polar_line.get_theta())) {
        double y_left = Polar_trig::rho_theta_x_to_y(polar_line.get_rho(), polar_line.get_theta(), min_x);
        if (Point left_point(min_x, y_left); inside(left_point))
            add(left_point);
    }
    // clip right: max_x
    if (!Polar_trig::singular_sin(polar_line.get_theta())) {
        double y_right = Polar_trig::rho_theta_x_to_y(polar_line.get_rho(), polar_line.get_theta(), max_x);
        Point right_point(max_x, y_right);
        if (inside(right_point))
            add(right_point);
    }
    // clip top: min_y
    if (!Polar_trig::singular_cos(polar_line.get_theta())) {
        double x_top = Polar_trig::rho_theta_y_to_x(polar_line.get_rho(), polar_line.get_theta(), min_y);
        if (Point top_point(x_top, min_y); inside(top_point))
            add(top_point);
    }
    // clip bottom: max_y
    if (!Polar_trig::singular_cos(polar_line.get_theta())) {
        double x_bottom = Polar_trig::rho_theta_y_to_x(polar_line.get_rho(), polar_line.get_theta(), max_y);
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

bool WB_window::inside(Point &point) const {
    return inside(point.x, point.y);
}
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
