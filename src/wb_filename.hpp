//
// Created by kushn on 7/26/2022.
//

#ifndef SRC__WB_FILENAME_HPP_
#define SRC__WB_FILENAME_HPP_

#include <string>
#include "cv_data_format.hpp"
#include "errors.hpp"
#include "wb_defs.hpp"

class Wb_filename {
 public:
std::string filename;
std::string root;
std::string ext;
  CV_data_format::format format;

  Wb_filename();
  Wb_filename(std::string m_filename,
  std::string m_root,
  std::string m_ext,
  CV_data_format::format m_format);
  Wb_filename(std::string m_filename, std::string pat);

  void parse_filename(std::string filename, Errors& errors);
  static Wb_filename* parse_image(std::string &filename, Errors& errors);
  static Wb_filename* parse_hist(std::string &filename, Errors &errors);
  static Wb_filename* parse_hough(std::string &filename, Errors &errors);
  static Wb_filename* parse_json(std::string &filename, Errors &errors);
  std::string to_jpeg(Errors &errors);
  std::string to_bin(Errors &errors);
  std::string to_text(Errors &errors);
  std::string to_log(Errors &errors);
  std::string to_hist(Errors &errors);
  std::string to_hist_text(Errors &errors);
  std::string to_hough(Errors &errors);
  std::string to_hough_text(Errors &errors);
  bool match_ext(std::string filename, std::string ext, std::string &root);

};

#endif //SRC__WB_FILENAME_HPP_
