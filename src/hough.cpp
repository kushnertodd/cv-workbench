//
// Created by kushn on 6/11/2022.
//

#include <cstring>
#include <fstream>
//#include "errors.hpp"
#include "file_utils.hpp"
//#include "hough_accum.hpp"
//#include "wb_window.hpp"
#include "image.hpp"
#include "wb_utils.hpp"
#include "hough.hpp"

Hough::~Hough() {
  delete hough_accum;
}

/**
 * For reading a Hough
 * @param m_hough_accum
 * @param m_hough_accum
 * @param m_theta_inc
 * @param m_threshold
 */
Hough::Hough(Hough_accum *m_hough_accum) :
    hough_accum(m_hough_accum) {
}

Hough *Hough::create_image(Image *image, int theta_inc, int pixel_threshold) {
  auto *hough_accum = Hough_accum::create_image(image, theta_inc, pixel_threshold);
  auto *hough = new Hough(hough_accum);
  return hough;
}

void Hough::find_peaks(std::list<Hough_peak> &hough_peaks, int rho_size, int theta_size, int threshold_count,
                       int threshold_difference,
                       double threshold_percentage) {
  hough_accum->find_peaks(hough_peaks, rho_size, theta_size, threshold_count, threshold_difference, threshold_percentage);
}

/*
void Hough::peaks_to_line_segments(std::list<Line_segment> &line_segments, int rows, int cols, int nrhos) {
  for (Hough_peak peak: hough_peaks) {
    Line_segment line_segment;
    if (WB_window::clip_window(rows, cols, line_segment, line, nrhos))
      line_segments.push_back(line_segment);
  }
}
*/

void Hough::log(Image *image, std::list<WB_log_entry> &log_entries) const {
  int nthetas = hough_accum->get_nthetas();
  int theta_inc = hough_accum->get_theta_inc();
  int nrhos = hough_accum->get_nrhos();
  int min_count = hough_accum->get_min_value();
  int max_count = hough_accum->get_max_value();
  double mean = hough_accum->get_mean();
  double std_dev = hough_accum->get_standard_deviation();

  WB_log_entry log_entry_rows("rows", wb_utils::int_to_string(image->get_rows()));
  log_entries.push_back(log_entry_rows);
  WB_log_entry log_entry_cols("cols", wb_utils::int_to_string(image->get_cols()));
  log_entries.push_back(log_entry_cols);
  WB_log_entry log_entry_components("components", wb_utils::int_to_string(image->get_components()));
  log_entries.push_back(log_entry_components);
  WB_log_entry log_entry_depth("depth", WB_image_depth::to_string(image->get_depth()));
  log_entries.push_back(log_entry_depth);
  WB_log_entry log_entry_theta_inc("theta_inc", wb_utils::int_to_string(theta_inc));
  log_entries.push_back(log_entry_theta_inc);
  WB_log_entry log_entry_nrhos("nrhos", wb_utils::int_to_string(nrhos));
  log_entries.push_back(log_entry_nrhos);
  WB_log_entry log_entry_nthetas("nthetas", wb_utils::int_to_string(nthetas));
  log_entries.push_back(log_entry_nthetas);
  WB_log_entry log_entry_min_value("min bin count", wb_utils::int_to_string(min_count));
  log_entries.push_back(log_entry_min_value);
  WB_log_entry log_entry_max_value("max bin count", wb_utils::int_to_string(max_count));
  log_entries.push_back(log_entry_max_value);
  WB_log_entry log_entry_mean("bin count mean", wb_utils::double_to_string(mean));
  log_entries.push_back(log_entry_mean);
  WB_log_entry log_entry_standard_deviation("bin count standard deviation",
                                            wb_utils::double_to_string(std_dev));
  log_entries.push_back(log_entry_standard_deviation);
}

Hough *Hough::read(const std::string &path, Errors &errors) {
  FILE *fp = file_utils::open_file_read(path, errors);
  Hough *hough = nullptr;
  if (fp) {
    hough = Hough::read(fp, errors);
    fclose(fp);
  }
  return hough;
}

Hough *Hough::read(FILE *fp, Errors &errors) {
  Hough_accum *hough_accum = Hough_accum::read(fp, errors);
  if (hough_accum == nullptr || errors.has_error())
    return nullptr;
  return new Hough(hough_accum);
}

// NRFPT
/*
Hough *Hough::read_text(std::ifstream &ifs, Errors &errors) {
  Hough_accum *hough_accum = Hough_accum::read_text(ifs, errors);
  if (hough_accum == nullptr || errors.has_error())
    return nullptr;
  return new Hough(hough_accum);
}
*/

void Hough::write(const std::string &path, Errors &errors) const {
  FILE *fp = file_utils::open_file_write(path, errors);
  if (fp) {
    write(fp, errors);
    fclose(fp);
  }
}

void Hough::write(FILE *fp, Errors &errors) const {
  hough_accum->write(fp, errors);
}

void Hough::write_text(const std::string &path, const std::string &delim, Errors &errors) const {
  std::ofstream ofs = file_utils::open_file_write_text(path, errors);
  if (ofs) {
    hough_accum->write_text(ofs, "\t");
    ofs.close();
  }
}

void Hough::write_text(std::ofstream &ofs, const std::string &delim) const {
  hough_accum->write_text(ofs, "\t");
}
