//
// Created by kushn on 6/21/2022.
//

#include <sstream>
#include "errors.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"
#include "operator_utils.hpp"

//

bool Operator_utils::get_int_parameter(const std::string &module,
                                       String_map &parameters,
                                       const std::string &parameter,
                                       int &int_value,
                                       Errors &errors) {
  if (!has_parameter(parameters, parameter)) {
    errors.add(module, "", "missing '" + parameter + "' parameter");
    return false;
  } else {
    std::string parameter_str = get_parameter(parameters, parameter);
    if (!wb_utils::is_numeric(parameter_str)) {
      errors.add(module, "", "not a numeric parameter: '" + parameter_str + "'");
      return false;
    } else if (!wb_utils::string_to_int(parameter_str, int_value)) {
      errors.add(module, "", "invalid integer parameter: '" + parameter_str + "'");
      return false;
    }
  }
  return true;
}

bool Operator_utils::get_real_parameter(const std::string &module,
                                        String_map &parameters,
                                        const std::string &parameter,
                                        double &real_value,
                                        Errors &errors) {
  if (!has_parameter(parameters, parameter)) {
    errors.add(module, "", "missing '" + parameter + "' parameter");
    return false;
  } else {
    std::string parameter_str = get_parameter(parameters, parameter);
    if (!wb_utils::is_numeric(parameter_str)) {
      errors.add(module, "", "not a numeric parameter: '" + parameter_str + "'");
      return false;
    } else if (!wb_utils::string_to_real(parameter_str, real_value)) {
      errors.add(module, "", "invalid integer parameter: '" + parameter_str + "'");
      return false;
    }
  }
  return true;
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
