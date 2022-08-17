//
// Created by kushn on 7/30/2022.
//

#include <fstream>
#include "errors.hpp"
#include "wb_log.hpp"

WB_log_entry::WB_log_entry(std::string m_item,
                           std::string m_value) :
    item(std::move(m_item)),
    value(std::move(m_value)) {}

void WB_log::log_to_file(const std::string& filename, const std::string& text, Errors &errors) {
  std::ofstream ofs(filename, std::ofstream::out);
  if (!ofs) {
    errors.add("Histogram::write_text", "", "invalid file '" + filename + "'");
    return;
  }
  ofs << text << std::endl;
  ofs.close();
}