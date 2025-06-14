#include "hough.hpp"
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include "errors.hpp"
#include "file_utils.hpp"
#include "wb_window.hpp"

extern bool debug;

/**
 * @brief
 */
Hough::~Hough() = default;
/**
 * @brief
 */
Hough::Hough() = default;
/**
 * https://stackoverflow.com/questions/21377360/proper-way-to-create-unique-ptr-that-holds-an-allocated-array
 * @brief
 * @param m_min_x
 * @param m_max_x
 * @param m_min_y
 * @param m_max_y
 * @param m_rho_inc
 * @param m_theta_inc
 * @param m_pixel_threshold
 * @param m_unit
 * @param m_min_theta
 * @param m_max_theta
 */
Hough::Hough(double m_min_x, double m_max_x, double m_min_y, double m_max_y, int m_rho_inc, int m_theta_inc,
             int m_pixel_threshold, bool m_unit, int m_min_theta, int m_max_theta) :
    pixel_threshold(m_pixel_threshold), unit(m_unit) {
    polar_trig = std::unique_ptr<Polar_trig>(
            new Polar_trig(m_min_x, m_min_y, m_max_x, m_max_y, m_rho_inc, m_theta_inc, m_min_theta, m_max_theta));
    nbins = get_nrhos() * get_nthetas();
    accumulator = std::unique_ptr<int[]>(new int[nbins]);
}
/**
 * @brief
 */
void Hough::clear() {
    for (int i = 0; i < nbins; i++)
        accumulator[i] = 0;
}
/**
 * @brief
 * @param lines
 * @param threshold
 */
void Hough::find_peaks(std::vector<Hough_peak> &filtered_peaks, double threshold, double rho_suppress,
                       int theta_suppress) const {
    std::vector<Hough_peak> peaks;
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            int count = get(rho_index, theta_index);
            double count_percentile = (100.0 * count) / accumulator_stats.get_max_value();
            if (count_percentile > threshold) {
                Hough_peak peak(count_percentile, polar_trig->to_rho(rho_index), polar_trig->to_theta(theta_index));
                peaks.push_back(peak);
            }
        }
    }
    std::sort(peaks.begin(), peaks.end(), Hough_peak::comp);
    for (auto &peak: peaks) {
        bool reject = false;
        for (auto &filtered_peak: filtered_peaks) {
            if (abs(peak.rho - filtered_peak.rho) < rho_suppress &&
                abs(peak.theta - filtered_peak.theta) < theta_suppress) {
                reject = true;
                break;
            }
        }
        if (!reject)
            filtered_peaks.push_back(peak);
    }
}
/**
 * @brief
 * @param rho_index
 * @param theta_index
 * @return
 */
int Hough::get(int rho_index, int theta_index) const {
    int index = rho_index_theta_index_to_index(rho_index, theta_index);
    return accumulator[index];
}
int Hough::get_max_theta() const { return polar_trig->get_max_theta(); }
double Hough::get_max_x() const { return polar_trig->get_max_x(); }
double Hough::get_max_y() const { return polar_trig->get_max_y(); }
int Hough::get_min_theta() const { return polar_trig->get_min_theta(); }
double Hough::get_min_x() const { return polar_trig->get_min_x(); }
double Hough::get_min_y() const { return polar_trig->get_min_y(); }
int Hough::get_nrhos() const { return polar_trig->get_nrhos(); }
int Hough::get_nthetas() const { return polar_trig->get_nthetas(); }
int Hough::get_rho_inc() const { return polar_trig->get_rho_inc(); }
int Hough::get_theta_inc() const { return polar_trig->get_theta_inc(); }
/**
 * @brief
 * @param image_theshold
 */
