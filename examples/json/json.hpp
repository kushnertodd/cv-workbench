#ifndef CV_WORKBENCH_CONFIG_JSON_H_
#define CV_WORKBENCH_CONFIG_JSON_H_
#include <exception>

class json_exception {
 private:
  std::string errmsg;
  std::string filename;
 public:
  json_exception(std::string m_errmsg, std::string m_filename);
  virtual const char *what() const noexcept;
};

class json {
 private:
  std::string text;
 public:
  void read(std::string  filename);
  void parse();
};

#endif //CV_WORKBENCH_CONFIG_JSON_H_
