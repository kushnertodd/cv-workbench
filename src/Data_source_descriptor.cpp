//
// Created by kushn on 6/11/2022.
//

#include <sstream>
#include "wb_utils.hpp"
#include "Data_source_descriptor.hpp"

Data_source_descriptor::~Data_source_descriptor() {}
Data_source_descriptor::Data_source_descriptor(int m_id, Repository_type_enum m_repository_type,
                                               Cv_data_type_enum m_cv_data_type_enum) :
    id(m_id),
    repository_type(m_repository_type),
    data_type(m_cv_data_type_enum) {}

string Data_source_descriptor::toString() {
  ostringstream os;
  os << "id " << id
     << " repository '" << repository_name_to_string(repository_type)
     << "' data type '" << data_type_to_string(data_type) << "'";
  return os.str();
}