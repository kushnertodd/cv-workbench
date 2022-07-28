//
// Created by kushn on 7/27/2022.
//

#include "cv_repository_type.hpp"

std::string CV_repository_type::repository_type_enum_to_string(CV_repository_type::type type) {
  switch (type) {
    case CV_repository_type::type::BERKELEY_DB:
      return "Berkeley DB";
    case CV_repository_type::type::FILESYSTEM:
      return "Filesystem";
    case CV_repository_type::type::INTERNET:
      return "Internet";
    case CV_repository_type::type::EXPERIMENT_STEP:
      return "Experiment step";
    default:
      return "unknown repository type";
  }
}

CV_repository_type::type CV_repository_type::string_to_repository_type_enum(const std::string &type) {
  if (type == "berkeley_db") return CV_repository_type::type::BERKELEY_DB;
  else if (type == "filesystem") return CV_repository_type::type::FILESYSTEM;
  else if (type == "internet") return CV_repository_type::type::INTERNET;
  else if (type == "step-output") return CV_repository_type::type::EXPERIMENT_STEP;
  else return CV_repository_type::type::UNDEFINED_REPOSITORY_TYPE;
}
