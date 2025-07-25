#include "histogram.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include "errors.hpp"
#include "file_utils.hpp"
#include "wb_utils.hpp"

extern bool debug;

/**
 * @brief
 */
Histogram::~Histogram() {}
/**
 * @brief
 */
Histogram::Histogram() = default;
/**
 * @brief
 * @param m_nbins
 * @param m_lower_value
 * @param m_upper_value
 */
Histogram::Histogram(int m_nbins, double m_lower_value, double m_upper_value) :
    nbins(m_nbins), lower_value(m_lower_value), upper_value(m_upper_value) {
    bins = std::make_unique<int[]>(nbins);
    for (int i = 0; i < nbins; i++)
        bins[i] = 0;
}
/**
 * @brief
 * @param image
 * @param nbins
 * @param lower_value
 * @param upper_value
 * @param saw_lower_value
 * @param saw_upper_value
 * @return
 */
Histogram *Histogram::create_image(Image *image, int nbins, double lower_value, bool saw_lower_value,
                                   double upper_value, bool saw_upper_value) {
    auto *histogram = new Histogram(nbins, lower_value, upper_value);
    histogram->initialize_image(image, lower_value, saw_lower_value, upper_value, saw_upper_value);
    return histogram;
}
/**
 * @brief
 * @param hough
 * @param nbins
 * @param lower_value
 * @param upper_value
 * @param saw_lower_value
 * @param saw_upper_value
 * @return
 */
Histogram *Histogram::create_hough(Hough *hough, int nbins, double lower_value, bool saw_lower_value,
                                   double upper_value, bool saw_upper_value) {
    auto *histogram = new Histogram(nbins, lower_value, upper_value);
    histogram->initialize_hough(hough, lower_value, saw_lower_value, upper_value, saw_upper_value);
    return histogram;
}
/**
 * @brief
 * @param hough
 * @param npeaks
 */
void Histogram::find_hough_peaks(Hough *hough, int npeaks) {
    const int nbins = 1000;
    Histogram *histogram = create_hough(hough, nbins, 0, 0, false, false);
    int peak_ct = 0;
    double threshold = 0.0;
    for (int i = nbins - 1; i >= 0 && peak_ct < npeaks; i--) {
        peak_ct += histogram->bins[i];
        if (peak_ct <= npeaks) {
            threshold = histogram->to_value(i);
        }
    }
    // TODO: define
    // hough->find_peaks(hough->lines, threshold);
}
/**
 * @brief
 * @param value
 * @return
 */
int Histogram::to_bin(double value) const {
    if (value < lower_value)
        return 0;
    else if (value > upper_value)
        return nbins - 1;
    else
        return wb_utils::double_to_int_round((nbins - 1) * (value - lower_value) / (upper_value - lower_value));
}
/**
 * @brief
 * @param bin
 * @return
 */
float Histogram::to_value(int bin) const {
    double frac = (upper_value - lower_value) / (nbins - 1);
    return wb_utils::double_to_float(bin * frac + lower_value);
}
/**
 * @brief
 * @return
 */
double Histogram::get_lower_value() const { return lower_value; }
/**
 * @brief
 * @return
 */
double Histogram::get_max_value() const { return input_value_stats.get_max_value(); }
/**
 * @brief
 * @return
 */
double Histogram::get_min_value() const { return input_value_stats.get_min_value(); }
/**
 * @brief
 * @return
 */
double Histogram::get_upper_value() const { return upper_value; }
/**
 * @brief
 * @param hough
 * @param saw_lower_value
 * @param saw_upper_value
 */
void Histogram::initialize_hough(Hough *hough, double in_lower_value, bool saw_lower_value, double in_upper_value,
                                 bool saw_upper_value) {
    for (int theta_index = 0; theta_index < hough->get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < hough->get_nrhos(); rho_index++) {
            double value = hough->get(rho_index, theta_index);
            input_value_stats.update(value);
        }
    }
    input_value_stats.finalize();
    if (!saw_lower_value)
        lower_value = input_value_stats.get_min_value();
    else
        lower_value = in_lower_value;
    if (!saw_upper_value)
        upper_value = input_value_stats.get_max_value();
    else
        upper_value = in_upper_value;
    for (int theta_index = 0; theta_index < hough->get_nthetas(); theta_index++) {
        for (int rho_index = 0; rho_index < hough->get_nrhos(); rho_index++) {
            double value = hough->get(rho_index, theta_index);
            if (value >= lower_value && value <= upper_value)
                update(value);
        }
    }
    update_bin_count_bounds();
}
/**
 * @brief
 * @param image
 * @param saw_lower_value
 * @param saw_upper_value
 */
