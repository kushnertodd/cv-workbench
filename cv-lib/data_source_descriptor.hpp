//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_
#define CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_

#include <json-c/json.h>
#include <string>
#include "wb_defs.hpp"
#include "histogram.hpp"
#include "hough.hpp"
#include "image.hpp"

class Data_source_descriptor {
 public:
  int id{};
  WB_data_type::Data_type data_type{};
  WB_data_format::Data_format data_format{};
  WB_repository_type::Repository_type repository_type{};
  virtual ~Data_source_descriptor();
  Data_source_descriptor(int m_id,
                         WB_data_type::Data_type m_data_type,
                         WB_data_format::Data_format m_data_format,
                         WB_repository_type::Repository_type m_repository_type);
  static Data_source_descriptor *from_json(json_object *json_data_source_descriptor, Errors &errors);
  virtual Histogram *read_histogram(Errors &errors) = 0;
  //  virtual Histogram *read_histogram_text(Errors &errors) = 0;
  virtual Hough *read_hough(Errors &errors) = 0;
  //  virtual Hough *read_hough_text(Errors &errors) = 0;
  virtual Image *read_image(Errors &errors) = 0;
  virtual Image *read_image_jpeg(Errors &errors) = 0;
  virtual Image *read_image_text(Errors &errors) = 0;
  virtual std::string read_json(Errors &errors) = 0;
  Histogram *read_operator_histogram(const std::string &module, Errors &errors);
  Hough *read_operator_hough(const std::string &module, Errors &errors);
  Image *read_operator_image(const std::string &module, Errors &errors);
  virtual std::string to_string();
  virtual void write_histogram(Histogram *histogram, Errors &errors) = 0;
  virtual void write_histogram_text(Histogram *histogram, Errors &errors) = 0;
  virtual void write_hough(Hough *hough, Errors &errors) = 0;
  virtual void write_hough_text(Hough *hough, Errors &errors) = 0;
  virtual void write_hough_peaks(Hough *hough, Errors &errors) = 0;
  virtual void write_hough_peaks_text(Hough *hough, Errors &errors) = 0;
  virtual void write_image(Image *image, Errors &errors) = 0;
  virtual void write_image_jpeg(Image *image, Errors &errors) = 0;
  virtual void write_image_text(Image *image, Errors &errors) = 0;
  virtual void write_json(std::string &json, Errors &errors) = 0;
  void write_operator_histogram(Histogram *output, const std::string &module, Errors &errors);
  void write_operator_hough(Hough *output, const std::string &module, Errors &errors);
  void write_operator_image(Image *output, const std::string &module, Errors &errors);
};

#endif //CV_WORKBENCH_SRC_DATA_SOURCE_DESCRIPTOR_HPP_
