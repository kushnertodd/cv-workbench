//
// Created by kushn on 8/9/2022.
//

#include <iostream>
#include "wb_window.hpp"

extern bool debug;

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
 *  @image html cv-workbench_wb_window_clip_90_degree.jpg
 *
 *   This shows the position of the clip point in each subcase:
 *   case        | 1.1| 1.2  | 1.3  | 1.4  | 1.5  | 1.6  |1.7
 *   ------------|----|------|------|------|------|------|-----
 *   upper point |left|left  |inside|inside|inside|right |right
 *   lower point |left|inside|left  |inside|right |inside|right
 *
 *   This shows the intersection points that make up the resulting line segment, or none:
 *   case         |1.1 |1.2   |1.3   |1.4   |1.5  | 1.6  |1.7
 *   -------------|----|------|------|------|-----|------|-----
 *   first point  |none|left  |top   |top   |top  |right |none
 *   second point |none|bottom|left  |bottom|right|bottom|none
 *
 * - case 2: pi/4 < theta < 3*pi/4
 *   must clip against the window left and right first
 *
 *   In case 2, there are 7 subcases where clip points are above, inside,
 *   or below the window:
 *
 *  @image html cv-workbench_wb_window_clip_0_degree.jpg
 *
 *   This shows the position of the clip point in each subcase:
 *   case       | 2.1 | 2.2  | 2.3   | 2.4  | 2.5  | 2.6  | 2.7
 *   -----------|-----|------|-------|------|------|------|-----
 *   upper point|above|above |inside |inside|inside|below |below
 *   lower point|above|inside|above  |inside|below |inside|below
 *
 *   This shows the intersection points that make up the resulting line segment, or none:
 *   case        |2.1 |2.2  | 2.3 |  2.4  | 2.5   |2.6   |2.7
 *   ------------|----|-----|-----|-------|-------|------|-----
 *   first point |none|top  | left|  left | left  |bottom|none
 *   second point|none|right| top |  right| bottom|right |none
 *
 * @param line Polar line to clip against window
 * @return line segment of endpoint on the window, or nullptr if none -- the latter won't occur for Hough lines
 */
