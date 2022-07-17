//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_INTERNET_DATA_SOURCE_DESCRIPTOR_HPP_
#define CV_WORKBENCH_SRC_INTERNET_DATA_SOURCE_DESCRIPTOR_HPP_

#include <string>
#include <json-c/json.h>
#include "wb_defs.hpp"
#include "errors.hpp"
#include "image.hpp"
#include "histogram.hpp"
#include "hough.hpp"

class Internet_data_source_descriptor : public Data_source_descriptor {
 public:
  std::string url;
  std::string depth; // cv_enums::CV_8U, cv_enums::CV_32S, or cv_enums::CV_32F
  int rows;
  int cols;
  Internet_data_source_descriptor(int m_id,
                                  cv_enums::CV_data_type m_cv_data_type);
  std::string read_json(Errors &errors) override;
  Image *read_image(Errors &errors) override;
  Histogram *read_histogram(Errors &errors) override;
  Hough *read_hough(Errors &errors) override;
  void write_json(std::string &json, Errors &errors) override;
  void write_image(Image *image, Errors &errors) override;
  void write_histogram(Histogram *histogram, Errors &errors) override;
  void write_hough(Hough *hough, Errors &errors) override;

  static Internet_data_source_descriptor *json_parse(json_object *json_data_descriptor,
                                                     int id,
                                                     cv_enums::CV_data_type data_type, Errors &errors);

  std::string to_string() override;
};

#endif //CV_WORKBENCH_SRC_INTERNET_DATA_SOURCE_DESCRIPTOR_HPP_
