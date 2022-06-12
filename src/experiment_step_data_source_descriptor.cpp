//
// Created by kushn on 6/11/2022.
//

#include <iostream>
#include <sstream>
#include "wb_json_utils.hpp"
#include "data_source_descriptor.hpp"
#include "experiment_step_data_source_descriptor.hpp"

extern bool debug;

using namespace std;

Experiment_step_data_source_descriptor::Experiment_step_data_source_descriptor(int m_id,
                                                                               Cv_data_type_enum m_cv_data_type_enum) :
    Data_source_descriptor(m_id, EXPERIMENT_STEP, m_cv_data_type_enum) {}
string Experiment_step_data_source_descriptor::read_json(Errors &errors) { return nullptr; }
Image *Experiment_step_data_source_descriptor::read_image(Errors &errors) { return nullptr; }
Histogram *Experiment_step_data_source_descriptor::read_histogram(Errors &errors) { return nullptr; }
Hough *Experiment_step_data_source_descriptor::read_hough(Errors &errors) { return nullptr; }
void Experiment_step_data_source_descriptor::write_json(string &json, Errors &errors) {}
void Experiment_step_data_source_descriptor::write_image(Image *image, Errors &errors) {}
void Experiment_step_data_source_descriptor::write_histogram(Histogram *histogram, Errors &errors) {}
void Experiment_step_data_source_descriptor::write_hough(Hough *hough, Errors &errors) {}
Experiment_step_data_source_descriptor *Experiment_step_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                                                                           int id,
                                                                                           Cv_data_type_enum data_type,
                                                                                           Errors &errors) {
  if (debug)
    cout << "Experiment_step_data_source_descriptor::json_parse: id '" << id << "' type "
         << data_type << endl;
  Experiment_step_data_source_descriptor *experiment_step_data_source_descriptor =
      new Experiment_step_data_source_descriptor(id, data_type);
  json_object *json_step_id =
      get_json_object("Experiment_step_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "step-id",
                      json_type_int,
                      errors);
  if (json_step_id != nullptr)
    experiment_step_data_source_descriptor->step_id = json_object_get_int(json_step_id);
  json_object *json_ref_id =
      get_json_object("Experiment_step_data_source_descriptor::json_parse",
                      json_data_descriptor,
                      "ref-id",
                      json_type_int,
                      errors);
  if (json_ref_id != nullptr)
    experiment_step_data_source_descriptor->ref_id = json_object_get_int(json_ref_id);
  return experiment_step_data_source_descriptor;
}

string Experiment_step_data_source_descriptor::toString() {
  ostringstream os;
  os << Data_source_descriptor::toString()
     << " step id " << step_id
     << " ref id " << ref_id;
  return os.str();
}