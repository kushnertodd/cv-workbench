//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "internet_data_source_descriptor.hpp"

extern bool debug;

using namespace std;

Internet_data_source_descriptor::Internet_data_source_descriptor(int m_id,
                                                                 Cv_data_type_enum m_cv_data_type_enum) :
    Data_source_descriptor(m_id, INTERNET, m_cv_data_type_enum) {}
string Internet_data_source_descriptor::read_json(Errors &errors) { return nullptr; }
Image *Internet_data_source_descriptor::read_image(Errors &errors) { return nullptr; }
Histogram *Internet_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }
Hough *Internet_data_source_descriptor::read_hough(Errors &errors) { return nullptr; }
void Internet_data_source_descriptor::write_json(string &json, Errors &errors) {}
void Internet_data_source_descriptor::write_image(Image *image, Errors &errors) {}
void Internet_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {}
void Internet_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {}

Internet_data_source_descriptor *Internet_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                                                             int id,
                                                                             Cv_data_type_enum data_type,
                                                                             Errors &errors) {
  if (debug)
    cout << "Internet_data_source_descriptor::json_parse: id '" << id << "' type "
         << data_type << endl;
  Internet_data_source_descriptor *internet_data_source_descriptor =
      new Internet_data_source_descriptor(id, data_type);
  json_object *json_url =
      get_json_object("Internet_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "url",
                      json_type_string,
                      errors);
  if (json_url != nullptr)
    internet_data_source_descriptor->url = json_object_get_string(json_url);
  json_object *json_depth =
      get_json_object("Internet_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "depth",
                      json_type_string,
                      errors);
  if (json_depth != nullptr)
    internet_data_source_descriptor->depth = json_object_get_string(json_depth);
  json_object *json_rows =
      get_json_object("Internet_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "rows",
                      json_type_int,
                      errors);
  if (json_rows != nullptr)
    internet_data_source_descriptor->rows = json_object_get_int(json_rows);
  json_object *json_columns =
      get_json_object("Internet_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "columns",
                      json_type_int,
                      errors);
  if (json_columns != nullptr)
    internet_data_source_descriptor->cols = json_object_get_int(json_columns);
  return internet_data_source_descriptor;
}

string Internet_data_source_descriptor::to_string() {
  ostringstream os;
  os << Data_source_descriptor::to_string()
     << " url " << url
     << " depth " << depth
     << " rows " << rows
     << " cols " << cols;
  return os.str();
}
