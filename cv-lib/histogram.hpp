#ifndef CV_WORKBENCH_SRC_HISTOGRAM_HPP_
#define CV_WORKBENCH_SRC_HISTOGRAM_HPP_

#include <memory>
#include "errors.hpp"
#include "hough.hpp"
#include "image.hpp"
#include "variance_stats.hpp"
#include "wb_filename.hpp"

/**
 * @brief The histogram for the input image pixel values or Hough accumulator bin counts
 *
 * min_count           bounds.min_value          The lowest count for any histogram bin
 * max_count           bounds.max_value          The largest count for any histogram bin
 * total_count         stats.count               The total input value count
 * mean                stats.mean                The input value mean
 * variance            stats.variance            The input value variance
 * sample variance     stats.sample_variance     The input value sample variance
 * standard deviation  stats.standard_deviation  The input value standard deviation
 * min_value           stats.bounds.min_value    The overall minimum input value
 * max_value           stats.bounds.max_value    The overall maximum input value
 */
class Histogram {
    std::unique_ptr<int[]> bins;
    int nbins{};
    double lower_value{};
    double upper_value{};
    Bounds bin_count_bounds;
    Variance_stats input_value_stats;

public:
    ~Histogram();
    Histogram();
    Histogram(int m_nbins, double m_lower_value, double m_upper_value);
    static Histogram *create_hough(Hough *input, int nbins, double in_lower_value, bool saw_lower_value,
                                   double in_upper_value, bool saw_upper_value);
    static Histogram *create_image(Image *input, int nbins, double in_lower_value, bool saw_lower_value,
                                   double in_upper_value, bool saw_upper_value);
    static void find_hough_peaks(Hough *hough, int npeaks);
    int to_bin(double value) const;
    float to_value(int bin) const;
    double get_lower_value() const;
    double get_max_value() const;
    double get_min_value() const;
    double get_upper_value() const;
    void initialize_hough(Hough *hough, double lower_value, bool saw_lower_value, double upper_value,
                          bool saw_upper_value);
    void initialize_image(Image *image, double lower_value, bool saw_lower_value, double upper_value,
                          bool saw_upper_value);
    void log(std::vector<WB_log_entry> &log_entries);
    static Histogram *read(std::string &path, Errors &errors);
    static Histogram *read(FILE *fp, Errors &errors);
    static Histogram *read_text(const std::string &path, Errors &errors);
    static Histogram *read_text(std::ifstream &ifs, Errors &errors);
    std::string to_string(const std::string &prefix = "");
    void update(double new_value) const;
    void update_bin_count_bounds();
    void write(std::string &path, Errors &errors) const;
    void write(FILE *fp, Errors &errors) const;
    static void write_gp_script(const Wb_filename &wb_filename);
    void write_text(std::string &path, const std::string &delim, Errors &errors) const;
};

#endif // CV_WORKBENCH_SRC_HISTOGRAM_HPP_
