#ifndef SRC__WB_WINDOW_HPP_
#define SRC__WB_WINDOW_HPP_

#include <list>
#include "line_segment.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"

class WB_window {
    std::list<Point> intersections;
    double x_max;
    double x_min;
    double y_max;
    double y_min;

public:
    WB_window(double m_x_max, double m_x_min, double m_y_max, double m_y_min);
    void add(Point &point);
    bool clip_window(Polar_trig &polar_trig, Polar_line &polar_line, Line_segment &line_segment);
};

#endif // SRC__WB_WINDOW_HPP_
