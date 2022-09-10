//
// Created by kushn on 6/11/2022.
//

#include <cstring>
#include "errors.hpp"
#include "file_utils.hpp"
#include "hough_accum.hpp"
#include "polar_trig.hpp"
#include "wb_utils.hpp"
#include "wb_window.hpp"

Hough_peak::~Hough_peak() = default;

/**
 *
 * @param m_theta_index
 * @param m_rho_index
 * @param m_theta_index
 * @param m_count
 * @param m_total_difference
 * @param m_percent_difference
 * @return
 */
Hough_peak::Hough_peak(int m_theta,
                       double m_rho,
                       int m_count,
                       int m_total_difference,
                       float m_percent_difference) :
    theta(m_theta),
    rho(m_rho),
    count(m_count),
    total_difference(m_total_difference),
    percent_difference(m_percent_difference) {}

Hough_peak::Hough_peak(int m_theta,
                       double m_rho,
                       int m_count,
                       int m_total_difference,
                       float m_percent_difference) :
    theta(m_theta),
    rho(m_rho),
    count(0),
    total_difference(0),
    percent_difference(0.0) {}

Hough_peak *Hough_peak::get_Hough_peak_from_theta_index_rho(int theta_index,
                                                            double rho,
                                                            int count,
                                                            int total_difference,
                                                            float percent_difference) {
  return new Hough_Peak(Polar_trig::theta_index_to_theta(theta_index),
                        rho, count, total_difference, percent_difference);
}

Hough_peak *Hough_peak::get_Hough_peak_from_theta_rho_index(int theta,
                                                            int rho_index,
                                                            int nrhos,
                                                            int count,
                                                            int total_difference,
                                                            float percent_difference) {

  return new Hough_Peak(theta_index,
                        Polar_trig::rho_index_to_rho(rho_index, nrhos),
                        count, total_difference, percent_difference);
}

Hough_peak *Hough_peak::get_Hough_peak_from_theta_index_rho_index(int theta_index,
                                                                  int rho_index,
                                                                  int nrhos,
                                                                  int count,
                                                                  int total_difference,
                                                                  float percent_difference) {

  return new Hough_Peak(Polar_trig::theta_index_to_theta(theta_index),
                        Polar_trig::rho_index_to_rho(rho_index, nrhos), count,
                        total_difference, percent_difference);
}

inline int Hough_peak::get_rho_index(int nrhos) const {
  return Polar_line::get_rho_index(nrhos);
}

int get_theta_index() const {
  return Polar_trig::theta_index_to_theta(theta_index);
}

Hough_peak *Hough_peak::read(const std::string &path, Errors &errors) {
  FILE *fp = file_utils::open_file_read(path, errors);
  Hough_peak *hough = nullptr;
  if (fp) {
    hough = Hough_peak::read(fp, errors);
    fclose(fp);
  }
  return hough;
}

Hough_peak *Hough_peak::read(FILE *fp, Errors &errors) {
  float rho;
  if (!errors.has_error())
    wb_utils::read_float(fp, rho, "Hough_peak::read", "", "missing rho", errors);
  int theta;
  wb_utils::read_int(fp, theta_index, "Hough_peak::read", "", "missing theta", errors);
  int count;
  if (!errors.has_error())
    wb_utils::read_int(fp, count, "Hough_peak::read", "", "missing count", errors);
  int total_difference;
  if (!errors.has_error())
    wb_utils::read_int(fp, total_difference, "Hough_peak::read", "", "missing total_difference", errors);
  float percent_difference;
  if (!errors.has_error())
    wb_utils::read_float(fp,
                         percent_difference,
                         "Hough_peak::read",
                         "",
                         "missing percent_difference",
                         errors);
  if (errors.has_error())
    return nullptr;
  else
    return new Hough_peak(Polar_trig::theta_index_to_theta(theta_index),
                          rho,
                          count,
                          total_difference,
                          percent);
}

Hough_peak *Hough_peak::read_text(const std::string &path, Errors &errors) {
  std::ifstream ifs = file_utils::open_file_read_text(path, errors);
  if (ifs) {
    Hough_peak *hough_peak = read_text(ifs, errors);
    ifs.close();
    return hough_peak;
  }
  return nullptr;
}

/**
 * convert tab-delimited file to image
 * grayscale only
 * @param ifs
 * @param errors
 * @return
 */
Hough_peak *Hough_peak::read_text(std::ifstream &ifs, Errors &errors) {
  int rows = 0;
  int cols = 0;
  bool first = true;
  std::string line;
  std::vector<std::vector<std::string>> lines;
  for (int count = 1; !errors.has_error() && getline(ifs, line); count++) {
    std::vector<std::string> values = wb_utils::string_split(line);
    if (values.size() < 2)
      errors.add("Hough_peak::read_text", "",
                 "missing values on record " + wb_utils::int_to_string(count));
    else {
      string rho_string = values.get(0);
      string theta_string = values.get(1);
      double rho;
      if (!wb_utils::string_to_double(value, &rho))
        errors.add("Hough_peak::read_text", "",
                   "invalid rho value on record " + wb_utils::int_to_string(count));
    }
    if (!errors.has_error()) {
      int theta;
      if (!wb_utils::string_to_int(value, &theta))
        errors.add("Hough_peak::read_text", "",
                   "invalid theta value on record " + wb_utils::int_to_string(count));
    }
    if (!errors.has_error()) {
      return Hough_peak()
    }
    if (first) {
      first = false;
      cols = (int) values.size();
      lines.push_back(values);
    } else if (values.size() != cols) {
      std::ostringstream os;
      os << "invalid image file: initial column length " << cols
         << " row " << rows << " column length " << values.size();
      errors.add("Image::read_text", "", os.str());
      return nullptr;
    } else
      lines.push_back(values);
    rows++;
  }
  auto *image = new Image(rows, cols, 1, WB_image_depth::Image_depth::CV_32S);
  pixel_32S *buf_ptr = image->buf_32S;
  for (const std::vector<std::string> &row_values: lines)
    for (const std::string &value_str: row_values) {
      int value;
      if (wb_utils::string_to_int(value_str, value))
        *buf_ptr++ = value;
      else {
        errors.add("Image::read_text", "", "invalid value '" + value_str + "'");
        delete image;
        return nullptr;
      }
    }
  return image;
}

void Hough_peak::set_rho(int rho_index, int nrhos) {
  rho = Polar_trig::rho_index_to_rho(rho_index, nrhos);
}

void Hough_peak::write(const std::string &path, Errors &errors) const {
  FILE *fp = file_utils::open_file_write(path, errors);
  if (fp) {
    write(fp, errors);
    fclose(fp);
  }
}

void Hough_peak::write(FILE *fp, Errors &errors) const {
  float rho_float = wb_utils::double_to_float(rho);
  fwrite(&rho_float, sizeof(float), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak rho ");
    return;
  }
  int theta = Polar_trig::theta_index_to_theta(theta_index);
  fwrite(&theta, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak theta ");
    return;
  }
  fwrite(&count, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak count ");
    return;
  }
  fwrite(&total_difference, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak total_difference ");
    return;
  }
  float percent_difference_float = wb_utils::double_to_float(percent_difference);
  fwrite(&percent_difference_float, sizeof(float), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak percent_difference ");
    return;
  }
}

void Hough_peak::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
  ofs << rho << delim;
  ofs << Polar_trig::theta_index_to_theta(theta_index) << delim;
  ofs << count << delim;
  ofs << total_difference << delim;
  ofs << percent_difference << delim;
  ofs << std::endl;
}




