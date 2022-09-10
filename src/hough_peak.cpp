//
// Created by kushn on 6/11/2022.
//

#include <cstring>
#include "errors.hpp"
#include "file_utils.hpp"
#include "hough_accum.hpp"
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
Hough_peak::Hough_peak(int m_theta_index,
                       int m_rho_index,
                       int m_count,
                       int m_total_difference,
                       float m_percent_difference) :
    theta_index(m_theta_index),
    rho_index(m_rho_index),
    count(m_count),
    total_difference(m_total_difference),
    percent_difference(m_percent_difference) {}

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
  int theta_index;
  wb_utils::read_int(fp, theta_index, "Hough_peak::read", "", "missing theta_index", errors);
  int rho_index;
  if (!errors.has_error())
    wb_utils::read_int(fp, rho_index, "Hough_peak::read", "", "missing rho_index", errors);
  int count;
  if (!errors.has_error())
    wb_utils::read_int(fp, count, "Hough_peak::read", "", "missing count", errors);
  int total_difference;
  if (!errors.has_error())
    wb_utils::read_int(fp, total_difference, "Hough_peak::read", "", "missing total_difference", errors);
  float percent_difference_float;
  if (!errors.has_error())
    wb_utils::read_float(fp,
                         percent_difference_float,
                         "Hough_peak::read",
                         "",
                         "missing percent_difference",
                         errors);
  float percent_difference = percent_difference_float;
  if (errors.has_error())
    return nullptr;
  else
    return new Hough_peak(theta_index,
                          rho_index,
                          count,
                          total_difference,
                          percent_difference);
}

void Hough_peak::write(const std::string &path, Errors &errors) const {
  FILE *fp = file_utils::open_file_write(path, errors);
  if (fp) {
    write(fp, errors);
    fclose(fp);
  }
}

void Hough_peak::write(FILE *fp, Errors &errors) const {
  fwrite(&theta_index, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak theta_index ");
    return;
  }
  fwrite(&rho_index, sizeof(int), 1, fp);
  if (ferror(fp) != 0) {
    errors.add("Hough_peak::write", "", "cannot write Hough peak rho_index ");
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
  ofs << theta_index << delim;
  ofs << rho_index << delim;
  ofs << count << delim;
  ofs << total_difference << delim;
  ofs << percent_difference << delim;
  ofs << std::endl;
}




