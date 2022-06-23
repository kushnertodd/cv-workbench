//
// Created by kushn on 6/21/2022.
//

#include <sstream>
#include "errors.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"
#include "operator_utils.hpp"

using namespace std;

bool Operator_utils::get_int_parameter(string module,
                                       String_map &parameters,
                                       string parameter,
                                       int &int_value,
                                       Errors &errors) {
  if (!has_parameter(parameters, parameter)) {
    errors.add(module + ": missing '" + parameter + "' parameter");
    return false;
  } else {
    string parameter_str = get_parameter(parameters, parameter);
    if (!Workbench_utils::is_numeric(parameter_str)) {
      errors.add(module + ": not a numeric parameter: '" + parameter_str + "'");
      return false;
    } else if (!Workbench_utils::string_to_int(parameter_str, int_value)) {
      errors.add(module + ": invalid integer parameter: '" + parameter_str + "'");
      return false;
    }
  }
  return true;
}

bool Operator_utils::get_real_parameter(string module,
                                        String_map &parameters,
                                        string parameter,
                                        double &real_value,
                                        Errors &errors) {
  if (!has_parameter(parameters, parameter)) {
    errors.add(module + ": missing '" + parameter + "' parameter");
    return false;
  } else {
    string parameter_str = get_parameter(parameters, parameter);
    if (!Workbench_utils::is_numeric(parameter_str)) {
      errors.add(module + ": not a numeric parameter: '" + parameter_str + "'");
      return false;
    } else if (!Workbench_utils::string_to_real(parameter_str, real_value)) {
      errors.add(module + ": invalid integer parameter: '" + parameter_str + "'");
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
string Operator_utils::get_parameter(String_map &parameters, string parameter) {
  return parameters[parameter];
}

bool Operator_utils::has_parameter(String_map &parameters, string parameter) {
  return parameters.find(parameter) != parameters.end();
}

string Operator_utils::parameters_to_string(String_map &parameters) {
  ostringstream os;
  String_map::iterator it;
  for (it = parameters.begin(); it != parameters.end(); it++) {
    os << "'" << it->first    // string (key)
       << "': '"
       << it->second   // string's value
       << "'";
  }
  return os.str();
}
