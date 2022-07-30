//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_data_format.hpp"
#include "wb_data_type.hpp"
#include "wb_repository_type.hpp"
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "experiment_step_data_source_descriptor.hpp"

extern bool debug;

//

Experiment_step_data_source_descriptor::Experiment_step_data_source_descriptor(int m_id,
                                                                               WB_data_type::Data_type m_data_type,
                                                                               WB_data_format::Data_format m_data_format) :
    Data_source_descriptor(m_id, m_data_type, m_data_format, WB_repository_type::Repository_type::EXPERIMENT_STEP),
    step_id(0),
    ref_id(0) {}

Histogram *Experiment_step_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }
Hough *Experiment_step_data_source_descriptor::read_hough(Errors &errors) { return nullptr; }
Image *Experiment_step_data_source_descriptor::read_image(Errors &errors) { return nullptr; }
Image *Experiment_step_data_source_descriptor::read_image_jpeg(Errors &errors) { return nullptr; }
std::string Experiment_step_data_source_descriptor::read_json(Errors &errors) { return ""; }
void Experiment_step_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {}
void Experiment_step_data_source_descriptor::write_histogram_text(Histogram *histogram, Errors &errors) {}
void Experiment_step_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {}
void Experiment_step_data_source_descriptor::write_hough_text(Hough *hough, Errors &errors) {}
void Experiment_step_data_source_descriptor::write_image(Image *image, Errors &errors) {}
void Experiment_step_data_source_descriptor::write_image_jpeg(Image *image, Errors &errors) {}
void Experiment_step_data_source_descriptor::write_json(std::string &json, Errors &errors) {}

Experiment_step_data_source_descriptor
*Experiment_step_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                                    int id,
                                                    WB_data_type::Data_type data_type,
                                                    WB_data_format::Data_format data_format,
                                                    Errors &errors) {
  if (debug)
    std::cout << "Experiment_step_data_source_descriptor::from_json: id '" << id << "' type "
              << std::endl;
  auto *experiment_step_data_source_descriptor =
      new Experiment_step_data_source_descriptor(id, data_type, data_format);
  json_object *json_step_id =
      get_json_object("Experiment_step_data_source_descriptor::from_json",
                      json_data_descriptor,
                      "step-id",
                      json_type_int,
                      errors);
  if (json_step_id != nullptr)
    experiment_step_data_source_descriptor->step_id = json_object_get_int(json_step_id);
  json_object *json_ref_id =
      get_json_object("Experiment_step_data_source_descriptor::from_json",
                      json_data_descriptor,
                      "ref-id",
                      json_type_int,
                      errors);
  if (json_ref_id != nullptr)
    experiment_step_data_source_descriptor->ref_id = json_object_get_int(json_ref_id);
  return experiment_step_data_source_descriptor;
}

std::string Experiment_step_data_source_descriptor::to_string() {
  std::ostringstream os;
  os << Data_source_descriptor::to_string()
     << " step id " << step_id
     << " ref id " << ref_id;
  return os.str();
}