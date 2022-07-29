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
  CV_data_format::Data_format format;

  Wb_filename();
  Wb_filename(std::string m_filename,
              std::string m_root,
              std::string m_ext,
              CV_data_format::Data_format m_format);
  static Wb_filename *create_wb_filename(std::string m_filename, Errors &errors);

  bool is_bin();
  bool is_jpeg();
  bool is_json();
  bool is_log();
  bool is_text();


  static bool match_ext(std::string filename, std::string ext, std::string &root);
  std::string to_bin();
  std::string to_hist();
  std::string to_hist_script();
  std::string to_hist_text();
  std::string to_hough();
  std::string to_hough_text();
  std::string to_jpeg();
  std::string to_json();
  std::string to_log();
  std::string to_text();
};

#endif //SRC__WB_FILENAME_HPP_
