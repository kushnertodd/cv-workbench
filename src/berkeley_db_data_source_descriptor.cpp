//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "berkeley_db_data_source_descriptor.hpp"

using namespace std;

Berkeley_db_data_source_descriptor::Berkeley_db_data_source_descriptor(int m_id,
                                   Cv_data_type_enum m_cv_data_type_enum) :
    Data_source_descriptor(m_id, BERKELEY_DB, m_cv_data_type_enum) {}
void Berkeley_db_data_source_descriptor::read(string json) {}
void Berkeley_db_data_source_descriptor::read(Image *image) {}
void Berkeley_db_data_source_descriptor::read(Histogram *histogram) {}
void Berkeley_db_data_source_descriptor::read(Hough *hough) {}
void Berkeley_db_data_source_descriptor::write(string json) {}
void Berkeley_db_data_source_descriptor::write(Image *image) {}
void Berkeley_db_data_source_descriptor::write(Histogram *histogram) {}
void Berkeley_db_data_source_descriptor::write(Hough *hough) {}

Berkeley_db_data_source_descriptor *Berkeley_db_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                                      int id,
                                                      Cv_data_type_enum cv_data_type_enum, Errors &errors) {
  if (debug)
    cout << "Berkeley_db_data_source_descriptor::json_parse: id '" << id << "' type "
         << cv_data_type_enum << endl;
  Berkeley_db_data_source_descriptor *berkeley_db_data_source_descriptor =
      new Berkeley_db_data_source_descriptor(id, cv_data_type_enum);
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

string Berkeley_db_data_source_descriptor::toString() {
  ostringstream os;
  os << Data_source_descriptor::toString()
     << " ref id " << ref_id;
  return os.str();
}