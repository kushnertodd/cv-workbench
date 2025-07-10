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
Polar_index::Polar_index() = default;
/**
 * @brief
 * @param m_rho_index
 * @param m_theta_index
 */
Polar_index::Polar_index(int m_rho_index, int m_theta_index) : rho_index(m_rho_index), theta_index(m_theta_index) {}
/**
 * @brief
 * @param m_rho_index
 * @param m_theta_index
 */
void Polar_index::init(int m_rho_index, int m_theta_index) {
    rho_index = m_rho_index;
    theta_index = m_theta_index;
}

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
 * @param m_view
 * @param m_min_x
 * @param m_max_x
 * @param m_min_y
 * @param m_max_y
 * @param m_saw_nrhos
 * @param m_nrhos
 * @param m_saw_rho_inc
 * @param m_rho_inc
 * @param m_theta_inc
 * @param m_pixel_threshold
 * @param m_unit
 * @param m_min_theta
 * @param m_max_theta
 */
Hough::Hough(View *m_view, double m_min_x, double m_max_x, double m_min_y, double m_max_y, bool m_saw_nrhos,
             int m_nrhos, bool m_saw_rho_inc, double m_rho_inc, int m_theta_inc, int m_pixel_threshold, bool m_unit,
             int m_min_theta, int m_max_theta) :
    view(m_view), pixel_threshold(m_pixel_threshold), unit(m_unit), saw_nrhos(m_saw_nrhos), nrhos(m_nrhos),
    saw_rho_inc(m_saw_rho_inc), rho_inc(m_rho_inc) {
    polar_trig =
            std::make_unique<Polar_trig>(m_min_x, m_max_x, m_min_y, m_max_y, m_theta_inc, m_min_theta, m_max_theta);
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
void Hough::find_peaks(double threshold, double rho_suppress, int theta_suppress) {
    std::vector<Hough_peak> initial_peaks;
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < nrhos; rho_index++) {
            int count = get(rho_index, theta_index);
            double count_percentile = (100.0 * count) / accumulator_stats.get_max_value();
            if (count_percentile > threshold) {
                Hough_peak peak(count_percentile, rho_index_to_rho(rho_index), theta_index_to_theta(theta_index));
                initial_peaks.push_back(peak);
            }
        }
    }
    std::sort(initial_peaks.begin(), initial_peaks.end(), Hough_peak::comp);
    for (auto &initial_peak: initial_peaks) {
        bool reject = false;
        for (auto &peak: peaks) {
            if (abs(peak.rho - initial_peak.rho) < rho_suppress &&
                abs(peak.theta - initial_peak.theta) < theta_suppress) {
                reject = true;
                break;
            }
        }
        if (!reject)
            peaks.push_back(initial_peak);
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
int Hough::get_nrhos() const { return nrhos; }
int Hough::get_nthetas() const { return polar_trig->get_nthetas(); }
int Hough::get_theta_inc() const { return polar_trig->get_theta_inc(); }
/**
 * @brief
 * @param image_theshold
 */
void Hough::initialize(int pixel_threshold, bool unit, int min_col, int min_row, int max_col, int max_row,
                       Errors &errors) {
    clear();
    int ncols = view->get_ncols();
    int nrows = view->get_nrows();
    for (int col = 0; col < ncols; col++) {
        for (int row = 0; row < nrows; row++) {
            double value = std::abs(view->get(col, row));
            if (value > pixel_threshold) {
                Point point;
                view->to_point(point, col, row);
                for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
                    int rho_index = point_theta_index_to_rho_index(point, theta_index);
                    update(rho_index, theta_index, (unit ? 1 : wb_utils::double_to_int_round(value)));
                }
            }
        }
    }
    update_accumulator_stats();
}
void Hough::initialize_accumulator() {
    nbins = nrhos * get_nthetas();
    accumulator = std::make_unique<int[]>(nbins);
}
void Hough::initialize_nrhos() {
    if (saw_nrhos)
        rho_inc = (max_rho - min_rho) / (nrhos - 1);
    else if (saw_rho_inc)
        nrhos = wb_utils::double_to_int_round((max_rho - min_rho) / rho_inc);
}
void Hough::initialize_rhos() {
    assert((!saw_nrhos && saw_rho_inc) || (saw_nrhos && !saw_rho_inc));
    int ncols = view->get_ncols();
    int nrows = view->get_nrows();
    min_rho = DBL_MAX;
    max_rho = -DBL_MAX;
    for (int col = 0; col < ncols; col++) {
        for (int row = 0; row < nrows; row++) {
            double value = std::abs(view->get(col, row));
            if (value > pixel_threshold) {
                Point point;
                view->to_point(point, col, row);
                for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
                    double rho = point_theta_index_to_rho(point, theta_index);
                    min_rho = std::min(rho, min_rho);
                    max_rho = std::max(rho, max_rho);
                }
            }
        }
    }
    rho_range = max_rho - min_rho;
    initialize_nrhos();
}
bool Hough::is_rho_index_valid(int rho_index) const { return rho_index >= 0 && rho_index < nrhos; }
/**
 * @brief
 * @param log_entries
 */
