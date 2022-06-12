//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_
#define CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_

#include <string>
#include "wb_enums.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "image.hpp"

using namespace std;

class Data_source_descriptor {
 public:
  int id;
  Repository_type_enum repository_type;
  Cv_data_type_enum data_type;
  Data_source_descriptor(int m_id, Repository_type_enum m_repository_type,
                         Cv_data_type_enum m_cv_data_type_enum);
  virtual void read(string json);
  virtual void read(Image *image);
  virtual void read(Histogram *histogram);
  virtual void read(Hough *hough);
  virtual void write(string json);
  virtual void write(Image *image);
  virtual void write(Histogram *histogram);
  virtual void write(Hough *hough);
  virtual string toString();
};

#endif //CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_
