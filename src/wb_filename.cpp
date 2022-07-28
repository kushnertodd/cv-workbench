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
                         CV_data_format::format m_format) {}

Wb_filename::Wb_filename(std::string m_filename, Errors &errors) {
  for (auto format :
       {
         CV_data_format::format::BINARY,
         CV_data_format::format::JPEG,
         CV_data_format::format::JSON,
         CV_data_format::format::LOG,
         CV_data_format::format::TEXT
       }) {
    std::string m_ext = CV_data_format::data_format_enum_to_ext(format);
    std::string root;
    if (Wb_filename::match_ext(filename, ext, root)) {
      filename = m_filename;
      root = root;
      ext = m_ext;
    }
  }
}

void Wb_filename::parse_filename(std::string filename, Errors& errors) {
  std::string prefix;
  std::string suffix;
  bool  at_beginning;
  bool at_end;

  //bool string_find(const std::string& text, std::string& prefix, std::string& suffix, const std::string& pat, bool &at_beginning, bool &at_end);
}

bool Wb_filename::match_ext(std::string filename, std::string ext, std::string &root) {
  std::string prefix,suffix;
  bool at_beginning, at_end;
  if (wb_utils::string_find(filename, prefix, suffix, "."+ext, at_beginning, at_end)) {
    if (at_end) {
      root = prefix;
      return true;
    }
  }
  return false;
}



Wb_filename* Wb_filename::parse_image(std::string &filename, Errors& errors) {
  Wb_filename* wb_filename = new Wb_filename();
  return wb_filename;
}

Wb_filename* Wb_filename::parse_hist(std::string &filename, Errors &errors) {return nullptr;}
Wb_filename* Wb_filename::parse_hough(std::string &filename, Errors &errors) {return nullptr;}
Wb_filename* Wb_filename::parse_json(std::string &filename, Errors &errors) {return nullptr;}
std::string Wb_filename::to_jpeg(Errors &errors) {return "";}
std::string Wb_filename::to_bin(Errors &errors) {return "";}
std::string Wb_filename::to_text(Errors &errors) {return "";}
std::string Wb_filename::to_log(Errors &errors) {return "";}
std::string Wb_filename::to_hist(Errors &errors) {return "";}
std::string Wb_filename::to_hist_text(Errors &errors) {return "";}
std::string Wb_filename::to_hough(Errors &errors) {return "";}
std::string Wb_filename::to_hough_text(Errors &errors) {return "";}
