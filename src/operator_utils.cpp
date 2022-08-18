//
// Created by kushn on 6/21/2022.
//

#include <sstream>
#include "data_source_descriptor.hpp"
#include "operator_utils.hpp"

//

void Operator_utils::get_int_parameter(const std::string &module,
                                       String_map &parameters,
                                       const std::string &parameter,
                                       int &int_value,
                                       Errors &errors) {
  if (!has_parameter(parameters, parameter)) {
    errors.add(module, "", "missing '" + parameter + "' parameter");
  } else {
    std::string parameter_str = get_parameter(parameters, parameter);
    if (!wb_utils::is_numeric(parameter_str)) {
      errors.add(module, "", "not a numeric parameter: '" + parameter_str + "'");
    } else if (!wb_utils::string_to_int(parameter_str, int_value)) {
      errors.add(module, "", "invalid integer parameter: '" + parameter_str + "'");
    }
  }
}

void Operator_utils::get_real_parameter(const std::string &module,
                                        String_map &parameters,
                                        const std::string &parameter,
                                        double &real_value,
                                        Errors &errors) {
  if (!has_parameter(parameters, parameter)) {
    errors.add(module, "", "missing '" + parameter + "' parameter");
  } else {
    std::string parameter_str = get_parameter(parameters, parameter);
    if (!wb_utils::is_numeric(parameter_str)) {
      errors.add(module, "", "not a numeric parameter: '" + parameter_str + "'");
    } else if (!wb_utils::string_to_double(parameter_str, real_value)) {
      errors.add(module, "", "invalid integer parameter: '" + parameter_str + "'");
    }
  }
}

/**
 * parameter value in map
 * @param parameters
 * @param parameter
 * @return empty string '' if parameter not present
 */
std::string Operator_utils::get_parameter(String_map &parameters, const std::string &parameter) {
  return parameters[parameter];
}

bool Operator_utils::has_parameter(String_map &parameters, const std::string &parameter) {
  return parameters.find(parameter) != parameters.end();
}

std::string Operator_utils::parameters_to_string(String_map &parameters) {
  std::ostringstream os;
  String_map::iterator it;
  for (it = parameters.begin(); it != parameters.end(); it++) {
    os << "'" << it->first    // string (key)
       << "': '"
       << it->second   // string's value
       << "'";
  }
  return os.str();
}

void Operator_utils::write_operator_image(Data_source_descriptor *output_data_store,
                                          Image *output,
                                          const std::string &module,
                                          Errors &errors,
                                          bool jpeg_permitted) {
  if (jpeg_permitted && output_data_store->data_format == WB_data_format::Data_format::JPEG)
    output_data_store->write_image_jpeg(output, errors);
  if (!errors.has_error()) {
    if (output_data_store->data_format == WB_data_format::Data_format::BINARY) 
      output_data_store->write_image(output, errors);
    else if (output_data_store->data_format == WB_data_format::Data_format::JPEG) 
      output_data_store->write_image_jpeg(output, errors);
    else
      errors.add(module, "", "only binary and jpeg output data formats supported");
  }
}
