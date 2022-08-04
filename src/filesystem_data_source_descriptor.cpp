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
#include "filesystem_data_source_descriptor.hpp"

extern bool debug;

Filesystem_data_source_descriptor::Filesystem_data_source_descriptor(int m_id,
                                                                     WB_data_type::Data_type m_data_type,
                                                                     WB_data_format::Data_format m_data_format) :
    Data_source_descriptor(m_id,
                           m_data_type,
                           m_data_format,
                           WB_repository_type::Repository_type::FILESYSTEM) {}

Filesystem_data_source_descriptor
*Filesystem_data_source_descriptor::from_json(json_object *json_data_source_descriptor,
                                              int id,
                                              WB_data_type::Data_type data_type,
                                              WB_data_format::Data_format data_format,
                                              Errors &errors) {
  if (debug)
    std::cout << "Filesystem_data_source_descriptor::from_json: id '" << id << "' type "
              << std::endl;
  auto *filesystem_data_source_descriptor =
      new Filesystem_data_source_descriptor(id, data_type, data_format);

  // parse: ' "directory": ... `
  json_object *json_directory =
      get_json_object("Filesystem_data_source_descriptor::from_json",
                      json_data_source_descriptor,
                      "directory",
                      json_type_string,
                      errors);
  if (json_directory != nullptr)
    filesystem_data_source_descriptor->directory = json_object_get_string(json_directory);
  else
    filesystem_data_source_descriptor->directory = ".";

  // parse: ' "filename": ... `
  json_object *json_filename =
      get_json_object("Filesystem_data_source_descriptor::from_json",
                      json_data_source_descriptor,
                      "filename",
                      json_type_string,
                      errors);
  if (json_filename != nullptr)
    filesystem_data_source_descriptor->filename = json_object_get_string(json_filename);
  else
    errors.add("Filesystem_data_source_descriptor::from_json", "", "missing required filename");

  // parse: ' "ext": ... `
  json_object *json_ext =
      get_json_object("Filesystem_data_source_descriptor::from_json",
                      json_data_source_descriptor,
                      "ext",
                      json_type_string,
                      errors, true);
  if (json_ext != nullptr)
    filesystem_data_source_descriptor->ext = json_object_get_string(json_ext);
  else
    filesystem_data_source_descriptor->ext =
        WB_data_format::to_ext(filesystem_data_source_descriptor->data_format);
  return filesystem_data_source_descriptor;
}

Histogram *Filesystem_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }

Hough *Filesystem_data_source_descriptor::read_hough(Errors &errors) {
  std::string path = to_path();
  FILE *fp = file_utils::open_file_read(path, errors);
  Hough *hough = nullptr;
  if (fp) {
    hough = Hough::read(fp, errors);
    fclose(fp);
  }
  return hough;
}

Image *Filesystem_data_source_descriptor::read_image(Errors &errors) {
  std::string path = to_path();
  FILE *fp = file_utils::open_file_read(path, errors);
  Image *image = nullptr;
  if (fp) {
    image = Image::read(fp, errors);
    fclose(fp);
  }
  return image;
}

Image *Filesystem_data_source_descriptor::read_image_jpeg(Errors &errors) {
  std::string path = to_path();
  return Image::read_jpeg(path, errors);
}

std::string Filesystem_data_source_descriptor::read_json(Errors &errors) { return ""; }

Hough *read_text(std::ifstream &ifs, Errors &errors) {
  return nullptr;
}

std::string Filesystem_data_source_descriptor::to_path() const {
  return to_path_noext() + "." + ext;
}

std::string Filesystem_data_source_descriptor::to_path_noext() const {
  return (directory.empty() ? "" : directory + "/") + filename;
}

std::string Filesystem_data_source_descriptor::to_string() {
  std::ostringstream os;
  os << Data_source_descriptor::to_string()
     << " file format '" << WB_data_format::to_string(data_format)
     << "' directory '" << directory
     << "' filename '" << filename
     << "' ext '" << ext << "'";
  return os.str();
}

void Filesystem_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {
  std::string path = to_path_noext();
  Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::BINARY);
  std::string data_filename = wb_filename.to_hist();
  FILE *fp = file_utils::open_file_write(data_filename, errors);
  if (fp) {
    histogram->write(fp, errors);
    fclose(fp);
  }
}

void Filesystem_data_source_descriptor::write_histogram_text(Histogram *histogram, Errors &errors) {
  std::string path = to_path_noext();
  histogram->write_text(path, "\t", errors);
}

void Filesystem_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {
  std::string path = to_path();
  FILE *fp = file_utils::open_file_write(path, errors);
  if (fp) {
    hough->write(fp, errors);
    fclose(fp);
  }
}

void Filesystem_data_source_descriptor::write_hough_text(Hough *hough, Errors &errors) {
  std::string path = to_path();
  std::ofstream ofs = file_utils::open_file_write_text(path, errors);
  if (ofs) {
    hough->write_text(ofs, "\t", errors);
    ofs.close();
  }
}

void Filesystem_data_source_descriptor::write_hough_peaks(Hough *hough, Errors &errors) {

}

void Filesystem_data_source_descriptor::write_hough_peaks_text(Hough *hough, Errors &errors) {

}

void Filesystem_data_source_descriptor::write_image(Image *image, Errors &errors) {
  std::string path = to_path();
  FILE *fp = file_utils::open_file_write(path, errors);
  if (fp) {
    image->write(fp, errors);
    fclose(fp);
  }
}

void Filesystem_data_source_descriptor::write_image_text(Image *image, Errors &errors) {
  std::string path = to_path();
  std::ofstream ofs = file_utils::open_file_write_text(path, errors);
  if (ofs) {
    image->write_text(ofs, "\t", errors);
    ofs.close();
  }
}

void Filesystem_data_source_descriptor::write_image_jpeg(Image *image, Errors &errors) {
  std::string path = to_path();
  image->write_jpeg(path, errors);
}

void Filesystem_data_source_descriptor::write_json(std::string &json, Errors &errors) {}

