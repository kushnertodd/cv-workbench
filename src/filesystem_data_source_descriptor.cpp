//
// Created by kushn on 6/11/2022.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "filesystem_data_source_descriptor.hpp"

extern bool debug;

using namespace std;

Filesystem_data_source_descriptor::Filesystem_data_source_descriptor(int m_id,
                                                                     Cv_data_type_enum m_cv_data_type_enum) :
    Data_source_descriptor(m_id, FILESYSTEM, m_cv_data_type_enum) {}
string Filesystem_data_source_descriptor::read_json(Errors &errors) {return "";}

Image *Filesystem_data_source_descriptor::read_image(Errors &errors) {
  string path =(directory == "" ? "" : directory + "/") + filename + "." + ext;
  if (file_format == BINARY) {
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == nullptr) {
      errors.add("Filesystem_data_source_descriptor::read_image: invalid file '" + path + "'");
      return nullptr;
    }
    int rows;
    size_t newLen;
    newLen = fread(&rows, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
      errors.add("Filesystem_data_source_descriptor::read_image: missing image rows in '" + path + "'");
      return nullptr;
    }
    int cols;
    newLen = fread(&cols, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
      errors.add("Filesystem_data_source_descriptor::read_image: missing image cols in '" + path + "'");
      return nullptr;
    }
    int components;
    newLen = fread(&components, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
      errors.add("Filesystem_data_source_descriptor::read_image: missing image components in '" + path + "'");
      return nullptr;
    }
    Image *image = Image::create_image_allocated_buffer(rows, cols, components);

    // Read the data into buffer.
    newLen = fread(image->buf, sizeof(char), image->nbytes, fp);
    if (ferror(fp) != 0) {
      errors.add("Filesystem_data_source_descriptor::read_image: cannot read image data in '" + path + "'");
      return nullptr;
    }
    fclose(fp);
    return image;
  } else if (file_format == JPEG) {
    return nullptr;
  }
}

Histogram *Filesystem_data_source_descriptor::read_histogram(Errors &errors) {return nullptr;}
Hough *Filesystem_data_source_descriptor::read_hough(Errors &errors) {return nullptr;}
void Filesystem_data_source_descriptor::write_json(string & json, Errors & errors) {}

void Filesystem_data_source_descriptor::write_image(Image *image, Errors &errors) {
  string path =      (directory == "" ? "" : directory + "/")          + filename + "." + ext;
  if (file_format == BINARY) {

  } else if (file_format == JPEG) {

  }
}

void Filesystem_data_source_descriptor::write_histogram(Histogram * histogram, Errors & errors) {}
void Filesystem_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {}
Filesystem_data_source_descriptor *Filesystem_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                                                                 int id,
                                                                                 Cv_data_type_enum cv_data_type_enum,
                                                                                 Errors &errors) {
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
  else
    filesystem_data_source_descriptor->directory = "";

  json_object *json_filename =
      get_json_object("Filesystem_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "filename",
                      json_type_string,
                      errors);
  if (json_filename != nullptr)
    filesystem_data_source_descriptor->filename = json_object_get_string(json_filename);

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
