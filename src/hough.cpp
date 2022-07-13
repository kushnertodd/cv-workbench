//
// Created by kushn on 6/11/2022.
//

#include <fstream>
#include <iostream>
#include "errors.hpp"
#include "file_utils.hpp"
#include "wb_utils.hpp"
#include "hough_accum.hpp"
#include "hough.hpp"

extern bool debug;

Hough::~Hough() {
  for (Polar_line* line : lines) {
    if (line != nullptr)
      delete line;
  }
  for (Line_segment* line_segment : line_segments) {
    if (line_segment != nullptr)
      delete line_segment;
  }
  if (accum != nullptr)
    delete accum;
}

Hough::Hough(Image *m_image, int m_theta_inc) :
    image(m_image),
    theta_inc(m_theta_inc) {
  if (debug)
    std::cout << "Hough::Hough image " << image->to_string() << " theta_inc " << theta_inc << std::endl;
  accum = new Hough_accum(theta_inc, image);
  accum->initialize(200);
}

/*
void Hough::draw_lines(Image *image, float value) {
  if (debug)
    std::cout << "Hough::draw_lines; image " <<image->to_string() << " value " << value<< std::endl;
  for (std::list<Point *> point_list :  line_points){
    if (debug)
      std::cout << "Hough::draw_lines; line_points size  " <<line_points.size()<< std::endl;
    for (Point* point : point_list) {
      if (!point->in_window()) {
        std::cout << "Hough::draw_lines; bad point  " <<point->to_string()<< std::endl;
      } else {
      image->set(point, value);
        std::cout << "Hough::draw_lines; good point  " <<point->to_string()<< std::endl;
    }}
  }
}
*/

void Hough::find_lines() {
  find_peaks();
  lines_to_line_segments();
}

void Hough::find_peaks() {
  int peak_threshold = accum->choose_threshold(cv_enums::CV_threshold_type::FIXED);
  accum->find_peaks(lines, peak_threshold);
  if (debug) {
    for (Polar_line *line: lines) {
      std::cout << "Hough::find_peaks: lines " << line->to_string() << std::endl;
    }
  }
}

void Hough::lines_to_line_segments() {
  for (Polar_line *line: lines) {
    Line_segment *line_segment = accum->clip_window(line);
    if (line_segment != nullptr)
      line_segments.push_back(line_segment);
  }
}

bool Hough::read(std::string filename, Errors &errors) {
  std::ifstream ifs(filename, std::ofstream::in);
  if (!ifs) {
    errors.add("Hough:read", "", "invalid filename '" + filename + "'");
    return false;
  }
  bool return_value = true;
  if (!accum->read(ifs, errors)) {
    return_value = false;
  }
  ifs.close();
  return return_value;
}

bool Hough::write(std::string filename, std::string delim, Errors &errors) {
  std::ofstream ofs(filename, std::ofstream::out);
  if (!ofs) {
    errors.add("Hough:write", "", "invalid filename '" + filename + "'");
    return false;
  }
  bool return_value = true;
  if (!accum->write_str(ofs, "\t", errors)) {
    return_value = false;
  }
  ofs.close();
  return return_value;
}




