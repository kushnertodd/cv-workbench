#include "wb_window.hpp"
#include <iostream>
#include "polar_trig.hpp"

extern bool debug;

WB_window::WB_window(double m_x_max, double m_x_min, double m_y_max, double m_y_min) :
    x_max(m_x_max), x_min(m_x_min), y_max(m_y_max), y_min(m_y_min) {}

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
bool WB_window::clip_window(int nrhos, int nthetas, Line_segment &line_segment, Polar_trig &polar_trig,
                            Polar_line &line) {
    int theta_lower = nthetas / 4;
    int theta_upper = nthetas * 3 / 4;
    // window is in (col, row) coordinates
    int window_left = 0;
    int window_right = ncols - 1;
    int window_top = 0;
    int window_bottom = nrows - 1;
    if (line.theta_index <= theta_lower || line.theta_index > theta_upper) {
        // case 1: 0 < theta < pi/4 or 3*pi/4 < theta < pi
        // must clip against the window top and bottom first
        int col_at_window_top = polar_trig.rho_theta_row_to_col(line.rho_index, line.theta_index, window_top);
        int col_at_window_bottom = polar_trig.rho_theta_row_to_col(line.rho_index, line.theta_index, window_bottom);
        // get the top or right pixel
        Pixel top_point;
        Pixel bottom_point;
        if (col_at_window_top < window_left && col_at_window_bottom < window_left) {
            // case 1.1: window top and bottom column both to the left of window
            // clipped line invalid -- should not happen with Hough
            if (debug)
                std::cout << "Hough_accum::clip_window case 1.1" << std::endl;
            return false;
        } else if (col_at_window_top < window_left && col_at_window_bottom >= window_left &&
                   col_at_window_bottom <= window_right) {
            // case 1.2: window top column to the left of the window and bottom column inside window
            int row_at_window_left = polar_trig.rho_theta_col_to_row(line.rho_index, line.theta_index, window_left);
            if (debug)
                std::cout << "Hough_accum::clip_window case 1.2"
                          << " row_at_window_left " << row_at_window_left << std::endl;
            top_point.set(row_at_window_left, window_left);
            bottom_point.set(window_bottom, col_at_window_bottom);
        } else if (col_at_window_top >= window_left && col_at_window_top <= window_right &&
                   col_at_window_bottom < window_left) {
            // case 1.3: window top column inside of the window and bottom column to the left of the window
            int row_at_window_left = polar_trig.rho_theta_col_to_row(line.rho_index, line.theta_index, window_left);
            if (debug)
                std::cout << "Hough_accum::clip_window case 1.3"
                          << " row_at_window_left " << row_at_window_left << std::endl;
            top_point.set(window_top, col_at_window_top);
            bottom_point.set(row_at_window_left, window_left);
        } else if (col_at_window_top >= window_left && col_at_window_top <= window_right &&
                   col_at_window_bottom >= window_left && col_at_window_bottom <= window_right) {
            // case 1.4: window top and bottom columns inside of the window
            if (debug)
                std::cout << "Hough_accum::clip_window case 1.4" << std::endl;
            top_point.set(window_top, col_at_window_top);
            bottom_point.set(window_bottom, col_at_window_bottom);
        } else if (col_at_window_top >= window_left && col_at_window_top <= window_right &&
                   col_at_window_bottom > window_right) {
            // case 1.5: window top column inside of the window and bottom column to the right of the window
            int row_at_window_right = polar_trig.rho_theta_col_to_row(line.rho_index, line.theta_index, window_right);
            if (debug)
                std::cout << "Hough_accum::clip_window case 1.5"
                          << " row_at_window_right " << row_at_window_right << std::endl;
            top_point.set(window_top, col_at_window_top);
            bottom_point.set(row_at_window_right, window_right);
        } else if (col_at_window_top > window_right && col_at_window_bottom >= window_left &&
                   col_at_window_bottom <= window_right) {
            // case 1.6: window top column to the right of the window and bottom column inside of the window
            int row_at_window_right = polar_trig.rho_theta_col_to_row(line.rho_index, line.theta_index, window_right);
            if (debug)
                std::cout << "Hough_accum::clip_window case 1.7"
                          << " row_at_window_right " << row_at_window_right << std::endl;
            top_point.set(row_at_window_right, window_right);
            bottom_point.set(window_bottom, col_at_window_bottom);
        } else if (col_at_window_top > window_right && col_at_window_bottom > window_right) {
            // case 1.7: window top and bottom columns to the right of the window
            // clipped line invalid -- should not happen with Hough
            if (debug)
                std::cout << "Hough_accum::clip_window case 1.7" << std::endl;
            return false;
        } else {
            if (debug)
                std::cout << "Hough_accum::clip_window case 1 shouldn't get here" << std::endl;
            return false;
        }
        top_point.check_point_valid(ncols, nrows);
        bottom_point.check_point_valid(ncols, nrows);
        line_segment.set(top_point, bottom_point);
        return true;
    } else {
        // case 2:pi/4 < theta < 3*pi/4
        // must clip against the window left and right first
        int row_at_window_left = polar_trig.rho_theta_col_to_row(line.rho_index, line.theta_index, window_left);
        int row_at_window_right = polar_trig.rho_theta_col_to_row(line.rho_index, line.theta_index, window_right);
        // get the top or right pixel
        Pixel left_point;
        Pixel right_point;
        if (debug)
            std::cout << "Hough_accum::clip_window"
                      << " row_at_window_left " << row_at_window_left << " row_at_window_right " << row_at_window_right
                      << std::endl;
        if (row_at_window_left < window_top && row_at_window_right < window_top) {
            // case 2.1: window left and right row both above the window
            // clipped line invalid -- should not happen with Hough
            if (debug)
                std::cout << "Hough_accum::clip_window case 2.1" << std::endl;
            return false;
        } else if (row_at_window_left < window_top && row_at_window_right >= window_top &&
                   row_at_window_right <= window_bottom) {
            // case 2.2: window left row above the window and right row inside window
            int col_at_window_top = polar_trig.rho_theta_row_to_col(line.rho_index, line.theta_index, window_top);
            if (debug)
                std::cout << "Hough_accum::clip_window case 2.2"
                          << " col_at_window_top " << col_at_window_top << std::endl;
            left_point.set(window_top, col_at_window_top);
            right_point.set(row_at_window_right, window_right);
        } else if (row_at_window_left >= window_top && row_at_window_left <= window_bottom &&
                   row_at_window_right < window_top) {
            // case 2.3: window left row inside of the window and right row above the window
            int col_at_window_top = polar_trig.rho_theta_row_to_col(line.rho_index, line.theta_index, window_top);
            if (debug)
                std::cout << "Hough_accum::clip_window case 2.3"
                          << " col_at_window_top " << col_at_window_top << std::endl;
            left_point.set(row_at_window_left, window_left);
            right_point.set(window_top, col_at_window_top);
        } else if (row_at_window_left >= window_top && row_at_window_left <= window_bottom &&
                   row_at_window_right >= window_top && row_at_window_right <= window_bottom) {
            // case 2.4: window left and right rows inside of the window
            if (debug)
                std::cout << "Hough_accum::clip_window case 2.4" << std::endl;
            left_point.set(row_at_window_left, window_left);
            right_point.set(row_at_window_right, window_right);
        } else if (row_at_window_left >= window_top && row_at_window_left <= window_bottom &&
                   row_at_window_right > window_bottom) {
            // case 2.5: window left row inside of the window and right row above the window
            int col_at_window_bottom = polar_trig.rho_theta_row_to_col(line.rho_index, line.theta_index, window_bottom);
            if (debug)
                std::cout << "Hough_accum::clip_window case 2.5"
                          << " col_at_window_bottom " << col_at_window_bottom << std::endl;
            left_point.set(row_at_window_left, window_left);
            right_point.set(col_at_window_bottom, window_bottom);
        } else if (row_at_window_left > window_bottom && row_at_window_right >= window_top &&
                   row_at_window_right <= window_bottom) {
            // case 2.6: window left row below the window and right row inside of the window
            int col_at_window_bottom = polar_trig.rho_theta_row_to_col(line.rho_index, line.theta_index, window_bottom);
            if (debug)
                std::cout << "Hough_accum::clip_window case 2.6"
                          << " col_at_window_bottom " << col_at_window_bottom << std::endl;
            left_point.set(window_bottom, col_at_window_bottom);
            right_point.set(row_at_window_right, window_right);
        } else if (row_at_window_left > window_bottom && row_at_window_right > window_bottom) {
            // case 2.7: window left and right rows below the windoww
            // clipped line invalid -- should not happen with Hough
            if (debug)
                std::cout << "Hough_accum::clip_window case 2.7" << std::endl;
            return false;
        } else {
            if (debug)
                std::cout << "Hough_accum::clip_window case 2"
                          << " shouldn't get here " << std::endl;
            return false;
        }
        left_point.check_point_valid(ncols, nrows);
        right_point.check_point_valid(ncols, nrows);
        line_segment.set(left_point, right_point);
        return true;
    }
}
