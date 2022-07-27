//
// Created by kushn on 7/26/2022.
//

#include "wb_filename.hpp"

void parse_filename(std::string filename, Errors& errors) {

  bool string_find(const std::string& text, std::string& prefix, std::string& suffix, const std::string& pat, bool &at_beginning, bool &at_end);

}

static Wb_filename* parse_image(std::string &filename, Errors& errors){
  Wb_filename* wb_filename = new Wb_filename();
}

static Wb_filename* parse_hist(std::string &filename, Errors &errors){}
static Wb_filename* parse_hough(std::string &filename, Errors &errors){}
static Wb_filename* parse_json(std::string &filename, Errors &errors){}
std::string to_jpeg(Errors &errors){}
std::string to_bin(Errors &errors){}
std::string to_text(Errors &errors){}
std::string to_log(Errors &errors){}
std::string to_hist(Errors &errors){}
std::string to_hist_text(Errors &errors){}
std::string to_hough(Errors &errors){}
std::string to_hough_text(Errors &errors){}