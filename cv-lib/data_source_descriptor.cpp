//
// Created by kushn on 6/11/2022.
//

#include <sstream>
#include "berkeley_db_data_source_descriptor.hpp"
#include "filesystem_data_source_descriptor.hpp"
#include "internet_data_source_descriptor.hpp"
#include "wb_json_utils.hpp"

Data_source_descriptor::~Data_source_descriptor() = default;

Data_source_descriptor::Data_source_descriptor(int m_id,
                                               WB_data_type::Data_type m_data_type,
                                               WB_data_format::Data_format m_data_format,
                                               WB_repository_types::Repository_type m_repository_type) :
    id(m_id),
    data_type(m_data_type),
    data_format(m_data_format),
    repository_type(m_repository_type) {}

Data_source_descriptor *Data_source_descriptor::from_json(json_object *json_data_source_descriptor, Errors &errors) {
  Data_source_descriptor *data_source_descriptor = nullptr;

  // parse: ' { "id": ... `
  int id;
  json_object *json_id =
      get_json_object("from_json", json_data_source_descriptor, "id",
                      json_type_int, errors);
  if (json_id != nullptr) {
    id = json_object_get_int(json_id);
  }

  // parse: ' "type": ... `
  WB_data_type::Data_type data_type;
  json_object *json_data_type =
      get_json_object("from_json",
                      json_data_source_descriptor,
                      "type",
                      json_type_string,
                      errors);
  if (json_data_type != nullptr) {
    std::string data_type_str = json_object_get_string(json_data_type);
    data_type = WB_data_type::from_string(data_type_str);
    if (data_type == WB_data_type::Data_type::UNDEFINED)
      errors.add("", "", "invalid data type: " + data_type_str);
  }

  // parse: ' "format": ... `
  WB_data_format::Data_format data_format;
  json_object *json_data_format =
      get_json_object("from_json",
                      json_data_source_descriptor,
                      "format",
                      json_type_string,
                      errors);
  if (json_data_format != nullptr) {
    std::string data_format_str = json_object_get_string(json_data_format);
    data_format =
        WB_data_format::from_string(data_format_str);
    if (data_format == WB_data_format::Data_format::UNDEFINED)
      errors.add("", "", "invalid data format: " + data_format_str);
  }

  // parse: ' "repository": ... `
  json_object *json_repository =
      get_json_object("from_json", json_data_source_descriptor, "repository",
                      json_type_string, errors);
  if (json_repository != nullptr) {
    std::string repository_str = json_object_get_string(json_repository);
    if (repository_str == "berkeley_db") {
      data_source_descriptor =
          Berkeley_db_data_source_descriptor::from_json(
              json_data_source_descriptor, id, data_type, data_format, errors);
    } else if (repository_str == "filesystem") {
      data_source_descriptor =
          Filesystem_data_source_descriptor::from_json(
              json_data_source_descriptor, id, data_type, data_format, errors);
    } else if (repository_str == "internet") {
      data_source_descriptor =
          Internet_data_source_descriptor::from_json(
              json_data_source_descriptor, id, data_type, data_format, errors);
    } else {
      errors.add("", "", "invalid data repository type: " + repository_str);
    }
  }
  return data_source_descriptor;
}

std::string Data_source_descriptor::to_string() {
  std::ostringstream os;
  os << "id " << id
     << "' data format '" << WB_data_type::to_string(data_type)
     << "' data type '" << WB_data_type::to_string(data_type)
     << " repository '" << WB_repository_types::to_string(repository_type)
     << "'";
  return os.str();
}

Histogram *Data_source_descriptor::read_operator_histogram(const std::string &module,
                                                           Errors &errors) {
  Histogram *input = nullptr;
  if (data_format == WB_data_format::Data_format::BINARY)
    input = read_histogram(errors);
  else
    errors.add(module, "", "invalid input data format " + WB_data_format::to_string(data_format));
  return input;
}

Hough *Data_source_descriptor::read_operator_hough(const std::string &module,
                                                   Errors &errors) {
  Hough *input = nullptr;
  if (data_format == WB_data_format::Data_format::BINARY)
    input = read_hough(errors);
  else
    errors.add(module, "", "invalid input data format " + WB_data_format::to_string(data_format));
  return input;
}

Image *Data_source_descriptor::read_operator_image(const std::string &module,
                                                   Errors &errors) {
  Image *input = nullptr;
  if (data_format == WB_data_format::Data_format::BINARY)
    input = read_image(errors);
  else if (data_format == WB_data_format::Data_format::JPEG)
    input = read_image_jpeg(errors);
  else if (data_format == WB_data_format::Data_format::TEXT)
    read_image_text(errors);
  else
    errors.add(module, "", "invalid input data format " + WB_data_format::to_string(data_format));
  return input;
}

void Data_source_descriptor::write_operator_histogram(Histogram *output,
                                                      const std::string &module,
                                                      Errors &errors) {
  if (data_format == WB_data_format::Data_format::BINARY)
    write_histogram(output, errors);
  else if (data_format == WB_data_format::Data_format::TEXT)
    write_histogram_text(output, errors);
  else
    errors.add(module, "", "invalid output data format " + WB_data_format::to_string(data_format));
}

void Data_source_descriptor::write_operator_hough(Hough *output,
                                                  const std::string &module,
                                                  Errors &errors) {
  if (data_format == WB_data_format::Data_format::BINARY)
    write_hough(output, errors);
  else if (data_format == WB_data_format::Data_format::TEXT)
    write_hough_text(output, errors);
  else
    errors.add(module, "", "invalid output data format " + WB_data_format::to_string(data_format));
}

void Data_source_descriptor::write_operator_image(Image *output,
                                                  const std::string &module,
                                                  Errors &errors) {
  if (data_format == WB_data_format::Data_format::BINARY)
    write_image(output, errors);
  else if (data_format == WB_data_format::Data_format::JPEG)
    write_image_jpeg(output, errors);
  else if (data_format == WB_data_format::Data_format::TEXT)
    write_image_text(output, errors);
  else
    errors.add(module, "", "invalid output data format " + WB_data_format::to_string(data_format));
}
