//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_FILESYSTEM_DATA_SOURCE_DESCRIPTOR_HPP_
#define CV_WORKBENCH_SRC_FILESYSTEM_DATA_SOURCE_DESCRIPTOR_HPP_

#include <string>
#include <json-c/json.h>
#include "data_source_descriptor.hpp"
#include "errors.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "image.hpp"
#include "wb_defs.hpp"

class Filesystem_data_source_descriptor : public Data_source_descriptor {
 public:
  cv_enums::CV_image_file_format file_format;
  std::string directory;
  std::string filename;
  std::string ext;
  Filesystem_data_source_descriptor(int m_id,
                                    cv_enums::CV_data_type m_cv_data_type);
  Histogram *read_histogram(Errors &errors);
  Hough *read_hough(Errors &errors);
  Image *read_image(Errors &errors);
  std::string read_json(Errors &errors);
  void write_histogram(Histogram *histogram, Errors &errors);
  void write_hough(Hough *hough, Errors &errors);
  void write_image(Image *image, Errors &errors);
  void write_json(std::string &json, Errors &errors);
  static Filesystem_data_source_descriptor *json_parse(json_object *json_data_descriptor,
                                                       int id,
                                                       cv_enums::CV_data_type data_type,
                                                       Errors &errors);
  std::string to_string();
};

#endif //CV_WORKBENCH_SRC_FILESYSTEM_DATA_SOURCE_DESCRIPTOR_HPP_
