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

Filesystem_data_source_descriptor::Filesystem_data_source_descriptor(int m_id,
                                                                     cv_enums::CV_data_type m_data_type,
                                                                     cv_enums::CV_data_format m_data_format) :
    Data_source_descriptor(m_id, m_data_type, m_data_format, cv_enums::FILESYSTEM) {}

Histogram *Filesystem_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }

Hough *Filesystem_data_source_descriptor::read_hough(Errors &errors) { return nullptr; }

Image *Filesystem_data_source_descriptor::read_image(Errors &errors) {
  std::string path = (directory.empty() ? "" : directory + "/") + filename + "." + ext;
  return Image::read(path, errors);
}

Image *Filesystem_data_source_descriptor::read_image_jpeg(Errors &errors) {
  std::string path = (directory.empty() ? "" : directory + "/") + filename + "." + ext;
  return Image::read_jpeg(path, errors);
}

std::string Filesystem_data_source_descriptor::read_json(Errors &errors) { return ""; }

void Filesystem_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {}

void Filesystem_data_source_descriptor::write_histogram_text(Histogram *histogram, Errors &errors) {
  std::string path = (directory.empty() ? "" : directory + "/") + filename; // ignore ext + "." + ext;
  histogram->write_text(path, "\t", errors);
}

void Filesystem_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {
  std::string path = (directory.empty() ? "" : directory + "/") + filename + "." + ext;
  hough->write(path, errors);
}

void Filesystem_data_source_descriptor::write_hough_text(Hough *hough, Errors &errors) {
  std::string path = (directory.empty() ? "" : directory + "/") + filename + "." + ext;
  hough->write_text(path, "\t", errors);
}

void Filesystem_data_source_descriptor::write_image(Image *image, Errors &errors) {
  std::string path = (directory.empty() ? "" : directory + "/") + filename + "." + ext;
  image->write(path, errors);
}

void Filesystem_data_source_descriptor::write_image_text(Image *image, Errors &errors) const {
  std::string path = (directory.empty() ? "" : directory + "/") + filename + "." + ext;
  image->write_text(path, "\t", errors);
}

void Filesystem_data_source_descriptor::write_image_jpeg(Image *image, Errors &errors) {
  std::string path = (directory.empty() ? "" : directory + "/") + filename + "." + ext;
  image->write_jpeg(path, errors);
}

void Filesystem_data_source_descriptor::write_json(std::string &json, Errors &errors) {}

Filesystem_data_source_descriptor
*Filesystem_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                               int id,
                                               cv_enums::CV_data_type data_type,
                                               cv_enums::CV_data_format data_format,
                                               Errors &errors) {
  if (debug)
    std::cout << "Filesystem_data_source_descriptor::json_parse: id '" << id << "' type "
              << data_type << std::endl;
  auto *filesystem_data_source_descriptor =
      new Filesystem_data_source_descriptor(id, data_type, data_format);

  // parse: ' "directory": ... `
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

  // parse: ' "filename": ... `
  json_object *json_filename =
      get_json_object("Filesystem_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "filename",
                      json_type_string,
                      errors);
  if (json_filename != nullptr)
    filesystem_data_source_descriptor->filename = json_object_get_string(json_filename);
  else
    errors.add("Filesystem_data_source_descriptor::json_parse", "", "missing required filename");

  // parse: ' "ext": ... `
  json_object *json_ext =
      get_json_object("Filesystem_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "ext",
                      json_type_string,
                      errors, true);
  if (json_ext != nullptr)
    filesystem_data_source_descriptor->ext = json_object_get_string(json_ext);
  else if (filesystem_data_source_descriptor->data_format == cv_enums::JPEG)
    filesystem_data_source_descriptor->ext = "jpg";
  else if (filesystem_data_source_descriptor->data_format == cv_enums::BINARY)
    filesystem_data_source_descriptor->ext = "bin";
  else if (filesystem_data_source_descriptor->data_format == cv_enums::TEXT)
    filesystem_data_source_descriptor->ext = "txt";
  else
    errors.add("Filesystem_data_source_descriptor::json_parse", "", "missing required extension");

  return filesystem_data_source_descriptor;
}

std::string Filesystem_data_source_descriptor::to_string() {
  std::ostringstream os;
  os << Data_source_descriptor::to_string()
     << " file format '" << wb_utils::data_format_enum_to_string(data_format)
     << "' directory '" << directory
     << "' filename '" << filename
     << "' ext '" << ext << "'";
  return os.str();
}

