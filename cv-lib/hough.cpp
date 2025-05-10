#include "hough.hpp"
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
 * @param m_image
 * @param m_rho_inc
 * @param m_theta_inc
 * @param m_pixel_threshold
 */
Hough::Hough(int m_ncols, int m_nrows, int m_rho_inc, int m_theta_inc, int m_pixel_threshold) :
    ncols(m_ncols), nrows(m_nrows), pixel_threshold(m_pixel_threshold) {
    polar_trig.init(ncols, nrows, m_rho_inc, m_theta_inc);
    nbins = get_nrhos() * get_nthetas();
    accumulator = std::unique_ptr<int[]>(new int[nbins]);
}
/**
 * @brief
 * @param m_image
 * @param m_rho_inc
 * @param m_theta_inc
 * @param m_pixel_threshold
 */
Hough::Hough(Image *m_image, int m_rho_inc, int m_theta_inc, int m_pixel_threshold) :
    Hough(m_image->get_ncols(), m_image->get_nrows(), m_rho_inc, m_theta_inc, m_pixel_threshold) {
    initialize(m_image, pixel_threshold);
}
/**
 * @brief
 */
void Hough::clear() {
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++)
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++)
            set(rho_index, theta_index, 0);
}
/**
 * @brief
 * @param lines
 * @param threshold
 */
void Hough::find_peaks(std::list<Polar_line> &lines, double threshold) const {
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            int count = get(rho_index, theta_index);
            if (count > threshold) {
                Polar_line line(rho_index, theta_index);
                lines.push_back(line);
            }
        }
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
/**
 * @brief
 * @return
 */
int Hough::get_ncols() const { return ncols; }
/**
 * @brief
 * @return
 */
int Hough::get_nrhos() const { return polar_trig.get_nrhos(); }
/**
 * @brief
 * @return
 */
int Hough::get_nrows() const { return nrows; }
/**
 * @brief
 * @return
 */
int Hough::get_nthetas() const { return polar_trig.get_nthetas(); }
/**
 * @brief
 * @return
 */
int Hough::get_rho_inc() const { return polar_trig.get_rho_inc(); }
/**
 * @brief
 * @return
 */
int Hough::get_theta_inc() const { return polar_trig.get_theta_inc(); }
/**
 * @brief
 * @param image_theshold
 */
void Hough::initialize(Image *image, int pixel_threshold) {
    clear();
    std::cout << "ncols " << ncols << " nrows " << nrows << std::endl;
    for (int col = 0; col < ncols; col++) {
        for (int row = 0; row < nrows; row++) {
            Point point;
            image->to_point(point, col, row);
            double value = std::abs(image->get(col, row));
            if (value > pixel_threshold) {
                std::cout << "(" << col << "/" << image->to_x(col) << ", " << row << "/" << image->to_y(row) << ") -> "
                          << "(" << std::setprecision(3) << point.get_x() << ", " << point.get_y() << ")" << std::endl;
                for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
                    int rho_index = polar_trig.point_theta_index_to_rho_index(point, theta_index);
                    std::cout << "    "
                              << "(" << theta_index << ", " << rho_index << "): "
                              << "(" << polar_trig.to_theta(theta_index) << ", " << polar_trig.to_rho(rho_index) << ") "
                              << std::endl;
                    update(rho_index, theta_index, wb_utils::double_to_int_round(value));
                }
            }
        }
    }
    update_accumulator_stats();
}
/*
void Hough::find_lines(int ncols, int nrows, int nrhos, int nthetas) {
  lines_to_line_segments(ncols, nrows, nrhos, nthetas);
}

void Hough::lines_to_line_segments(int nrows, int ncols, int nrhos, int nthetas) {
  for (Polar_line line: lines) {
    Line_segment line_segment;
      if (WB_window::clip_window(nrows, ncols, nrhos, nthetas,line_segment, line))
      line_segments.push_back(line_segment);
  }
}
*/
/**
 * @brief
 * @param log_entries
 */
void Hough::log(std::list<WB_log_entry> &log_entries) {
    WB_log_entry log_entry_ncols("ncols", wb_utils::int_to_string(get_ncols()));
    log_entries.push_back(log_entry_ncols);
    WB_log_entry log_entry_nrows("nrows", wb_utils::int_to_string(get_nrows()));
    log_entries.push_back(log_entry_nrows);
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
    int ncols{};
    int nrows{};
    int rho_inc{};
    int theta_inc{};
    wb_utils::read_int(fp, ncols, "Hough::read", "", "missing hough accumulator ncols", errors);
    if (!errors.has_error())
        wb_utils::read_int(fp, nrows, "Hough::read", "", "missing hough accumulator nrows", errors);
    if (!errors.has_error())
        wb_utils::read_int(fp, rho_inc, "Hough::read", "", "missing hough accumulator rho_inc", errors);
    if (!errors.has_error())
        wb_utils::read_int(fp, theta_inc, "Hough::read", "", "missing hough accumulator theta_inc", errors);
    if (errors.has_error())
        return nullptr;
    else {
        auto *hough = new Hough(ncols, nrows, rho_inc, theta_inc);
        wb_utils::read_int_buffer(fp, hough->accumulator.get(), hough->nbins, "Hough::read", "",
                                  "cannot read hough accumulator data", errors);
        if (errors.has_error()) {
            delete hough;
            return nullptr;
        }
        hough->update_accumulator_stats();
        return hough;
    }
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
    assert(index < nbins);
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
int Hough::to_rho_index(double rho) const { return polar_trig.to_rho_index(rho); }
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
    int ncols = get_ncols();
    fwrite(&ncols, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator get_ncols()");
        return;
    }
    int nrows = get_nrows();
    fwrite(&nrows, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator get_nrows()");
        return;
    }
    int theta_inc = get_theta_inc();
    fwrite(&theta_inc, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator theta_inc");
        return;
    }
    int rho_inc = get_rho_inc();
    fwrite(&rho_inc, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator rho_inc");
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
 * @param path
 * @param delim
 * @param errors
 */
void Hough::write_text(const std::string &path, const std::string &delim, Errors &errors) {
    std::ofstream ofs = file_utils::open_file_write_text(path, errors);
    if (ofs) {
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
    ofs << delim << std::fixed;
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
        double rho = polar_trig.to_rho(rho_index);
        ofs << std::setprecision(3) << rho << delim;
    }
    ofs << std::endl;
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        ofs << polar_trig.to_theta(theta_index) << delim;
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            ofs << get(rho_index, theta_index) << delim;
        }
        ofs << std::endl;
    }
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Hough::write_peak_lines(FILE *fp, Errors &errors) const {
    size_t npeaks = lines.size();
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
    for (Polar_line line: lines) {
        line.write(fp, errors);
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
    for (Polar_line line: lines) {
        line.write_text(ofs, delim, errors);
        if (errors.has_error())
            break;
    }
}