void Hough::log(std::vector<WB_log_entry> &log_entries) {
    WB_log_entry log_entry_saw_rho_inc("saw rho inc", wb_utils::int_to_string(saw_rho_inc));
    log_entries.push_back(log_entry_saw_rho_inc);
    WB_log_entry log_entry_rho_inc("rho inc", wb_utils::int_to_string(rho_inc));
    log_entries.push_back(log_entry_rho_inc);
    WB_log_entry log_entry_theta_inc("theta inc", wb_utils::int_to_string(get_theta_inc()));
    log_entries.push_back(log_entry_theta_inc);
    WB_log_entry log_entry_saw_nrhos("saw_nrhos", wb_utils::int_to_string(saw_nrhos));
    log_entries.push_back(log_entry_saw_nrhos);
    WB_log_entry log_entry_nrhos("nrhos", wb_utils::int_to_string(nrhos));
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
 * @param point
 * @param theta_index
 * @return
 */
double Hough::point_theta_index_to_rho(Point &point, int theta_index) {
    return point_theta_index_to_rho(point.x, point.y, theta_index);
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta_index
 * @return
 */
double Hough::point_theta_index_to_rho(double x, double y, int theta_index) const {
    double rho = point_theta_to_rho(x, y, theta_index_to_theta(theta_index));
    return rho;
}
/**
 * @brief
 * @param point
 * @param theta_index
 * @return
 */
int Hough::point_theta_index_to_rho_index(Point &point, int theta_index) {
    return point_theta_index_to_rho_index(point.x, point.y, theta_index);
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta_index
 * @return
 */
int Hough::point_theta_index_to_rho_index(double x, double y, int theta_index) {
    int rho_index = rho_to_rho_index(point_theta_to_rho(x, y, theta_index_to_theta(theta_index)));
    return rho_index;
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta
 * @return
 */
double Hough::point_theta_to_rho(Point &point, int theta) const {
    double rho = point_theta_to_rho(point.x, point.y, theta);
    return rho;
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta
 * @return
 */
double Hough::point_theta_to_rho(double x, double y, int theta) const {
    assert(polar_trig->is_theta_valid(theta));
    double cos_t = Polar_line::to_cos(theta);
    double sin_t = Polar_line::to_sin(theta);
    double rho = x * cos_t + y * sin_t;
    return rho;
}
/**
 * @brief
 * @param point
 * @param theta
 * @return
 */
int Hough::point_theta_to_rho_index(Point &point, int theta) {
    int rho_index = point_theta_to_rho_index(point.x, point.y, theta);
    return rho_index;
}
/**
 * @brief
 * @param x
 * @param y
 * @param theta
 * @return
 */
int Hough::point_theta_to_rho_index(double x, double y, int theta) {
    int rho_index = rho_to_rho_index(point_theta_to_rho(x, y, theta));
    return rho_index;
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
    bool saw_rho_inc;
    wb_utils::read_bool(fp, saw_rho_inc, "Hough::read", "", "missing hough saw_rho_inc", errors);
    double rho_inc;
    if (!errors.has_error())
        wb_utils::read_double(fp, rho_inc, "Hough::read", "", "missing hough rho_inc", errors);
    bool saw_nrhos;
    if (!errors.has_error())
        wb_utils::read_bool(fp, saw_nrhos, "Hough::read", "", "missing hough saw_nrhos", errors);
    int nrhos;
    if (!errors.has_error())
        wb_utils::read_int(fp, nrhos, "Hough::read", "", "missing hough nrhos", errors);
    double min_rho;
    if (!errors.has_error())
        wb_utils::read_double(fp, min_rho, "Hough::read", "", "missing hough min_rho", errors);
    double max_rho;
    if (!errors.has_error())
        wb_utils::read_double(fp, max_rho, "Hough::read", "", "missing hough max_rho", errors);
    double rho_range;
    if (!errors.has_error())
        wb_utils::read_double(fp, rho_range, "Hough::read", "", "missing hough rho_range", errors);
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
        View *view{};
        hough = new Hough(view, min_x, max_x, min_y, max_y, saw_nrhos, nrhos, saw_rho_inc, rho_inc, theta_inc,
                          pixel_threshold, (int_unit == 1), min_theta, max_theta);
        hough->min_rho = min_rho;
        hough->max_rho = max_rho;
        hough->rho_range = max_rho - min_rho;
        hough->initialize_accumulator();
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
 * @return
 */
double Hough::rho_index_to_rho(int rho_index) const {
    assert(is_rho_index_valid(rho_index));
    double rho = (rho_index * rho_range) / (nrhos - 1) + min_rho;
    return rho;
}
/**
 * @brief
 * @param rho
 * @return
 */
int Hough::rho_to_rho_index(double rho) const {
    assert(rho >= min_rho && rho <= max_rho);
    double rho_index_double = (nrhos - 1) * (rho - min_rho) / rho_range;
    int rho_index = wb_utils::double_to_int_round(rho_index_double);
    assert(is_rho_index_valid(rho_index));
    return rho_index;
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
 * @param theta
 * @return
 */
int Hough::theta_index_to_theta(int theta_index) const { return polar_trig->theta_index_to_theta(theta_index); }
/**
 * @brief
 * @param theta
 * @return
 */
int Hough::theta_to_theta_index(int theta) const { return polar_trig->theta_to_theta_index(theta); }
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
        for (int rho_index = 0; rho_index < nrhos; rho_index++) {
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
    // TODO: use wb_utils::write_bool/double/int(...)
    wb_utils::write_bool(fp, saw_rho_inc, "Hough::write", "", "cannot write Hough accumulator saw_rho_inc", errors);
    if (!errors.has_error())
        wb_utils::write_double(fp, rho_inc, "Hough::write", "", "cannot write Hough accumulator rho_inc", errors);
    if (!errors.has_error())
        wb_utils::write_bool(fp, saw_nrhos, "Hough::write", "", "cannot write Hough accumulator saw_nrhos", errors);
    if (!errors.has_error())
        wb_utils::write_int(fp, nrhos, "Hough::write", "", "cannot write Hough accumulator nrhos", errors);
    if (!errors.has_error())
        wb_utils::write_double(fp, min_rho, "Hough::write", "", "cannot write Hough accumulator min_rho", errors);
    if (!errors.has_error())
        wb_utils::write_double(fp, max_rho, "Hough::write", "", "cannot write Hough accumulator max_rho", errors);
    if (!errors.has_error())
        wb_utils::write_double(fp, rho_range, "Hough::write", "", "cannot write Hough accumulator rho_range", errors);
    int theta_inc = get_theta_inc();
    if (!errors.has_error())
        wb_utils::write_int(fp, theta_inc, "Hough::write", "", "cannot write Hough accumulator theta_inc", errors);
    double min_x = get_min_x();
    if (!errors.has_error())
        wb_utils::write_double(fp, min_x, "Hough::write", "", "cannot write Hough accumulator min_x", errors);
    double max_x = get_max_x();
    if (!errors.has_error())
        wb_utils::write_double(fp, max_x, "Hough::write", "", "cannot write Hough accumulator max_x", errors);
    double min_y = get_min_y();
    if (!errors.has_error())
        wb_utils::write_double(fp, min_y, "Hough::write", "", "cannot write Hough accumulator min_y", errors);
    double max_y = get_max_y();
    if (!errors.has_error())
        wb_utils::write_double(fp, max_y, "Hough::write", "", "cannot write Hough accumulator max_y", errors);
    if (!errors.has_error())
        wb_utils::write_int(fp, pixel_threshold, "Hough::write", "", "cannot write Hough accumulator pixel_threshold",
                            errors);
    int int_unit = (unit ? 1 : 0);
    if (!errors.has_error())
        wb_utils::write_int(fp, int_unit, "Hough::write", "", "cannot write Hough accumulator unit", errors);
    int min_theta = get_min_theta();
    if (!errors.has_error())
        wb_utils::write_int(fp, min_theta, "Hough::write", "", "cannot write Hough accumulator min_theta", errors);
    int max_theta = get_max_theta();
    if (!errors.has_error())
        wb_utils::write_int(fp, max_theta, "Hough::write", "", "cannot write Hough accumulator max_theta", errors);
    if (!errors.has_error())
        wb_utils::write_int_buffer(fp, accumulator.get(), nbins, "Hough::write", "",
                                   "cannot write Hough accumulator data ", errors);
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Hough::write_peak_lines(FILE *fp, Errors &errors) const {
    size_t npeaks = peaks.size();
    wb_utils::write_int(fp, npeaks, "Hough::write_peak_lines", "", "cannot write Hough peak line count", errors);
    int theta_inc = get_theta_inc();
    if (!errors.has_error())
        wb_utils::write_int(fp, theta_inc, "Hough::write_peak_lines", "", "cannot write Hough theta_inc", errors);
    if (!errors.has_error())
        wb_utils::write_int(fp, nrhos, "Hough::write_peak_lines", "", "cannot write Hough nrhos", errors);
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
    ofs << "min_x" << delim << std::setprecision(2) << get_min_x() << std::endl;
    ofs << "max_x" << delim << std::setprecision(2) << get_max_x() << std::endl;
    ofs << "min_y" << delim << std::setprecision(2) << get_min_y() << std::endl;
    ofs << "max_y" << delim << std::setprecision(2) << get_max_y() << std::endl;
    ofs << "nrhos" << delim << nrhos << std::endl;
    ofs << "min_rho" << delim << std::setprecision(2) << min_rho << std::endl;
    ofs << "max_rho" << delim << std::setprecision(2) << max_rho << std::endl;
    ofs << "rho_inc" << delim << std::setprecision(2) << rho_inc << std::endl;
    ofs << "rho_range" << delim << std::setprecision(2) << rho_range << std::endl;
    ofs << "nthetas" << delim << get_nthetas() << std::endl;
    ofs << "min_theta" << delim << std::setprecision(2) << get_min_theta() << std::endl;
    ofs << "max_theta" << delim << std::setprecision(2) << get_max_theta() << std::endl;
    ofs << "theta_inc" << delim << get_theta_inc() << std::endl;
    ofs << "max" << delim << accumulator_stats.get_max_value() << std::endl;
    ofs << "pixel_threshold" << delim << pixel_threshold << std::endl;
    ofs << "unit" << delim << unit << std::endl;
    ofs << delim;
    for (int rho_index = 0; rho_index < nrhos; rho_index++) {
        double rho = rho_index_to_rho(rho_index);
        ofs << std::setprecision(2) << rho << delim;
    }
    ofs << std::endl;
    int theta_inc = get_theta_inc();
    int min_theta = get_min_theta();
    int max_theta = get_max_theta();
    for (int theta_index = 0; theta_index < get_nthetas(); theta_index++) {
        ofs << theta_index_to_theta(theta_index) << delim;
        for (int rho_index = 0; rho_index < nrhos; rho_index++) {
            ofs << std::setprecision(1) << get(rho_index, theta_index) << delim;
        }
        ofs << std::endl;
    }
    ofs << std::endl;
}
