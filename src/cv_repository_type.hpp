//
// Created by kushn on 7/27/2022.
//

#ifndef SRC__CV_REPOSITORY_TYPE_HPP_
#define SRC__CV_REPOSITORY_TYPE_HPP_

#include <map>
#include <string>

class CV_repository_type {
 public:
  enum class Repository_type {
    BERKELEY_DB, // separate file for each CV_data_type
    FILESYSTEM, // directory, filename
    INTERNET, // endpoint that produced binary data
    EXPERIMENT_STEP, // output of experiment step
    UNDEFINED
  };
  static const std::map<CV_repository_type::Repository_type, std::string> to_strings;
  static const std::map<std::string, CV_repository_type::Repository_type> from_strings;
  static std::string to_string(CV_repository_type::Repository_type repository_type);
  static CV_repository_type::Repository_type from_string(const std::string &text);
};

#endif //SRC__CV_REPOSITORY_TYPE_HPP_
