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

  static bool match_ext(std::string filename, std::string ext, std::string &root);
  std::string to_jpeg(Errors &errors);
  std::string to_bin(Errors &errors);
  std::string to_text(Errors &errors);
  std::string to_log(Errors &errors);
  std::string to_hist(Errors &errors);
  std::string to_hist_text(Errors &errors);
  std::string to_hough(Errors &errors);
  std::string to_hough_text(Errors &errors);
};

#endif //SRC__WB_FILENAME_HPP_
