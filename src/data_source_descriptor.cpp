//
// Created by kushn on 6/11/2022.
//

#include <sstream>
#include "berkeley_db_data_source_descriptor.hpp"
#include "filesystem_data_source_descriptor.hpp"
#include "internet_data_source_descriptor.hpp"
#include "wb_data_format.hpp"
#include "wb_data_type.hpp"
#include "wb_repository_type.hpp"
#include "data_source_descriptor.hpp"
#include "wb_json_utils.hpp"

Data_source_descriptor::~Data_source_descriptor() = default;

Data_source_descriptor::Data_source_descriptor(int m_id,
                                               WB_data_type::Data_type m_data_type,
                                               WB_data_format::Data_format m_data_format,
                                               WB_repository_type::Repository_type m_repository_type) :
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
     << " repository '" << WB_repository_type::to_string(repository_type)
     << "'";
  return os.str();
}