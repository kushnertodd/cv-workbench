//
// Created by kushn on 6/11/2022.
//

#include "file_utils.hpp"
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

Hough *Hough::create_image(Image *image, int theta_inc, int rho_inc, int pixel_threshold) {
  auto *hough_accum = Hough_accum::create_image(image, theta_inc, rho_inc, pixel_threshold);
  auto *hough = new Hough(hough_accum);
  return hough;
}

void Hough::find_peaks(std::list<Hough_peak> &hough_peaks, int rho_size, int theta_size, int threshold_count,
                       int threshold_difference,
                       double threshold_percentage) {
  hough_accum->find_peaks(hough_peaks, rho_size, theta_size, threshold_count, threshold_difference, threshold_percentage,
                          count_stats,
                          difference_stats,
                          percentage_stats);
}

void Hough::log(std::list<WB_log_entry> &log_entries) const {
  int nthetas = hough_accum->get_nthetas();
  int theta_inc = hough_accum->get_theta_inc();
  int rho_inc = hough_accum->get_rho_inc();
  int nrhos = hough_accum->get_nrhos();
  int min_count = wb_utils::double_to_int(hough_accum->get_min_value());
  int max_count = wb_utils::double_to_int(hough_accum->get_max_value());
  double mean = hough_accum->get_mean();
  double std_dev = hough_accum->get_standard_deviation();

  WB_log_entry log_entry_theta_inc("theta inc", wb_utils::int_to_string(theta_inc));
  log_entries.push_back(log_entry_theta_inc);
  WB_log_entry log_entry_rho_inc("rho inc", wb_utils::int_to_string(rho_inc));
  log_entries.push_back(log_entry_rho_inc);
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

void Hough::log_peaks(std::list<Hough_peak> &hough_peaks, std::list<WB_log_entry> &log_entries) {
  int npeaks = (int)hough_peaks.size();
  int count_min =  wb_utils::double_to_int(count_stats.get_min_value());
  int count_max =  wb_utils::double_to_int(count_stats.get_max_value());
  double count_mean = count_stats.get_mean();
  double count_standard_deviation = count_stats.get_standard_deviation();

  int difference_min =  wb_utils::double_to_int(difference_stats.get_min_value());
  int difference_max =  wb_utils::double_to_int(difference_stats.get_max_value());
  double difference_mean = difference_stats.get_mean();
  double difference_standard_deviation = difference_stats.get_standard_deviation();

  double percentage_min =  percentage_stats.get_min_value();
  double percentage_max =  percentage_stats.get_max_value();
  double percentage_mean = percentage_stats.get_mean();
  double percentage_standard_deviation = percentage_stats.get_standard_deviation();

  WB_log_entry log_entry_npeaks("npeaks", wb_utils::int_to_string(npeaks));
  log_entries.push_back(log_entry_npeaks);
  WB_log_entry log_entry_count_min_value("min bin count", wb_utils::int_to_string(count_min));
  log_entries.push_back(log_entry_count_min_value);
  WB_log_entry log_entry_count_max_value("max bin count", wb_utils::int_to_string(count_max));
  log_entries.push_back(log_entry_count_max_value);
  WB_log_entry log_entry_count_mean("bin count mean", wb_utils::double_to_string(count_mean));
  log_entries.push_back(log_entry_count_mean);
  WB_log_entry log_entry_count_standard_deviation("bin count standard deviation",
                                            wb_utils::double_to_string(count_standard_deviation));
  log_entries.push_back(log_entry_count_standard_deviation);

  WB_log_entry log_entry_difference_min_value("min difference", wb_utils::int_to_string(difference_min));
  log_entries.push_back(log_entry_difference_min_value);
  WB_log_entry log_entry_difference_max_value("max difference", wb_utils::int_to_string(difference_max));
  log_entries.push_back(log_entry_difference_max_value);
  WB_log_entry log_entry_difference_mean("difference mean", wb_utils::double_to_string(difference_mean));
  log_entries.push_back(log_entry_difference_mean);
  WB_log_entry log_entry_difference_standard_deviation("difference standard deviation",
                                                  wb_utils::double_to_string(difference_standard_deviation));
  log_entries.push_back(log_entry_difference_standard_deviation);

  WB_log_entry log_entry_percentage_min_value("min difference percentage", wb_utils::double_to_string(percentage_min));
  log_entries.push_back(log_entry_percentage_min_value);
  WB_log_entry log_entry_percentage_max_value("max difference percentage", wb_utils::double_to_string(percentage_max));
  log_entries.push_back(log_entry_percentage_max_value);
  WB_log_entry log_entry_percentage_mean("difference percentage mean", wb_utils::double_to_string(percentage_mean));
  log_entries.push_back(log_entry_percentage_mean);
  WB_log_entry log_entry_percentage_standard_deviation("difference percentage standard deviation",
                                                  wb_utils::double_to_string(percentage_standard_deviation));
  log_entries.push_back(log_entry_percentage_standard_deviation);
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
