//
// Created by kushn on 8/9/2022.
//

#ifndef SRC__WB_WINDOW_HPP_
#define SRC__WB_WINDOW_HPP_

#include "line_segment.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"

class WB_window {
public:
    static bool clip_window(int nrows, int ncols, int nrhos, int nthetas, Line_segment &line_segment,
                            Polar_trig &polar_trig, Polar_line &line);
};

#endif // SRC__WB_WINDOW_HPP_
