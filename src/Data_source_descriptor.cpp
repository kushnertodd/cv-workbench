//
// Created by kushn on 6/11/2022.
//

#include <sstream>
#include "wb_utils.hpp"
#include "data_source_descriptor.hpp"

Data_source_descriptor::~Data_source_descriptor() = default;
Data_source_descriptor::Data_source_descriptor(int m_id, cv_enums::CV_repository_type m_repository_type,
                                               cv_enums::CV_data_type m_cv_data_type) :
    id(m_id),
    repository_type(m_repository_type),
    data_type(m_cv_data_type) {}

std::string Data_source_descriptor::to_string() {
  std::ostringstream os;
  os << "id " << id
     << " repository '" << wb_utils::repository_type_enum_to_string(repository_type)
     << "' data type '" << wb_utils::data_type_enum_to_string(data_type) << "'";
  return os.str();
}