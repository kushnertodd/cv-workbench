//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_INTERNET_DATA_SOURCE_DESCRIPTOR_HPP_
#define CV_WORKBENCH_SRC_INTERNET_DATA_SOURCE_DESCRIPTOR_HPP_

#include <string>
#include <json-c/json.h>
#include "wb_data_format.hpp"
#include "wb_data_type.hpp"
#include "wb_image_depth.hpp"
#include "wb_repository_type.hpp"
#include "wb_defs.hpp"
#include "errors.hpp"
#include "image.hpp"
#include "histogram.hpp"
#include "hough.hpp"

class Internet_data_source_descriptor : public Data_source_descriptor {
 public:
  std::string url{};
  std::string depth{}; // WB_image_depth::Image_depth::CV_8U, WB_image_depth::Image_depth::CV_32S, or WB_image_depth::Image_depth::CV_32F
  int rows{};
  int cols{};
  Internet_data_source_descriptor(int m_id,
                                  WB_data_type::Data_type m_data_type,
                                  WB_data_format::Data_format data_format);
  Histogram *read_histogram(Errors &errors) override;
  Hough *read_hough(Errors &errors) override;
  Image *read_image(Errors &errors) override;
  Image *read_image_jpeg(Errors &errors) override;
  Image *read_image_text(Errors &errors) override;
  std::string read_json(Errors &errors) override;
  void write_histogram(Histogram *histogram, Errors &errors) override;
  void write_histogram_text(Histogram *histogram, Errors &errors) override;
  void write_hough(Hough *hough, Errors &errors) override;
  void write_hough_text(Hough *hough, Errors &errors) override;
  void write_hough_peaks(Hough *hough, Errors &errors) override;
  void write_hough_peaks_text(Hough *hough, Errors &errors) override;
  void write_image(Image *image, Errors &errors) override;
  void write_image_jpeg(Image *image, Errors &errors) override;
  void write_image_text(Image *image, Errors &errors) override;
  void write_json(std::string &json, Errors &errors) override;
  static Internet_data_source_descriptor
  *from_json(json_object *json_data_source_descriptor,
             int id,
             WB_data_type::Data_type data_type,
             WB_data_format::Data_format data_format,
             Errors &errors);

  std::string to_string() override;
};

#endif //CV_WORKBENCH_SRC_INTERNET_DATA_SOURCE_DESCRIPTOR_HPP_
