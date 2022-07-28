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
  std::string directory;
  std::string filename;
  std::string ext;
  Filesystem_data_source_descriptor(int m_id,
                                    CV_data_type::Data_type m_data_type,
                                    CV_data_format::Data_format m_data_format);
  Histogram *read_histogram(Errors &errors) override;
  Hough *read_hough(Errors &errors) override;
  Image *read_image(Errors &errors) override;
  Image *read_image_jpeg(Errors &errors) override;
  std::string read_json(Errors &errors) override;
  void write_histogram(Histogram *histogram, Errors &errors) override;
  void write_histogram_text(Histogram *histogram, Errors &errors) override;
  void write_hough(Hough *hough, Errors &errors) override;
  void write_hough_text(Hough *hough, Errors &errors) override;
  void write_image(Image *image, Errors &errors) override;
  void write_image_jpeg(Image *image, Errors &errors) override;
  void write_image_text(Image *image, Errors &errors) const;
  void write_json(std::string &json, Errors &errors) override;
  static Filesystem_data_source_descriptor
  *json_parse(json_object *json_data_descriptor,
              int id,
              CV_data_type::Data_type data_type,
              CV_data_format::Data_format data_format,
              Errors &errors);
  std::string to_string() override;
};

#endif //CV_WORKBENCH_SRC_FILESYSTEM_DATA_SOURCE_DESCRIPTOR_HPP_
