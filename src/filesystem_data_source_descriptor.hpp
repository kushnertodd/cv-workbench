//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_FILESYSTEM_DATA_SOURCE_DESCRIPTOR_HPP_
#define CV_WORKBENCH_SRC_FILESYSTEM_DATA_SOURCE_DESCRIPTOR_HPP_

#include <string>
#include <json-c/json.h>
#include "wb_enums.hpp"
#include "errors.hpp"
#include "image.hpp"
#include "histogram.hpp"
#include "hough.hpp"

class Filesystem_data_source_descriptor : public Data_source_descriptor {
 public:
  string directory;
  string filename;
  Filesystem_data_source_descriptor(int m_id,
                                    Cv_data_type_enum m_cv_data_type_enum);
  void read(string &json);
  void read(Image *image);
  void read(Histogram *histogram);
  void read(Hough *hough);
  void write(string &json);
  void write(Image *image);
  void write(Histogram *histogram);
  void write(Hough *hough);
  static Filesystem_data_source_descriptor *json_parse(json_object *json_data_descriptor,
                                                       int id,
                                                       Cv_data_type_enum cv_data_type_enum, Errors &errors);
};



#endif //CV_WORKBENCH_SRC_FILESYSTEM_DATA_SOURCE_DESCRIPTOR_HPP_
