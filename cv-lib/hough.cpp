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
 */
Hough::Hough(double m_x_min, double m_x_max, double m_y_min, double m_y_max, int m_rho_inc, int m_theta_inc,
             int m_pixel_threshold) : pixel_threshold(m_pixel_threshold) {
    polar_trig =
            std::unique_ptr<Polar_trig>(new Polar_trig(m_x_min, m_x_max, m_y_min, m_y_max, m_rho_inc, m_theta_inc));
    nbins = get_nrhos() * get_nthetas();
    accumulator = std::unique_ptr<int[]>(new int[nbins]);
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
int Hough::get_nrhos() const { return polar_trig->get_nrhos(); }
/**
 * @brief
 * @return
 */
int Hough::get_nthetas() const { return polar_trig->get_nthetas(); }
/**
 * @brief
 * @return
 */
int Hough::get_rho_inc() const { return polar_trig->get_rho_inc(); }
/**
 * @brief
 * @return
 */
int Hough::get_theta_inc() const { return polar_trig->get_theta_inc(); }
/**
 * @brief
 * @return
 */
double Hough::get_x_min() const { return polar_trig->get_x_min(); }
/**
 * @brief
 * @return
 */
double Hough::get_x_max() const { return polar_trig->get_x_max(); }
/**
 * @brief
 * @return
 */
double Hough::get_y_min() const { return polar_trig->get_y_min(); }
/**
 * @brief
 * @return
 */
double Hough::get_y_max() const { return polar_trig->get_y_max(); }
/**
 * @brief
 * @param image_theshold
 */
void Hough::initialize(Image *image, int pixel_threshold) {
    clear();
    for (int col = 0; col < image->get_ncols(); col++) {
        for (int row = 0; row < image->get_nrows(); row++) {
            Point point;
            image->to_point(point, col, row);
            double value = std::abs(image->get(col, row));
            if (value > pixel_threshold) {
                for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
                    int rho_index = polar_trig->point_theta_index_to_rho_index(point, theta_index);
                    update(rho_index, theta_index, wb_utils::double_to_int_round(value));
                }
            }
        }
    }
    update_accumulator_stats();
}
/**
 * @brief
 * @param log_entries
 */
void Hough::log(std::list<WB_log_entry> &log_entries) {
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
    double x_min;
    if (!errors.has_error())
        wb_utils::read_double(fp, x_min, "Hough::read", "", "missing hough x_min", errors);
    double x_max;
    if (!errors.has_error())
        wb_utils::read_double(fp, x_max, "Hough::read", "", "missing hough x_max", errors);
    double y_min;
    if (!errors.has_error())
        wb_utils::read_double(fp, y_min, "Hough::read", "", "missing hough y_min", errors);
    double y_max;
    if (!errors.has_error())
        wb_utils::read_double(fp, y_max, "Hough::read", "", "missing hough y_max", errors);
    Hough *hough = nullptr;
    if (!errors.has_error()) {
        auto hough = new Hough(x_min, x_max, y_min, y_max, rho_inc, theta_inc);
        wb_utils::read_int_buffer(fp, hough->accumulator.get(), hough->nbins, "Hough::read", "",
                                  "cannot read hough accumulator data", errors);
        if (!errors.has_error()) {
            hough->update_accumulator_stats();
            return hough;
        }
    }
    delete hough;
    return nullptr;
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
int Hough::to_rho_index(double rho) const { return polar_trig->to_rho_index(rho); }
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
    double x_min = get_x_min();
    fwrite(&x_min, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator x_min");
        return;
    }
    double x_max = get_x_max();
    fwrite(&x_max, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator get_x_max");
        return;
    }
    double y_min = get_y_min();
    fwrite(&y_min, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator y_min");
        return;
    }
    double y_max = get_y_max();
    fwrite(&y_max, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Hough::write", "", "cannot write Hough accumulator y_max");
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
    ofs << "x_min" << delim << std::setprecision(1) << get_x_min() << std::endl;
    ofs << "x_max" << delim << std::setprecision(1) << get_x_max() << std::endl;
    ofs << "y_min" << delim << std::setprecision(1) << get_y_min() << std::endl;
    ofs << "y_max" << delim << std::setprecision(1) << get_y_max() << std::endl;
    ofs << delim;
    for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
        double rho = polar_trig->to_rho(rho_index);
        ofs << std::setprecision(1) << rho << delim;
    }
    ofs << std::endl;
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        ofs << polar_trig->to_theta(theta_index) << delim;
        for (int rho_index = 0; rho_index < get_nrhos(); rho_index++) {
            ofs << get(rho_index, theta_index) << delim;
        }
        ofs << std::endl;
    }
}
