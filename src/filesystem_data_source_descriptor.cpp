//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_json_utils.hpp"
#include "wb_utils.hpp"
#include "data_source_descriptor.hpp"
#include "filesystem_data_source_descriptor.hpp"

extern bool debug;

using namespace std;

Filesystem_data_source_descriptor::Filesystem_data_source_descriptor(int m_id,
                                                                     Cv_data_type_enum m_cv_data_type_enum) :
    Data_source_descriptor(m_id, FILESYSTEM, m_cv_data_type_enum) {}
string Filesystem_data_source_descriptor::read_json(Errors &errors) { return ""; }

Image *Filesystem_data_source_descriptor::read_image(Errors &errors) {
  string path = (directory == "" ? "" : directory + "/") + filename + "." + ext;
  switch (file_format) {
    case BINARY:
      return Image::read_binary(path, errors);
      break;
    case JPEG:
      return Image::read_jpeg(path, errors);
      break;
    default:
      return nullptr;
  }
}

Histogram *Filesystem_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }
Hough *Filesystem_data_source_descriptor::read_hough(Errors &errors) { return nullptr; }
void Filesystem_data_source_descriptor::write_json(string &json, Errors &errors) {}

void Filesystem_data_source_descriptor::write_image(Image *image, Errors &errors) {
  string path = (directory == "" ? "" : directory + "/") + filename + "." + ext;
  switch (file_format) {
    case BINARY:
      image->write_binary(path, errors);
      break;
    case JPEG:
      image->write_jpeg(path, errors);
      break;
    default:
      break;
  }
}

void Filesystem_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {}
void Filesystem_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {}
Filesystem_data_source_descriptor *Filesystem_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                                                                 int id,
                                                                                 Cv_data_type_enum data_type,
                                                                                 Errors &errors) {
  if (debug)
    cout << "Filesystem_data_source_descriptor::json_parse: id '" << id << "' type "
         << data_type << endl;
  Filesystem_data_source_descriptor *filesystem_data_source_descriptor =
      new Filesystem_data_source_descriptor(id, data_type);

  json_object *json_file_format =
      get_json_object("Filesystem_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "format",
                      json_type_string,
                      errors);
  if (json_file_format != nullptr) {
    string file_format_str = json_object_get_string(json_file_format);
    Cv_image_file_format_enum file_format =
        Workbench_utils::string_to_file_format_enum(file_format_str);
    if (file_format == UNDEFINED_FILE_FORMAT)
      errors.add("Filesystem_data_source_descriptor::json_parse: invalid file format '" + file_format_str + "'");
    else
      filesystem_data_source_descriptor->file_format = file_format;
  }
  json_object *json_directory =
      get_json_object("Filesystem_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "directory",
                      json_type_string,
                      errors);
  if (json_directory != nullptr)
    filesystem_data_source_descriptor->directory = json_object_get_string(json_directory);
  else
    filesystem_data_source_descriptor->directory = ".";

  json_object *json_filename =
      get_json_object("Filesystem_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "filename",
                      json_type_string,
                      errors);
  if (json_filename != nullptr)
    filesystem_data_source_descriptor->filename = json_object_get_string(json_filename);
  else
    errors.add("Filesystem_data_source_descriptor::json_parse: missing required filename");

  json_object *json_ext =
      get_json_object("Filesystem_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "ext",
                      json_type_string,
                      errors);
  if (json_ext != nullptr)
    filesystem_data_source_descriptor->ext = json_object_get_string(json_ext);
  else
    filesystem_data_source_descriptor->ext = "jpg";

  return filesystem_data_source_descriptor;
}

string Filesystem_data_source_descriptor::to_string() {
  ostringstream os;
  os << Data_source_descriptor::to_string()
     << " file format '" << Workbench_utils::file_format_to_string(file_format)
     << "' directory '" << directory
     << "' filename '" << filename
     << "' ext '" << ext << "'";
  return os.str();
}

