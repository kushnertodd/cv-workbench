//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_
#define CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_

#include <string>
#include "wb_defs.hpp"
#include "image.hpp"

//

class Data_source_descriptor {
 public:
  int id;
  cv_enums::CV_repository_type repository_type;
  cv_enums::CV_data_type data_type;
  virtual ~Data_source_descriptor();
  Data_source_descriptor(int m_id, cv_enums::CV_repository_type m_repository_type,
                         cv_enums::CV_data_type m_cv_data_type);
  virtual std::string read_json(Errors &errors) = 0;
  virtual Image *read_image(Errors &errors) = 0;
  virtual void write_json(std::string &json, Errors &errors) = 0;
  virtual void write_image(Image *image, Errors &errors) = 0;
  virtual std::string to_string();
};

#endif //CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_
