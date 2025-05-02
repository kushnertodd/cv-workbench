#include "wb_window.hpp"
#include <iostream>
#include "polar_trig.hpp"

extern bool debug;

/**
 * @brief
 * @param m_x_max
 * @param m_x_min
 * @param m_y_max
 * @param m_y_min
 */
WB_window::WB_window(double m_x_max, double m_x_min, double m_y_max, double m_y_min) :
    x_max(m_x_max), x_min(m_x_min), y_max(m_y_max), y_min(m_y_min) {}
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
 * There are two main cases based on the angle of the line, because there is a potential
 * singularity clipping the other way:
 *
 * - case 1: 0 < theta < pi/4 and 3*pi/4 < theta < pi
 *   must clip against the window top and bottom first
 *
 *   In case 1, there are 7 subcases where clip points are to the left, inside,
 *   or to the right of the window:
 *
 *
 * - case 2: pi/4 < theta < 3*pi/4
 *   must clip against the window left and right first
 *
 *
 * @param line Polar line to clip against window
 * @return line segment of endpoint on the window, or nullptr if none -- the latter won't occur for Hough lines
 */
bool WB_window::clip_window(Polar_trig &polar_trig, Polar_line &polar_line, Line_segment &line_segment) {
    // clip left: x_min
    double y_left;
    if (!Polar_trig::singular_sin(polar_line.theta)) {
        y_left = polar_trig->rho_theta_x_to_y(polar_line.rho, polar_line.theta, x_min);
        Point left_point(x_min, y_left);
        add(left_point);
    }
    // clip right: x_max
    double y_right;
    if (!Polar_trig::singular_sin(polar_line.theta)) {
        y_right = polar_trig->rho_theta_x_to_y(polar_line.rho, polar_line.theta, x_max);
        Point right_point(x_max, y_right);
        add(right_point);
    }
    // clip top: y_min
    double x_top;
    if (!Polar_trig::singular_cos(polar_line.theta)) {
        x_top = polar_trig->rho_theta_y_to_x(polar_line.rho, polar_line.theta, y_min);
        Point top_point(x_top, y_min);
        add(top_point);
    }
    // clip bottom: y_max
    double x_bottom;
    if (!Polar_trig::singular_cos(polar_line.theta)) {
        x_bottom = polar_trig->rho_theta_y_to_x(polar_line.rho, polar_line.theta, y_min);
        Point bottom_point(x_bottom, y_min);
        add(bottom_point);
    }
    // check that exactly two points found
    if (intersections.size == 2) {
        line_segment.init(intersections[0], intersections[1]);
        return true;
    } else
        return false;
}
