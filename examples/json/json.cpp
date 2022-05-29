#include <sstream>
#include <cerrno>
#include <cstring>
#include "file_utils.hpp"
#include "json.hpp"

json_exception::json_exception(std::string m_errmsg, std::string m_filename) :
    errmsg(m_errmsg),
    filename(m_filename) {
}

const char *json_exception::what() const noexcept {
  std::ostringstream os;
  os << filename << errno;//<< ": " << strerror(errno);
  return os.str().c_str();
}

void json::read(std::string filename) {
  try {
    text = file_utils_cpp::read_file(filename);
  } catch (int ex) {
    throw new json_exception(strerror(errno), filename);
  }
}

void json::parse() {

}
