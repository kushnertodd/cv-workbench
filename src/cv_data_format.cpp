//
// Created by kushn on 7/27/2022.
//

#include "cv_data_format.hpp"

const std::map<CV_data_format::Data_format, std::string> CV_data_format::to_exts =
    {
        {CV_data_format::Data_format::BINARY, "bin"},
        {CV_data_format::Data_format::JPEG, "jpg"},
        {CV_data_format::Data_format::JSON, "json"},
        {CV_data_format::Data_format::LOG, "log"},
        {CV_data_format::Data_format::TEXT, "txt"}
    };
const std::map<CV_data_format::Data_format, std::string> CV_data_format::to_strings =
    {
        {CV_data_format::Data_format::BINARY, "bin"},
        {CV_data_format::Data_format::JPEG, "jpeg"},
        {CV_data_format::Data_format::JSON, "json"},
        {CV_data_format::Data_format::LOG, "log"},
        {CV_data_format::Data_format::TEXT, "text"}
    };
const std::map<std::string, CV_data_format::Data_format> CV_data_format::from_exts =
    {
        {"bin", CV_data_format::Data_format::BINARY},
        {"jpg", CV_data_format::Data_format::JPEG},
        {"json", CV_data_format::Data_format::JSON},
        {"log", CV_data_format::Data_format::LOG},
        {"txt", CV_data_format::Data_format::TEXT}
    };
const std::map<std::string, CV_data_format::Data_format> CV_data_format::from_strings =
    {
        {"bin", CV_data_format::Data_format::BINARY},
        {"jpg", CV_data_format::Data_format::JPEG},
        {"json", CV_data_format::Data_format::JSON},
        {"log", CV_data_format::Data_format::LOG},
        {"txt", CV_data_format::Data_format::TEXT}
    };

std::string CV_data_format::to_ext(CV_data_format::Data_format data_format) {
  return CV_data_format::to_exts.at(data_format);
}

std::string CV_data_format::to_string(CV_data_format::Data_format data_format) {
  return CV_data_format::to_strings.at(data_format);
}

CV_data_format::Data_format CV_data_format::from_ext(const std::string &ext) {
  if (CV_data_format::from_exts.count(ext))
    return CV_data_format::from_exts.at(ext);
  else
    return CV_data_format::Data_format::UNDEFINED;
}

CV_data_format::Data_format CV_data_format::from_string(const std::string &text) {
  if (CV_data_format::from_strings.count(text))
    return CV_data_format::from_strings.at(text);
  else
    return CV_data_format::Data_format::UNDEFINED;
}
