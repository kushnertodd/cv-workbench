#include "wb_window.hpp"
#include <iostream>
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
 * @param m_x_min
 * @param m_y_min
 * @param m_x_max
 * @param m_y_max
 */
WB_window::WB_window(double m_x_min, double m_y_min, double m_x_max, double m_y_max) :
    x_min(m_x_min), y_min(m_y_min), x_max(m_x_max), y_max(m_y_max) {}
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
    // clip left: x_min
    double y_left;
    if (!Polar_trig::singular_sin(polar_line.get_theta())) {
        y_left = Polar_trig::rho_theta_x_to_y(polar_line.get_rho(), polar_line.get_theta(), x_min);
        Point left_point(x_min, y_left);
        if (inside(left_point))
            add(left_point);
    }
    // clip right: x_max
    double y_right;
    if (!Polar_trig::singular_sin(polar_line.get_theta())) {
        y_right = Polar_trig::rho_theta_x_to_y(polar_line.get_rho(), polar_line.get_theta(), x_max);
        Point right_point(x_max, y_right);
        if (inside(right_point))
            add(right_point);
    }
    // clip top: y_min
    double x_top;
    if (!Polar_trig::singular_cos(polar_line.get_theta())) {
        x_top = Polar_trig::rho_theta_y_to_x(polar_line.get_rho(), polar_line.get_theta(), y_min);
        Point top_point(x_top, y_min);
        if (inside(top_point))
            add(top_point);
    }
    // clip bottom: y_max
    double x_bottom;
    if (!Polar_trig::singular_cos(polar_line.get_theta())) {
        x_bottom = Polar_trig::rho_theta_y_to_x(polar_line.get_rho(), polar_line.get_theta(), y_max);
        Point bottom_point(x_bottom, y_min);
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
    if (point.x < x_min || point.x > x_max)
        return false;
    if (point.y < y_min || point.y > y_max)
        return false;
    return true;
}
