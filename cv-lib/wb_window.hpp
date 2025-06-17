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
    double min_x;
    double min_y;
    double max_x;
    double max_y;

public:
    WB_window(Point &point_min, Point &point_max);
    WB_window(double m_min_x, double m_min_y, double m_max_x, double m_max_y);
    void add(Point &point);
    bool clip_window(Polar_line &polar_line, Line_segment &line_segment);
    bool inside(Point &point) const;
    bool inside(double x, double y) const;
    std::string to_string() const;
};

#endif // SRC__WB_WINDOW_HPP_
