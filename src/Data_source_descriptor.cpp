//
// Created by kushn on 6/11/2022.
//

#include "Data_source_descriptor.hpp"

Data_source_descriptor::Data_source_descriptor(int m_id, Repository_type_enum m_repository_type,
                       Cv_data_type_enum m_cv_data_type_enum) :
    id(m_id),
    repository_type(m_repository_type),
    cv_data_type_enum(m_cv_data_type_enum) {}

void Data_source_descriptor::read(string json) {}
void Data_source_descriptor::read(Image *image) {}
void Data_source_descriptor::read(Histogram *histogram) {}
void Data_source_descriptor::read(Hough *hough) {}
void Data_source_descriptor::write(string json) {}
void Data_source_descriptor::write(Image *image) {}
void Data_source_descriptor::write(Histogram *histogram) {}
void Data_source_descriptor::write(Hough *hough) {}