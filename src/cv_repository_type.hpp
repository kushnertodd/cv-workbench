//
// Created by kushn on 7/27/2022.
//

#ifndef SRC__CV_REPOSITORY_TYPE_HPP_
#define SRC__CV_REPOSITORY_TYPE_HPP_

#include <string>

class CV_repository_type {
 public:
  enum class type {
    BERKELEY_DB, // separate file for each CV_data_type
    FILESYSTEM, // directory, filename
    INTERNET, // endpoint that produced binary data
    EXPERIMENT_STEP, // output of experiment step
    UNDEFINED_REPOSITORY_TYPE
  };
 static  std::string repository_type_enum_to_string(CV_repository_type::type type);
  static  CV_repository_type::type string_to_repository_type_enum(const std::string &type);

};

#endif //SRC__CV_REPOSITORY_TYPE_HPP_
