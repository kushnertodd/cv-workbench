//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "filesystem_data_source_descriptor.hpp"

extern bool debug;

using namespace std;

  Filesystem_data_source_descriptor::Filesystem_data_source_descriptor(int m_id,
                                    Cv_data_type_enum m_cv_data_type_enum) :
      Data_source_descriptor(m_id, FILESYSTEM, m_cv_data_type_enum) {}
  void Filesystem_data_source_descriptor::read(string &json) {}
  void Filesystem_data_source_descriptor::read(Image *image) {

  }
  void Filesystem_data_source_descriptor::read(Histogram *histogram) {}
  void Filesystem_data_source_descriptor::read(Hough *hough) {}
  void Filesystem_data_source_descriptor::write(string &json) {}
  void Filesystem_data_source_descriptor::write(Image *image) {}
  void Filesystem_data_source_descriptor::write(Histogram *histogram) {}
  void Filesystem_data_source_descriptor::write(Hough *hough) {}
   Filesystem_data_source_descriptor *Filesystem_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                                       int id,
                                                       Cv_data_type_enum cv_data_type_enum, Errors &errors) {
    if (debug)
      cout << "Filesystem_data_source_descriptor::json_parse: id '" << id << "' type "
           << cv_data_type_enum << endl;
    Filesystem_data_source_descriptor *filesystem_data_source_descriptor =
        new Filesystem_data_source_descriptor(id, cv_data_type_enum);
    json_object *json_directory =
        get_json_object("Filesystem_data_source_descriptor::json_parse",
                        json_data_descriptor,
                        "directory",
                        json_type_string,
                        errors);
    if (json_directory != nullptr)
      filesystem_data_source_descriptor->directory = json_object_get_string(json_directory);
    json_object *json_filename =
        get_json_object("Filesystem_data_source_descriptor::json_parse",
                        json_data_descriptor,
                        "filename",
                        json_type_string,
                        errors);
    if (json_filename != nullptr)
      filesystem_data_source_descriptor->filename = json_object_get_string(json_filename);
    json_object *json_depth =
        get_json_object("Filesystem_data_source_descriptor::json_parse",
                        json_data_descriptor,
                        "depth",
                        json_type_string,
                        errors);
    if (json_depth != nullptr)
      filesystem_data_source_descriptor->depth = json_object_get_string(json_depth);
    json_object *json_rows =
        get_json_object("Filesystem_data_source_descriptor::json_parse",
                        json_data_descriptor,
                        "rows",
                        json_type_int,
                        errors);
    if (json_rows != nullptr)
      filesystem_data_source_descriptor->rows = json_object_get_int(json_rows);
    json_object *json_columns =
        get_json_object("Filesystem_data_source_descriptor::json_parse",
                        json_data_descriptor,
                        "columns",
                        json_type_int,
                        errors);
    if (json_columns != nullptr)
      filesystem_data_source_descriptor->cols = json_object_get_int(json_columns);
    return filesystem_data_source_descriptor;
  }
