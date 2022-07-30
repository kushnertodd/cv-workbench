//
// Created by kushn on 7/30/2022.
//

#include <fstream>
#include "errors.hpp"
#include "wb_log.hpp"

void WB_log::log_to_file(std::string filename, std::string text, Errors &errors) {
  std::ofstream ofs(filename, std::ofstream::out);
  if (!ofs) {
    errors.add("Histogram::write_text", "", "invalid file '" + filename + "'");
    return;
  }
  ofs << text << std::endl;
  ofs.close();
}