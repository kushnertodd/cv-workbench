//
// Created by kushn on 7/27/2022.
//

#include "wb_repository_type.hpp"

const std::map<WB_repository_type::Repository_type, std::string> WB_repository_type::to_strings =
    {
        {WB_repository_type::Repository_type::BERKELEY_DB, "Berkeley DB"},
        {WB_repository_type::Repository_type::FILESYSTEM, "Filesystem"},
        {WB_repository_type::Repository_type::INTERNET, "Internet"}
    };
const std::map<std::string, WB_repository_type::Repository_type> WB_repository_type::from_strings =
    {
        {"Berkeley DB", WB_repository_type::Repository_type::BERKELEY_DB},
        {"Filesystem", WB_repository_type::Repository_type::FILESYSTEM},
        {"Internet", WB_repository_type::Repository_type::INTERNET}
    };

std::string WB_repository_type::to_string(WB_repository_type::Repository_type repository_type) {
  return WB_repository_type::to_strings.at(repository_type);
}

WB_repository_type::Repository_type WB_repository_type::from_string(const std::string &text) {
  if (WB_repository_type::from_strings.count(text))
    return WB_repository_type::from_strings.at(text);
  else
    return WB_repository_type::Repository_type::UNDEFINED;
}
