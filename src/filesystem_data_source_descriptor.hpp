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
  Cv_image_file_format_enum file_format;
  string directory;
  string filename;
  string ext;
  Filesystem_data_source_descriptor(int m_id,
                                    Cv_data_type_enum m_cv_data_type_enum);
  string read_json(Errors &errors);
  Image *read_image(Errors &errors);
  Histogram *read_histogram(Errors &errors);
  Hough *read_hough(Errors &errors);
  void write_json(string &json, Errors &errors);
  void write_image(Image *image, Errors &errors);
  void write_histogram(Histogram *histogram, Errors &errors);
  void write_hough(Hough *hough, Errors &errors);
  static Filesystem_data_source_descriptor *json_parse(json_object *json_data_descriptor,
                                                       int id,
                                                       Cv_data_type_enum cv_data_type_enum,
                                                       Errors &errors);
};

#endif //CV_WORKBENCH_SRC_FILESYSTEM_DATA_SOURCE_DESCRIPTOR_HPP_
