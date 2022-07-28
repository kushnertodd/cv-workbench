//
// Created by kushn on 7/26/2022.
//

#include "errors.hpp"
#include "wb_utils.hpp"
#include "wb_filename.hpp"

Wb_filename::Wb_filename() {}

Wb_filename::Wb_filename(std::string m_filename,
                         std::string m_root,
                         std::string m_ext,
                         CV_data_format::Data_format m_format) {}

Wb_filename *Wb_filename::create_wb_filename(std::string filename, Errors &errors) {
  for (const auto data_format: CV_data_format::from_exts) {
    std::string ext = data_format.first;
    std::string root;
    if (match_ext(filename, ext, root)) {
      Wb_filename *wb_filename = new Wb_filename(filename, root, ext, data_format.second);
      return wb_filename;
    }
  }
  return nullptr;
}

bool Wb_filename::match_ext(std::string filename, std::string ext, std::string &root) {
  std::string prefix, suffix;
  bool at_beginning, at_end;
  if (wb_utils::string_find(filename, prefix, suffix, "." + ext, at_beginning, at_end)) {
    if (at_end) {
      root = prefix;
      return true;
    }
  }
  return false;
}

std::string Wb_filename::to_jpeg(Errors &errors) { return filename + ".jpg"; }
std::string Wb_filename::to_bin(Errors &errors) { return filename + ".bin"; }
std::string Wb_filename::to_text(Errors &errors) { return filename + ".txt"; }
std::string Wb_filename::to_log(Errors &errors) { return filename + ".log"; }
std::string Wb_filename::to_hist(Errors &errors) { return filename + ".hist.bin"; }
std::string Wb_filename::to_hist_text(Errors &errors) { return filename + ".hist.txt"; }
std::string Wb_filename::to_hough(Errors &errors) { return filename + ".hough.bin"; }
std::string Wb_filename::to_hough_text(Errors &errors) { return filename + ".hough.txt"; }