void Hough::initialize(Image *image, int pixel_threshold, bool unit, int min_col, bool saw_min_col, int min_row,
                       bool saw_min_row, int max_col, bool saw_max_col, int max_row, bool saw_max_row, Errors &errors) {
    clear();
    if (!saw_min_col)
        min_col = 0;
    if (!saw_min_row)
        min_row = 0;
    if (!saw_max_col)
        max_col = image->get_ncols() - 1;
    if (!saw_max_row)
        max_row = image->get_nrows() - 1;
    if (min_col < 0)
        errors.add("Hough::initialize", "", "min-col must be positive");
    if (min_row < 0)
        errors.add("Hough::initialize", "", "min-row must be positive");
    int ncols = image->get_ncols();
    int nrows = image->get_nrows();
    if (max_col >= ncols)
        errors.add("Hough::initialize", "", "max-col must be within image");
    if (max_row >= nrows)
        errors.add("Hough::initialize", "", "max-row must be within image");
    if (max_col < min_col)
        errors.add("Hough::initialize", "", "max-col must be at least as large as mi-col");
    if (max_row < min_row)
        errors.add("Hough::initialize", "", "min-row must be at least as large as max-row");
    if (!errors.has_error()) {
        for (int col = min_col; col <= max_col; col++) {
            for (int row = min_row; row <= max_row; row++) {
                double value = std::abs(image->get(col, row));
                if (value > pixel_threshold) {
                    Point point;
                    image->to_point(point, col, row);
                    int theta_inc = get_theta_inc();
                    int min_theta = get_min_theta();
                    int max_theta = get_max_theta();
                    if (max_theta > min_theta) {
                        for (int theta = min_theta; theta <= max_theta; theta += theta_inc) {
                            double rho = polar_trig->point_theta_to_rho(point, theta);
                            int rho_index = polar_trig->to_rho_index(rho);
                            int theta_index = polar_trig->to_theta_index(theta);
                            update(rho_index, theta_index, (unit ? 1 : wb_utils::double_to_int_round(value)));
                        }
                    } else {
                        int theta = 0;
                        for (theta = min_theta; theta < theta_pi; theta += theta_inc) {
                            double rho = polar_trig->point_theta_to_rho(point, theta);
                            int rho_index = polar_trig->to_rho_index(rho);
                            int theta_index = polar_trig->to_theta_index(theta);
                            update(rho_index, theta_index, (unit ? 1 : wb_utils::double_to_int_round(value)));
                        }
                        for (theta -= theta_pi; theta <= max_theta; theta += theta_inc) {
                            int theta_adj = theta + theta_pi;
                            double rho = polar_trig->point_theta_to_rho(point, theta_adj);
                            int rho_index = polar_trig->to_rho_index(rho);
                            int theta_index = polar_trig->to_theta_index(theta_adj);
                            update(rho_index, theta_index, (unit ? 1 : wb_utils::double_to_int_round(value)));
                        }
                    }
                }
            }
        }
        update_accumulator_stats();
    }
}
/**
 * @brief
 * @param log_entries
 */
