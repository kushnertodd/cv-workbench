//
// Created by kushn on 8/9/2022.
//

#ifndef SRC__WB_WINDOW_HPP_
#define SRC__WB_WINDOW_HPP_

#include "line_segment.hpp"
#include "polar_line.hpp"

class WB_window {
 public:
  static bool clip_window(int rows, int cols, Line_segment &line_segment, Polar_line &line, int nrhos);
};

#endif //SRC__WB_WINDOW_HPP_
