//
// Created by kushn on 6/21/2022.
//

#include <sstream>
#include "data_source_descriptor.hpp"
#include "operator_utils.hpp"

//

/**
 * find string parameter value and convert to integer:
 * optional && parameter missing -> return false
 * | parameter missing -> return false, error(missing)
 * | parameter non-numeric -> return false, error(format)
 * | t -> return true
 * @param module calling module for error message
 * @param parameters script operation parameters
 * @param parameter operation parameter to convert
 * @param int_value output converted integer value
 * @param errors accumulated errors
 * @param optional permissible for parameter to be missing
 * @return
 */
bool Operator_utils::get_int_parameter(const std::string &module,
                                       String_map &parameters,
                                       const std::string &parameter,
                                       int &int_value,
                                       Errors &errors,
                                       bool optional) {
  if (!has_parameter(parameters, parameter)) {
    if (!optional)
      errors.add(module, "", parameter + " required");
    return false;
  } else {
    std::string parameter_str = get_parameter(parameters, parameter);
    if (!wb_utils::string_to_int(parameter_str, int_value)) {
      errors.add(module, "", "non-integer  " + parameter + ": " + parameter_str);
      return false;
    }
    return true;
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

/**
 * find string parameter value and convert to real number:
 * optional && parameter missing -> return false
 * | parameter missing -> return false, error(missing)
 * | parameter non-numeric -> return false, error(format)
 * | t -> return true
 * @param module calling module for error message
 * @param parameters script operation parameters
 * @param parameter operation parameter to convert
 * @param real_value output converted real value
 * @param errors accumulated errors
 * @param optional permissible for parameter to be missing
 * @return
 */
bool Operator_utils::get_real_parameter(const std::string &module,
                                        String_map &parameters,
                                        const std::string &parameter,
                                        double &real_value,
                                        Errors &errors,
                                        bool optional) {
  if (!has_parameter(parameters, parameter)) {
    if (!optional)
      errors.add(module, "", parameter + " required");
    return false;
  } else {
    std::string parameter_str = get_parameter(parameters, parameter);
    if (!wb_utils::string_to_double(parameter_str, real_value)) {
      errors.add(module, "", "non-real  " + parameter + ": " + parameter_str);
      return false;
    }
    return true;
  }
}

/**
 * find string parameter value and convert to integer:
 * optional && parameter missing -> return false
 * | parameter missing -> return false, error(missing)
 * | t -> return true
 * @param module calling module for error message
 * @param parameters script operation parameters
 * @param parameter operation parameter to convert
 * @param string_value output string value
 * @param errors accumulated errors
 * @param optional permissible for parameter to be missing
 * @return
 */
bool Operator_utils::get_string_parameter(const std::string &module,
                                          String_map &parameters,
                                          const std::string &parameter,
                                          std::string &string_value,
                                          Errors &errors,
                                          bool optional) {
  if (!has_parameter(parameters, parameter)) {
    if (!optional)
      errors.add(module, "", parameter + " required");
    return false;
  }
  string_value = get_parameter(parameters, parameter);
  return true;
}

void Operator_utils::get_subimage_parameters(Image *image,
                                             const std::string &module,
                                             String_map &parameters,
                                             Errors &errors) {
  int min_row;
  bool have_min_row = Operator_utils::get_int_parameter(module, parameters, "min-row", min_row, errors, true);
  int min_col;
  bool have_min_col = Operator_utils::get_int_parameter(module, parameters, "min-col", min_col, errors, true);
  int max_row;
  bool have_max_row = Operator_utils::get_int_parameter(module, parameters, "max-row", max_row, errors, true);
  int max_col;
  bool have_max_col = Operator_utils::get_int_parameter(module, parameters, "max-col", max_col, errors, true);
  if (!errors.has_error() && (have_min_row || have_min_col || have_max_row || have_max_col)) {
    if (!have_min_row) min_row = 0;
    if (!have_min_col) min_col = 0;
    if (!have_max_row) max_row = image->get_rows() - 1;
    if (!have_max_col) max_col = image->get_cols() - 1;
    image->set_subimage(min_row, min_col, max_row, max_col, errors);
  }
}

bool Operator_utils::has_parameter(String_map &parameters, const std::string &parameter) {
  return parameters.find(parameter) != parameters.end();
}

std::string Operator_utils::parameters_to_string(String_map &parameters) {
  std::ostringstream os;
  String_map::iterator it;
  for (it = parameters.begin(); it != parameters.end(); it++) {
    os << it->first    // string (key)
       << ": "
       << it->second
       << std::endl;
  }
  return os.str();
}


