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
void Experiment_step_data_source_descriptor::read(Image *image) {}
void Experiment_step_data_source_descriptor::read(Histogram *histogram) {}
void Experiment_step_data_source_descriptor::read(Hough *hough) {}
Experiment_step_data_source_descriptor *Experiment_step_data_source_descriptor::json_parse(json_object *json_data_descriptor,
                                                                                           int id,
                                                                                           Cv_data_type_enum cv_data_type_enum,
                                                                                           Errors &errors) {
  if (debug)
    cout << "Experiment_step_data_source_descriptor::json_parse: id '" << id << "' type "
         << cv_data_type_enum << endl;
  Experiment_step_data_source_descriptor *experiment_step_data_source_descriptor =
      new Experiment_step_data_source_descriptor(id, cv_data_type_enum);
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