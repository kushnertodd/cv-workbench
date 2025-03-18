//
// Created by kushn on 7/26/2022.
//

#include "errors.hpp"
#include "wb_utils.hpp"
#include "wb_filename.hpp"

Wb_filename::Wb_filename() = default;

Wb_filename::Wb_filename(std::string m_filename,
                         std::string m_root,
                         std::string m_ext,
                         WB_data_format::Data_format m_format) :
    filename(std::move(m_filename)),
    root(std::move(m_root)),
    ext(std::move(m_ext)),
    format(m_format) {}

void Wb_filename::add_suffix(const std::string &suffix){
  root += suffix;
}

Wb_filename *Wb_filename::create_wb_filename(const std::string &filename, Errors &errors) {
  for (const auto &data_format: WB_data_format::from_exts) {
    std::string ext = data_format.first;
    std::string root;
    if (match_ext(filename, ext, root)) {
      auto *wb_filename = new Wb_filename(filename, root, ext, data_format.second);
      return wb_filename;
    }
  }
  errors.add("", "", "unrecognized filename extension: " + filename);
  return nullptr;
}

bool Wb_filename::is_bin() const {
  return ext == "bin";
}
bool Wb_filename::is_jpeg() const {
  return ext == "jpg" || ext == "jpeg";
}
bool Wb_filename::is_json() const {
  return ext == "json";
}
bool Wb_filename::is_log() const {
  return ext == "log";
}
bool Wb_filename::is_text() const {
  return ext == "txt";
}

bool Wb_filename::match_ext(const std::string &filename, const std::string &ext, std::string &root) {
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

std::string Wb_filename::to_bin() const { return root + ".bin"; }
std::string Wb_filename::to_hist() const { return root + ".hist.bin"; }
std::string Wb_filename::to_hist_script() const { return root + ".hist.gp"; }
std::string Wb_filename::to_hist_text() const { return root + ".hist.txt"; }
std::string Wb_filename::to_hough() const { return root + ".hough.bin"; }
std::string Wb_filename::to_hough_text() const { return root + ".hough.txt"; }
std::string Wb_filename::to_jpeg() const { return root + ".jpg"; }
std::string Wb_filename::to_json() const { return root + ".json"; }
std::string Wb_filename::to_log() const { return root + ".log"; }
std::string Wb_filename::to_peaks() const { return root + ".peaks.bin"; }
std::string Wb_filename::to_peaks_text() const { return root + ".peaks.txt"; }
std::string Wb_filename::to_text() const { return root + ".txt"; }
