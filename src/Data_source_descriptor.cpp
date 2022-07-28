//
// Created by kushn on 6/11/2022.
//

#include <sstream>
#include "cv_data_format.hpp"
#include "cv_data_type.hpp"
#include "cv_repository_type.hpp"
#include "data_source_descriptor.hpp"

Data_source_descriptor::~Data_source_descriptor() = default;
Data_source_descriptor::Data_source_descriptor(int m_id,
                                               CV_data_type::Data_type m_data_type,
                                               CV_data_format::Data_format m_data_format,
                                               CV_repository_type::Repository_type m_repository_type) :
    id(m_id),
    data_type(m_data_type),
    data_format(m_data_format),
    repository_type(m_repository_type) {}

std::string Data_source_descriptor::to_string() {
  std::ostringstream os;
  os << "id " << id
     << "' data format '" << CV_data_type::to_string(data_type)
     << "' data type '" << CV_data_type::to_string(data_type)
     << " repository '" << CV_repository_type::to_string(repository_type)
     << "'";
  return os.str();
}