void Histogram::initialize_image(Image *image, double in_lower_value, bool saw_lower_value, double in_upper_value,
                                 bool saw_upper_value) {
    for (int col = 0; col < image->get_ncols(); col++) {
        for (int row = 0; row < image->get_nrows(); row++) {
            double value = image->get(col, row);
            input_value_stats.update(value);
        }
    }
    input_value_stats.finalize();
    lower_value = (saw_lower_value ? in_lower_value : input_value_stats.get_min_value());
    upper_value = (saw_upper_value ? in_upper_value : input_value_stats.get_max_value());
    bin_count_bounds.set(lower_value, upper_value);
    for (int col = 0; col < image->get_ncols(); col++) {
        for (int row = 0; row < image->get_nrows(); row++) {
            double value = image->get(col, row);
            if (value >= lower_value && value <= upper_value)
                update(value);
        }
    }
    update_bin_count_bounds();
}
/**
 * @brief
 * @param log_entries
 */
void Histogram::log(std::vector<WB_log_entry> &log_entries) {
    WB_log_entry log_entry_lower_value("lower-value", wb_utils::double_to_string(lower_value));
    log_entries.push_back(log_entry_lower_value);
    WB_log_entry log_entry_upper_value("upper_value", wb_utils::double_to_string(upper_value));
    log_entries.push_back(log_entry_upper_value);
    WB_log_entry log_entry_pixel_count("pixel count", wb_utils::int_to_string(input_value_stats.get_count()));
    log_entries.push_back(log_entry_pixel_count);
    WB_log_entry log_entry_pixel_mean("pixel mean", wb_utils::double_to_string(input_value_stats.get_mean()));
    log_entries.push_back(log_entry_pixel_mean);
    WB_log_entry log_entry_pixel_standard_deviation(
            "pixel standard deviation", wb_utils::double_to_string(input_value_stats.get_standard_deviation()));
    log_entries.push_back(log_entry_pixel_standard_deviation);
    WB_log_entry log_entry_pixel_min_value("min pixel value",
                                           wb_utils::double_to_string(input_value_stats.get_min_value()));
    log_entries.push_back(log_entry_pixel_min_value);
    WB_log_entry log_entry_pixel_max_value("max pixel value",
                                           wb_utils::double_to_string(input_value_stats.get_max_value()));
    log_entries.push_back(log_entry_pixel_max_value);
    WB_log_entry log_entry_bin_min_count(
            "min bin count", wb_utils::int_to_string(wb_utils::double_to_int_round(bin_count_bounds.get_min_value())));
    log_entries.push_back(log_entry_bin_min_count);
    WB_log_entry log_entry_bin_max_count(
            "max bin count", wb_utils::int_to_string(wb_utils::double_to_int_round(bin_count_bounds.get_max_value())));
    log_entries.push_back(log_entry_bin_max_count);
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
Histogram *Histogram::read(std::string &path, Errors &errors) {
    FILE *fp = file_utils::open_file_read(path, errors);
    Histogram *histogram = nullptr;
    if (fp) {
        histogram = Histogram::read(fp, errors);
        fclose(fp);
    }
    return histogram;
}
/**
 * @brief
 * @param fp
 * @param errors
 * @return
 */
Histogram *Histogram::read(FILE *fp, Errors &errors) {
    auto *histogram = new Histogram();
    if (fp == nullptr)
        return nullptr;
    wb_utils::read_int(fp, histogram->nbins, "Histogram::read", "", "missing nbins", errors);
    if (errors.has_error()) {
        delete histogram;
        return nullptr;
    }
    float lower_value_float = 0.0;
    wb_utils::read_float(fp, lower_value_float, "Histogram::read", "", "missing lower_value", errors);
    if (errors.has_error()) {
        delete histogram;
        return nullptr;
    }
    histogram->lower_value = lower_value_float;
    float upper_value_float = 0.0;
    wb_utils::read_float(fp, upper_value_float, "Histogram::read", "", "missing upper_value", errors);
    if (errors.has_error()) {
        delete histogram;
        return nullptr;
    }
    histogram->upper_value = upper_value_float;
    histogram->bins = std::make_unique<int[]>(histogram->nbins);
    wb_utils::read_int_buffer(fp, histogram->bins.get(), histogram->nbins, "Histogram::read", "", "cannot read data",
                              errors);
    if (errors.has_error()) {
        delete histogram;
        return nullptr;
    }
    histogram->update_bin_count_bounds();
    return histogram;
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
Histogram *Histogram::read_text(const std::string &path, Errors &errors) { return nullptr; }
/**
 * @brief
 * @param ifs
 * @param errors
 * @return
 */
Histogram *Histogram::read_text(std::ifstream &ifs, Errors &errors) { return nullptr; }
/**
 * @brief
 * @param prefix
 * @return
 */
std::string Histogram::to_string(const std::string &prefix) {
    std::ostringstream os{};
    os << "histogram:" << std::endl
       << prefix << "    " << std::setw(20) << std::left << "nbins " << nbins << std::endl
       << prefix << "    " << std::setw(20) << std::left << "lower_value " << lower_value << std::endl
       << prefix << "    " << std::setw(20) << std::left << "upper_value " << upper_value << std::endl
       << prefix << "    " << bin_count_bounds.to_string(prefix + "    ") << prefix << "    "
       << input_value_stats.to_string(prefix + "    ");
    return os.str();
}
/**
 * @brief
 * @param value
 */
void Histogram::update(double value) const {
    int bin = to_bin(value);
    bins[bin]++;
}
/**
 * @brief
 */
void Histogram::update_bin_count_bounds() {
    for (int i = 0; i < nbins; i++)
        bin_count_bounds.update(bins[i]);
}
/**
 * @brief
 * @param path
 * @param errors
 */
void Histogram::write(std::string &path, Errors &errors) const {}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Histogram::write(FILE *fp, Errors &errors) const {
    wb_utils::write_int(fp, nbins, "Histogram::write", "", "cannot write nbins", errors);
    if (!errors.has_error())
        wb_utils::write_float(fp, wb_utils::double_to_float(lower_value), "Histogram::write", "",
                              "cannot write lower_value", errors);
    if (!errors.has_error())
        wb_utils::write_float(fp, wb_utils::double_to_float(upper_value), "Histogram::write", "",
                              "cannot write upper_value", errors);
    if (!errors.has_error())
        input_value_stats.write(fp, errors);
    if (!errors.has_error())
        wb_utils::write_int_buffer(fp, bins.get(), nbins, "Histogram::write", "", "cannot write bins'", errors);
}
/**
 * @brief
 * @param wb_filename
 */
void Histogram::write_gp_script(const Wb_filename &wb_filename) {
    std::string script_filename = wb_filename.to_hist_script();
    std::string data_filename = wb_filename.to_hist_text();
    std::ofstream ofs(script_filename, std::ofstream::out);
    ofs << "set style line 1 \\" << std::endl;
    ofs << "    linecolor rgb '#0060ad' \\" << std::endl;
    ofs << "    linetype 1 linewidth 2 \\" << std::endl;
    ofs << "    pointtype 7 pointsize 0" << std::endl;
    ofs << "plot './" << data_filename << "' with linespoints linestyle 1" << std::endl;

    ofs << "pause -1 \"Hit any key to continue\"" << std::endl;
    ofs.close();
}
/**
 * @brief
 * path excludes extension, so write_text() can add .txt for text and .gp for gnuplot script
 * @param path
 * @param delim
 * @param errors
 */
void Histogram::write_text(std::string &path, const std::string &delim, Errors &errors) const {
    Wb_filename wb_filename(path, path, "", WB_data_format::Data_format::TEXT);
    std::ofstream ofs = file_utils::open_file_write_text(wb_filename.to_hist_text(), errors);
    if (errors.has_error())
        return;
    int start_bin = to_bin(lower_value);
    int end_bin = to_bin(upper_value);
    for (int i = start_bin; i < end_bin; i++) {
        double value = to_value(i);
        int count = bins[i];
        ofs << wb_utils::double_to_int(value) << delim << count << std::endl;
    }
    ofs << std::endl;
    ofs.close();
    write_gp_script(wb_filename);
}
