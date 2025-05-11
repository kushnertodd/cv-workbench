#ifndef SRC__WB_WINDOW_HPP_
#define SRC__WB_WINDOW_HPP_

#include <vector>
#include "line_segment.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"

/**
 * @brief
 */
class WB_window {
    std::vector<Point> intersections;
    double x_min;
    double y_min;
    double x_max;
    double y_max;

public:
    WB_window(Point &point_min, Point &point_max);
    WB_window(double m_x_min, double m_y_min, double m_x_max, double m_y_max);
    void add(Point &point);
    bool clip_window(Polar_line &polar_line, Line_segment &line_segment);
    bool inside(Point &point) const;
    std::string to_string() const;
};

#endif // SRC__WB_WINDOW_HPP_