void Hough::log(std::vector<WB_log_entry> &log_entries) {
    WB_log_entry log_entry_rho_inc("rho inc", wb_utils::int_to_string(get_rho_inc()));
    log_entries.push_back(log_entry_rho_inc);
    WB_log_entry log_entry_theta_inc("theta inc", wb_utils::int_to_string(get_theta_inc()));
    log_entries.push_back(log_entry_theta_inc);
    WB_log_entry log_entry_nrhos("nrhos", wb_utils::int_to_string(get_nrhos()));
    log_entries.push_back(log_entry_nrhos);
    WB_log_entry log_entry_nthetas("nthetas", wb_utils::int_to_string(get_nthetas()));
    log_entries.push_back(log_entry_nthetas);
    WB_log_entry log_entry_mean("pixel mean", wb_utils::double_to_string(accumulator_stats.get_mean()));
    log_entries.push_back(log_entry_mean);
    WB_log_entry log_entry_standard_deviation("pixel standard deviation",
                                              wb_utils::double_to_string(accumulator_stats.get_standard_deviation()));
    log_entries.push_back(log_entry_standard_deviation);
    WB_log_entry log_entry_min_value("min pixel value", wb_utils::double_to_string(accumulator_stats.bounds.min_value));
    log_entries.push_back(log_entry_min_value);
    WB_log_entry log_entry_max_value("max pixel value", wb_utils::double_to_string(accumulator_stats.bounds.max_value));
    log_entries.push_back(log_entry_max_value);
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
Hough *Hough::read(const std::string &path, Errors &errors) {
    FILE *fp = file_utils::open_file_read(path, errors);
    Hough *hough = nullptr;
    if (fp) {
        hough = Hough::read(fp, errors);
        fclose(fp);
    }
    return hough;
}
/**
 * @brief
 * @param fp
 * @param errors
 * @return
 */
Hough *Hough::read(FILE *fp, Errors &errors) {
    int rho_inc;
    if (!errors.has_error())
        wb_utils::read_int(fp, rho_inc, "Hough::read", "", "missing hough rho_inc", errors);
    int theta_inc;
    if (!errors.has_error())
        wb_utils::read_int(fp, theta_inc, "Hough::read", "", "missing hough theta_inc", errors);
    double min_x;
    if (!errors.has_error())
        wb_utils::read_double(fp, min_x, "Hough::read", "", "missing hough min_x", errors);
    double max_x;
    if (!errors.has_error())
        wb_utils::read_double(fp, max_x, "Hough::read", "", "missing hough max_x", errors);
    double min_y;
    if (!errors.has_error())
        wb_utils::read_double(fp, min_y, "Hough::read", "", "missing hough min_y", errors);
    double max_y;
    if (!errors.has_error())
        wb_utils::read_double(fp, max_y, "Hough::read", "", "missing hough max_y", errors);
    int pixel_threshold;
    if (!errors.has_error())
        wb_utils::read_int(fp, pixel_threshold, "Hough::read", "", "missing hough pixel_threshold", errors);
    int int_unit;
    if (!errors.has_error())
        wb_utils::read_int(fp, int_unit, "Hough::read", "", "missing hough unit", errors);
    int min_theta;
    if (!errors.has_error())
        wb_utils::read_int(fp, min_theta, "Hough::read", "", "missing hough min_theta", errors);
    int max_theta;
    if (!errors.has_error())
        wb_utils::read_int(fp, max_theta, "Hough::read", "", "missing hough max_theta", errors);
    Hough *hough = nullptr;
    if (!errors.has_error()) {
        hough = new Hough(min_x, max_x, min_y, max_y, rho_inc, theta_inc, pixel_threshold, (int_unit == 1), min_theta,
                          max_theta);
        wb_utils::read_int_buffer(fp, hough->accumulator.get(), hough->nbins, "Hough::read", "",
                                  "cannot read hough accumulator data", errors);
        if (!errors.has_error())
            hough->update_accumulator_stats();
        if (errors.has_error())
            delete hough;
    }
    return hough;
}
/**
 * @brief
 * TODO: not functional, cannot create Hough without ncols, nrows, rho_inc, theta_inc
 * @param ifs
 * @param errors
 * @return
 */
Hough *Hough::read_text(std::ifstream &ifs, Errors &errors) {
    auto *hough = new Hough();
    std::string line;
    while (getline(ifs, line)) {
        std::vector<std::string> values = wb_utils::string_split(line);
        for (const std::string &value_str: values) {
            int value;
            if (!wb_utils::string_to_int(value_str, value)) {
                errors.add("Hough::read_text", "", "invalid value '" + value_str + "'");
                delete hough;
                return nullptr;
            }
        }
    }
    return hough;
}
/**
 * @brief
 * @param rho_index
 * @param theta_index
 * @return
 */
int Hough::rho_index_theta_index_to_index(int rho_index, int theta_index) const {
    int index = rho_index * get_nthetas() + theta_index;
    assert(index >= 0 && index < nbins);
    return index;
}
/**
 * @brief
 * @param rho_index
 * @param theta_index
 * @param value
 */
void Hough::set(int rho_index, int theta_index, int value) {
    int index = rho_index_theta_index_to_index(rho_index, theta_index);
    accumulator[index] = value;
}
/**
 * @brief
 * @param rho
 * @return
 */
int Hough::to_rho_index(double rho) const { return polar_trig->to_rho_index(rho); }
/**
 * @brief
 * @param theta
 * @return
 */
int Hough::to_theta_index(int theta) const { return polar_trig->to_theta_index(theta); }
/**
 * @brief
 * @param rho_index
 * @param theta_index
 * @param value
 */
void Hough::update(int rho_index, int theta_index, int value) const {
    int index = rho_index_theta_index_to_index(rho_index, theta_index);
    accumulator[index] += value;
}
/**
 * @brief
 */
void Hough::update_accumulator_stats() {
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            accumulator_stats.update(get(rho_index, theta_index));
        }
    }
}
/**
 * @brief
 * @param path
 * @param errors
 */