void WB_window::clip_window(int rows, int cols, Line_segment &line_segment, Polar_line &line, Errors &errors) {
  line_segment.clear();
  // window is in (row, col) coordinates
  int window_left = 0;
  int window_right = cols - 1;
  int window_top = 0;
  int window_bottom = rows - 1;
  //double theta_lower = 89; //Theta::radians_to_degrees(atan2(rows, cols));
  //double theta_upper = 180 - theta_lower;
  bool clip_failed = true;
/*
  double line_cos = line.to_cos();
  double line_sin = line.to_sin();
  double window_diagonal = sqrt(rows*rows + cols*cols);
  double window_cos = cols / window_diagonal;
  double window_sin = rows / window_diagonal;
  double product1 = line_sin * window_cos;
  double product2 = window_sin * line_cos;
  double tan_window_diagonal_theta_radians = atan2(rows, cols);
  double tan_window_diagonal_theta_degrees = tan_window_diagonal_theta_radians * 180 / M_PI;
  double theta_lower =tan_window_diagonal_theta_degrees ;
  double theta_upper = 180 - tan_window_diagonal_theta_degrees;
*/
  //if (true) {//line.get_theta_degrees() < theta_lower || line.get_theta_degrees() > theta_upper) {
  //if (product1 >= product2 && product1 <= -product2) {
  //if (line.get_theta_degrees() >= theta_lower && line.get_theta_degrees() < theta_upper) {
  // case 1: line is relatively vertical
  // clip against the window top and bottom first
  int col_at_window_top = line.row_to_col(window_top, rows, cols);
  int col_at_window_bottom = line.row_to_col(window_bottom, rows, cols);
  int row_at_window_left = line.col_to_row(window_left, rows, cols);
  int row_at_window_right = line.col_to_row(window_right, rows, cols);
  // get the top or right point
  Point top_point;
  Point bottom_point;
  if (col_at_window_top < window_left
      && col_at_window_bottom < window_left) {
    // case 1.1: window top and bottom column both to the left of window
    // clipped line invalid -- should not happen with Hough
    if (debug)
      std::cout << "Hough_accum::clip_window case 1.1"
                << std::endl;
    // return false;
  } else if (col_at_window_top < window_left
      && col_at_window_bottom >= window_left
      && col_at_window_bottom <= window_right) {
    // case 1.2: window top column to the left of the window and bottom column inside window
     row_at_window_left = line.col_to_row(window_left, rows, cols);
    if (debug)
      std::cout << "Hough_accum::clip_window case 1.2"
                << " row_at_window_left " << row_at_window_left
                << std::endl;
    top_point.set(row_at_window_left, window_left);
    bottom_point.set(window_bottom, col_at_window_bottom);
    clip_failed = false;
  } else if (col_at_window_top >= window_left
      && col_at_window_top <= window_right
      && col_at_window_bottom < window_left) {
    // case 1.3: window top column inside of the window and bottom column to the left of the window
     row_at_window_left = line.col_to_row(window_left, rows, cols);
    if (debug)
      std::cout << "Hough_accum::clip_window case 1.3"
                << " row_at_window_left " << row_at_window_left
                << std::endl;
    top_point.set(window_top, col_at_window_top);
    bottom_point.set(row_at_window_left, window_left);
    clip_failed = false;
  } else if (col_at_window_top >= window_left && col_at_window_top <= window_right
      && col_at_window_bottom >= window_left && col_at_window_bottom <= window_right) {
    // case 1.4: window top and bottom columns inside of the window
    if (debug)
      std::cout << "Hough_accum::clip_window case 1.4"
                << std::endl;
    top_point.set(window_top, col_at_window_top);
    bottom_point.set(window_bottom, col_at_window_bottom);
    clip_failed = false;
  } else if (col_at_window_top >= window_left
      && col_at_window_top <= window_right
      && col_at_window_bottom > window_right) {
    // case 1.5: window top column inside of the window and bottom column to the right of the window
     row_at_window_right =
    line.col_to_row(window_right, rows, cols);
    if (debug)
      std::cout << "Hough_accum::clip_window case 1.5"
                << " row_at_window_right " << row_at_window_right
                << std::endl;
    top_point.set(window_top, col_at_window_top);
    bottom_point.set(row_at_window_right, window_right);
    clip_failed = false;
  } else if (col_at_window_top > window_right
      && col_at_window_bottom >= window_left
      && col_at_window_bottom <= window_right) {
    // case 1.6: window top column to the right of the window and bottom column inside of the window
     row_at_window_right = line.col_to_row(window_right, rows, cols);
    if (debug)
      std::cout << "Hough_accum::clip_window case 1.7"
                << " row_at_window_right " << row_at_window_right
                << std::endl;
    top_point.set(row_at_window_right, window_right);
    bottom_point.set(window_bottom, col_at_window_bottom);
    clip_failed = false;
  } else if (col_at_window_top > window_right
      && col_at_window_bottom > window_right) {
    // case 1.7: window top and bottom columns to the right of the window
    // clipped line invalid -- should not happen with Hough
    if (debug)
      std::cout << "Hough_accum::clip_window case 1.7"
                << std::endl;
    //return false;
  } else {
    if (debug)
      std::cout << "Hough_accum::clip_window case 1 shouldn't get here"
                << std::endl;
    //return false;
  }
  if (!clip_failed) {
    top_point.check_point_valid(rows, cols);
    bottom_point.check_point_valid(rows, cols);
    line_segment.set(top_point, bottom_point);
    return;
  }
  //} //else
  // if we got here, clip failed or was untested
  // case 2: line relatively horizontal
  // clip against the window left and right first
//  int row_at_window_left = line.col_to_row(window_left, rows, cols);
//  int row_at_window_right = line.col_to_row(window_right, rows, cols);
//  int col_at_window_top = line.row_to_col(window_top, rows, cols);
//  int col_at_window_bottom = line.row_to_col(window_bottom, rows, cols);
  // get the top or right point
  Point left_point;
  Point right_point;
  if (debug)
    std::cout << "Hough_accum::clip_window"
              << " row_at_window_left " << row_at_window_left
              << " row_at_window_right " << row_at_window_right
              << std::endl;
  if (row_at_window_left < window_top
      && row_at_window_right < window_top) {
    // case 2.1: window left and right row both above the window
    // clipped line invalid -- should not happen with Hough
    if (debug)
      std::cout << "Hough_accum::clip_window case 2.1"
                << std::endl;
    //return false;
  } else if (row_at_window_left < window_top
      && row_at_window_right >= window_top
      && row_at_window_right <= window_bottom) {
    // case 2.2: window left row above the window and right row inside window
     col_at_window_top = line.row_to_col(window_top, rows, cols);
    if (debug)
      std::cout << "Hough_accum::clip_window case 2.2"
                << " col_at_window_top " << col_at_window_top
                << std::endl;
    left_point.set(window_top, col_at_window_top);
    right_point.set(row_at_window_right, window_right);
    clip_failed = false;
  } else if (row_at_window_left >= window_top
      && row_at_window_left <= window_bottom
      && row_at_window_right < window_top) {
    // case 2.3: window left row inside of the window and right row above the window
     col_at_window_top = line.row_to_col(window_top, rows, cols);
    if (debug)
      std::cout << "Hough_accum::clip_window case 2.3"
                << " col_at_window_top " << col_at_window_top
                << std::endl;
    left_point.set(row_at_window_left, window_left);
    right_point.set(window_top, col_at_window_top);
    clip_failed = false;
  } else if (row_at_window_left >= window_top && row_at_window_left <= window_bottom
      && row_at_window_right >= window_top && row_at_window_right <= window_bottom) {
    // case 2.4: window left and right rows inside of the window
    if (debug)
      std::cout << "Hough_accum::clip_window case 2.4"
                << std::endl;
    left_point.set(row_at_window_left, window_left);
    right_point.set(row_at_window_right, window_right);
    clip_failed = false;
  } else if (row_at_window_left >= window_top && row_at_window_left <= window_bottom
      && row_at_window_right > window_bottom) {
    // case 2.5: window left row inside of the window and right row above the window
     col_at_window_bottom = line.row_to_col(window_bottom, rows, cols);
    if (debug)
      std::cout << "Hough_accum::clip_window case 2.5"
                << " col_at_window_bottom " << col_at_window_bottom
                << std::endl;
    left_point.set(row_at_window_left, window_left);
    right_point.set(window_bottom, col_at_window_bottom);
    clip_failed = false;
  } else if (row_at_window_left > window_bottom
      && row_at_window_right >= window_top
      && row_at_window_right <= window_bottom) {
    // case 2.6: window left row below the window and right row inside of the window
     col_at_window_bottom = line.row_to_col(window_bottom, rows, cols);
    if (debug)
      std::cout << "Hough_accum::clip_window case 2.6"
                << " col_at_window_bottom " << col_at_window_bottom
                << std::endl;
    left_point.set(window_bottom, col_at_window_bottom);
    right_point.set(row_at_window_right, window_right);
    clip_failed = false;
  } else if (row_at_window_left > window_bottom
      && row_at_window_right > window_bottom) {
    // case 2.7: window left and right rows below the windoww
    // clipped line invalid -- should not happen with Hough
    if (debug)
      std::cout << "Hough_accum::clip_window case 2.7"
                << std::endl;
    //return false;
  } else {
    if (debug)
      std::cout << "Hough_accum::clip_window case 2"
                << " shouldn't get here "
                << std::endl;
    //return false;
  }
  if (!clip_failed) {
    left_point.check_point_valid(rows, cols);
    right_point.check_point_valid(rows, cols);
    line_segment.set(left_point, right_point);
  } else
    errors.add("Operator_hough_draw_line::run", "", "failed clipping " +line.to_string() + " against image ");
  //return !clip_failed;
}

