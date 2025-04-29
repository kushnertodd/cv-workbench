#include "experiment_step.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include "data_source_descriptor.hpp"
#include "operator.hpp"
#include "operator_dispatcher.hpp"
#include "wb_data_type.hpp"
#include "wb_json_utils.hpp"

extern bool debug;

Experiment_step::~Experiment_step() {
    for (Data_source_descriptor *descriptor: input_data_sources) {
        delete descriptor;
    }
    for (Data_source_descriptor *descriptor: output_data_stores) {
        delete descriptor;
    }
}
Experiment_step::Experiment_step() : id(0), json_experiment_step(nullptr) {}
Experiment_step::Experiment_step(json_object *m_json_experiment_step) :
    id(0), json_experiment_step(m_json_experiment_step) {}
Experiment_step::Experiment_step(int m_id, std::string m_operator_name) :
    id(m_id), operator_name(std::move(m_operator_name)), json_experiment_step(nullptr) {}
/**
 * Parse experiment json
 * @param jobj  json-c parsed json
 * @param errors experiment parse errors
 */
Experiment_step *Experiment_step::from_json(json_object *json_experiment_step, Errors &errors) {
    // parse: ' { "id": ... `
    json_object *json_id =
            get_json_object("Experiment_step::from_json", json_experiment_step, "id", json_type_int, errors);
    json_object *json_operator =
            get_json_object("Experiment_step::from_json", json_experiment_step, "operator", json_type_string, errors);
    json_object *json_input_data = get_json_object("Experiment_step::from_json", json_experiment_step, "input-data",
                                                   json_type_array, errors, true);
    json_object *json_output_data =
            get_json_object("Experiment_step::from_json", json_experiment_step, "output-data", json_type_array, errors);
    json_object *json_parameters =
            get_json_object("Experiment_step::from_json", json_experiment_step, "parameters", json_type_object, errors);
    auto *experiment_step = new Experiment_step(json_experiment_step);
    if (json_id != nullptr)
        experiment_step->id = json_object_get_int(json_id);
    if (json_operator != nullptr)
        experiment_step->operator_name = json_object_get_string(json_operator);
    // parse input data array
    if (json_input_data != nullptr) {
        size_t nsteps = json_object_array_length(json_input_data);
        for (int i = 0; i < nsteps; i++) {
            json_object *json_input_data_descriptor = json_object_array_get_idx(json_input_data, i);
            if (json_input_data_descriptor != nullptr) {
                if (error_check_type("Experiment_step::from_json", "input-data descriptor", json_input_data_descriptor,
                                     json_type_object, errors)) {
                    Data_source_descriptor *input_data_store_descriptor =
                            Data_source_descriptor::from_json(json_input_data_descriptor, errors);
                    if (input_data_store_descriptor != nullptr)
                        experiment_step->input_data_sources.push_back(input_data_store_descriptor);
                }
            }
        }
    }
    // parse output data array
    if (json_output_data != nullptr) {
        size_t nsteps = json_object_array_length(json_output_data);
        for (int i = 0; i < nsteps; i++) {
            json_object *json_output_data_descriptor = json_object_array_get_idx(json_output_data, i);
            if (error_check_type("Experiment_step::from_json", "output-data descriptor", json_output_data_descriptor,
                                 json_type_object, errors)) {
                Data_source_descriptor *output_data_store_descriptor =
                        Data_source_descriptor::from_json(json_output_data_descriptor, errors);
                if (output_data_store_descriptor != nullptr)
                    experiment_step->output_data_stores.push_back(output_data_store_descriptor);
            }
        }
    }
    // parse parameters
    if (json_parameters != nullptr) {
        if (debug)
            std::cout << "json_parameters type = '" << json_type_to_name(json_object_get_type(json_parameters)) << "'"
                      << std::endl;
        if (error_check_type("Experiment_step::from_json", "parameters", json_parameters, json_type_object, errors)) {
            json_object_object_foreach(json_parameters, key, val) {
                json_type type = json_object_get_type(val);
                if (type == json_type_string) {
                    std::string val_str = json_object_get_string(val);
                    experiment_step->operator_parameters[key] = val_str;
                } else {
                    errors.add("Experiment_step::from_json", "",
                               "invalid parameter type '" + std::string(json_type_to_name(type)) + "' for key '" +
                                       std::string(key) + "'");
                }
            }
        }
    }
    return experiment_step;
}
void Experiment_step::log_experiment_step(const std::list<WB_log_entry> &log_entries, Errors &errors) const {
    if (errors.has_error()) {
        json_object *json_error_list = json_object_new_array();
        for (const std::string &error: errors.error_list) {
            json_object_array_add(json_error_list, json_object_new_string(error.c_str()));
        }
        json_object_object_add(json_experiment_step, "errors", json_error_list);
    } else if (!log_entries.empty()) {
        json_object *json_log_entry_list = json_object_new_object();
        for (const WB_log_entry &log_entry: log_entries) {
            json_object_object_add(json_log_entry_list, log_entry.item.c_str(),
                                   json_object_new_string(log_entry.value.c_str()));
        }
        json_object_object_add(json_experiment_step, "results", json_log_entry_list);
    }
}
void Experiment_step::run(Errors &errors) {
    Operator *step_operator = Operator_dispatcher::create_operator(operator_name);
    if (step_operator == nullptr) {
        if (debug)
            std::cout << "Experiment_step::run: invalid operator '" + operator_name + "'" << std::endl;
        errors.add("Experiment_step::run", "", "invalid operator '" + operator_name + "'");
    } else {
        if (debug) {
            for (Data_source_descriptor *input_data_source: input_data_sources) {
                std::cout << "Experiment_step::run input_data_source: " << input_data_source->to_string() << std::endl;
            }
            for (Data_source_descriptor *output_data_store: output_data_stores) {
                std::cout << "Experiment_step::run output_data_store: " << output_data_store->to_string() << std::endl;
            }
            std::cout << "Experiment_step::run operator_parameters: " << std::endl;
            String_map::iterator it;
            for (it = operator_parameters.begin(); it != operator_parameters.end(); it++) {
                std::cout << it->first // string (key)
                          << ':' << it->second // string's value
                          << std::endl;
            }
        }
        std::list<WB_log_entry> log_entries;
        step_operator->run(input_data_sources, output_data_stores, operator_parameters, log_entries, errors);
        log_experiment_step(log_entries, errors);
        delete step_operator;
    }
}
std::string Experiment_step::to_string() {
    std::ostringstream os;
    os << "Experiment_step::run: id " << id << " operator " << operator_name << std::endl;
    os << "Experiment_step::run: input data sources" << std::endl;
    for (Data_source_descriptor *descriptor: input_data_sources) {
        if (descriptor != nullptr)
            os << "   " << descriptor->to_string() << std::endl;
    }
    std::cout << "Experiment_step::run: output data stores" << std::endl;
    for (Data_source_descriptor *descriptor: output_data_stores) {
        if (descriptor != nullptr)
            os << "   " << descriptor->to_string() << std::endl;
    }
    return os.str();
}
