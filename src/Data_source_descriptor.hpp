//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_
#define CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_

#include <string>
#include "wb_defs.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "image.hpp"

using namespace std;

class Data_source_descriptor {
 public:
  int id;
  Cv_repository_type_enum repository_type;
  Cv_data_type_enum data_type;
  virtual ~Data_source_descriptor();
  Data_source_descriptor(int m_id, Cv_repository_type_enum m_repository_type,
                         Cv_data_type_enum m_cv_data_type_enum);
  virtual string read_json(Errors &errors) = 0;
  virtual Image *read_image(Errors &errors) = 0;
  virtual Histogram *read_histogram(Errors &errors) = 0;
  virtual Hough *read_hough(Errors &errors) = 0;
  virtual void write_json(string &json, Errors &errors) = 0;
  virtual void write_image(Image *image, Errors &errors) = 0;
  virtual void write_histogram(Histogram *histogram, Errors &errors) = 0;
  virtual void write_hough(Hough *hough, Errors &errors) = 0;
  virtual string toString();
};

#endif //CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_
