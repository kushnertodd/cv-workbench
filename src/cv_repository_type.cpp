//
// Created by kushn on 7/27/2022.
//

#include "cv_repository_type.hpp"

const std::map<CV_repository_type::Repository_type, std::string> CV_repository_type::to_strings =
    {
        {CV_repository_type::Repository_type::BERKELEY_DB, "Berkeley DB"},
        {CV_repository_type::Repository_type::FILESYSTEM, "Filesystem"},
        {CV_repository_type::Repository_type::INTERNET, "Internet"},
        {CV_repository_type::Repository_type::EXPERIMENT_STEP, "Experiment step"}
    };
const std::map<std::string, CV_repository_type::Repository_type> CV_repository_type::from_strings =
    {
        {"Berkeley DB", CV_repository_type::Repository_type::BERKELEY_DB},
        {"Filesystem", CV_repository_type::Repository_type::FILESYSTEM},
        {"Internet", CV_repository_type::Repository_type::INTERNET},
        {"Experiment step", CV_repository_type::Repository_type::EXPERIMENT_STEP}
    };

std::string CV_repository_type::to_string(CV_repository_type::Repository_type repository_type) {
  return CV_repository_type::to_strings.at(repository_type);
}

CV_repository_type::Repository_type CV_repository_type::from_string(const std::string &text) {
  if (CV_repository_type::from_strings.count(text))
    return CV_repository_type::from_strings.at(text);
  else
    return CV_repository_type::Repository_type::UNDEFINED;
}