void Hough::write(const std::string &path, Errors &errors) const {
    FILE *fp = file_utils::open_file_write(path, errors);
    if (fp) {
        write(fp, errors);
        fclose(fp);
    }
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Hough::write(FILE *fp, Errors &errors) const {
    int rho_inc = get_rho_inc();
    fwrite(&rho_inc, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator rho_inc");
        return;
    }
    int theta_inc = get_theta_inc();
    fwrite(&theta_inc, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator theta_inc");
        return;
    }
    double min_x = get_min_x();
    fwrite(&min_x, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator min_x");
        return;
    }
    double max_x = get_max_x();
    fwrite(&max_x, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator get_max_x");
        return;
    }
    double min_y = get_min_y();
    fwrite(&min_y, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator min_y");
        return;
    }
    double max_y = get_max_y();
    fwrite(&max_y, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator max_y");
        return;
    }
    fwrite(&pixel_threshold, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator pixel_threshold");
        return;
    }
    int int_unit = (unit ? 1 : 0);
    fwrite(&int_unit, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator unit");
        return;
    }
    int min_theta = get_min_theta();
    fwrite(&min_theta, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator min_theta");
        return;
    }
    int max_theta = get_max_theta();
    fwrite(&max_theta, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator max_theta");
        return;
    }
    size_t newLen;
    newLen = fwrite(accumulator.get(), sizeof(int), nbins, fp);
    if (ferror(fp) != 0 || newLen != nbins) {
        errors.add("Hough::write", "", "cannot write Hough accumulator data ");
        return;
    }
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Hough::write_peak_lines(FILE *fp, Errors &errors) const {
    size_t npeaks = peaks.size();
    fwrite(&npeaks, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write_peak_lines", "", "cannot write Hough peak line count");
        return;
    }
    int theta_inc = get_theta_inc();
    fwrite(&theta_inc, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write_peak_lines", "", "cannot write Hough theta_inc  ");
        return;
    }
    int nrhos = get_nrhos();
    fwrite(&nrhos, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write_peak_lines", "", "cannot write Hough nrhos ");
        return;
    }
    for (auto peak: peaks) {
        peak.write(fp, errors);
        if (errors.has_error())
            break;
    }
}
/**
 * @brief
 * @param ofs
 * @param delim
 * @param errors
 */
void Hough::write_peak_lines_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
    for (auto &peak: peaks) {
        peak.write_text(ofs, delim, errors);
        if (errors.has_error())
            break;
    }
}
/**
 * @brief
 * @param path
 * @param delim
 * @param errors
 */
void Hough::write_text(const std::string &path, const std::string &delim, Errors &errors) {
    std::ofstream ofs = file_utils::open_file_write_text(path, errors);
    if (!errors.has_error()) {
        write_text(ofs, "\t", errors);
        ofs.close();
    }
}
/**
 * @brief
 * @param ofs
 * @param delim
 * @param errors
 */
void Hough::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) {
    ofs << std::fixed;
    ofs << "rho_inc" << delim << get_rho_inc() << std::endl;
    ofs << "theta_inc" << delim << get_theta_inc() << std::endl;
    ofs << "nrhos" << delim << std::setprecision(1) << get_nrhos() << std::endl;
    ofs << "nthetas" << delim << std::setprecision(1) << get_nthetas() << std::endl;
    ofs << "min_x" << delim << std::setprecision(1) << get_min_x() << std::endl;
    ofs << "max_x" << delim << std::setprecision(1) << get_max_x() << std::endl;
    ofs << "min_y" << delim << std::setprecision(1) << get_min_y() << std::endl;
    ofs << "max_y" << delim << std::setprecision(1) << get_max_y() << std::endl;
    ofs << "pixel_threshold" << delim << pixel_threshold << std::endl;
    ofs << "unit" << delim << unit << std::endl;
    ofs << "max" << delim << accumulator_stats.get_max_value() << std::endl;
    ofs << delim;
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
        double rho = polar_trig->to_rho(rho_index);
        ofs << std::setprecision(1) << rho << delim;
    }
    ofs << std::endl;
    int theta_inc = get_theta_inc();
    int min_theta = get_min_theta();
    int max_theta = get_max_theta();
    if (max_theta > min_theta) {
        for (int theta = min_theta; theta <= max_theta; theta += theta_inc) {
            int theta_index = polar_trig->to_theta_index(theta);
            ofs << polar_trig->to_theta(theta_index) << delim;
            for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
                ofs << std::setprecision(1) << get(rho_index, theta_index) << delim;
            }
            ofs << std::endl;
        }
        ofs << std::endl;
    } else {
        int theta = min_theta;
        for (; theta < theta_pi; theta += theta_inc) {
            int theta_index = polar_trig->to_theta_index(theta);
            ofs << polar_trig->to_theta(theta_index) << delim;
            for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
                ofs << std::setprecision(1) << get(rho_index, theta_index) << delim;
            }
            ofs << std::endl;
        }
        for (; theta < max_theta + theta_pi; theta += theta_inc) {
            int theta_index = polar_trig->to_theta_index(theta);
            ofs << polar_trig->to_theta(theta_index) << delim;
            for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
                ofs << std::setprecision(1) << get(rho_index, theta_index) << delim;
            }
            ofs << std::endl;
        }
    }
    ofs << std::endl;
}
