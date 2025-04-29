#ifndef SRC__WB_WINDOW_HPP_
#define SRC__WB_WINDOW_HPP_

#include "line_segment.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"

class WB_window {
    double x_max;
    double x_min;
    double y_max;
    double y_min;

public:
    WB_window(double m_x_max, double m_x_min, double m_y_max, double m_y_min);
    bool clip_window(Line_segment &line_segment, Polar_trig &polar_trig, Polar_line &line);
};

#endif // SRC__WB_WINDOW_HPP_
