//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "berkeley_db_data_source_descriptor.hpp"

//

extern bool debug;

Berkeley_db_data_source_descriptor::Berkeley_db_data_source_descriptor(int m_id,
                                                                       cv_enums::CV_data_type m_cv_data_type) :
    Data_source_descriptor(m_id, cv_enums::BERKELEY_DB, m_cv_data_type) {}

std::string Berkeley_db_data_source_descriptor::read_json(Errors &errors) { return ""; }
Image *Berkeley_db_data_source_descriptor::read_image(Errors &errors) { return nullptr; }
Histogram *Berkeley_db_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }
Hough *Berkeley_db_data_source_descriptor::read_hough(Errors &errors) { return nullptr; }
void Berkeley_db_data_source_descriptor::write_json(std::string &json, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_image(Image *image, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {}
void Berkeley_db_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {}

Berkeley_db_data_source_descriptor *Berkeley_db_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                                                                   int id,
                                                                                   cv_enums::CV_data_type data_type,
                                                                                   Errors &errors) {
  if (debug)
    std::cout << "Berkeley_db_data_source_descriptor::json_parse: id '" << id << "' type "
         << data_type << std::endl;
  Berkeley_db_data_source_descriptor *berkeley_db_data_source_descriptor =
      new Berkeley_db_data_source_descriptor(id, data_type);
  json_object *json_ref_id =
      get_json_object("Berkeley_db_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "ref-id",
                      json_type_int,
                      errors,
                      true);
  if (json_ref_id != nullptr) {
    berkeley_db_data_source_descriptor->ref_id = json_object_get_int(json_ref_id);
  }
  return berkeley_db_data_source_descriptor;
}

std::string Berkeley_db_data_source_descriptor::to_string() {
  std::ostringstream os;
  os << Data_source_descriptor::to_string()
     << " ref id " << ref_id;
  return os.str();
}
