//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_data_format.hpp"
#include "wb_data_type.hpp"
#include "wb_repository_type.hpp"
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "berkeley_db_data_source_descriptor.hpp"

extern bool debug;

Berkeley_db_data_source_descriptor::Berkeley_db_data_source_descriptor(int m_id,
                                                                       WB_data_type::Data_type m_data_type,
                                                                       WB_data_format::Data_format m_data_format) :
    Data_source_descriptor(m_id,
                           m_data_type,
                           m_data_format,
                           WB_repository_types::Repository_type::BERKELEY_DB),
    ref_id(0) {}

Berkeley_db_data_source_descriptor
*Berkeley_db_data_source_descriptor::from_json(json_object *json_data_source_descriptor,
                                               int id,
                                               WB_data_type::Data_type data_type,
                                               WB_data_format::Data_format data_format,
                                               Errors &errors) {
  if (debug)
    std::cout << "Berkeley_db_data_source_descriptor::from_json: id '" << id << "' type "
              << std::endl;
  auto *berkeley_db_data_source_descriptor =
      new Berkeley_db_data_source_descriptor(id, data_type, data_format);
  json_object *json_ref_id =
      get_json_object("Berkeley_db_data_source_descriptor::from_json",
                      json_data_source_descriptor,
                      "ref-id",
                      json_type_int,
                      errors,
                      true);
  if (json_ref_id != nullptr) {
    berkeley_db_data_source_descriptor->ref_id = json_object_get_int(json_ref_id);
  }
  return berkeley_db_data_source_descriptor;
}

Histogram *Berkeley_db_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }
Hough *Berkeley_db_data_source_descriptor::read_hough(Errors &errors) { return nullptr; }
Image *Berkeley_db_data_source_descriptor::read_image(Errors &errors) { return nullptr; }
Image *Berkeley_db_data_source_descriptor::read_image_jpeg(Errors &errors) { return nullptr; }
Image *Berkeley_db_data_source_descriptor::read_image_text(Errors &errors) { return nullptr; }
std::string Berkeley_db_data_source_descriptor::read_json(Errors &errors) { return ""; }
void Berkeley_db_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_histogram_text(Histogram *histogram, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_hough_text(Hough *hough, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_hough_peaks(Hough *hough, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_hough_peaks_text(Hough *hough, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_image(Image *image, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_image_jpeg(Image *image, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_image_text(Image *image, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_json(std::string &json, Errors &errors) {}

std::string Berkeley_db_data_source_descriptor::to_string() {
  std::ostringstream os;
  os << Data_source_descriptor::to_string()
     << " ref id " << ref_id;
  return os.str();
}
