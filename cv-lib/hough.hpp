#ifndef CV_WORKBENCH_SRC_HOUGH_HPP_
#define CV_WORKBENCH_SRC_HOUGH_HPP_

#include <cmath>
#include <fstream>
#include <memory>
#include <string>
#include "bounds.hpp"
#include "errors.hpp"
#include "file_utils.hpp"
#include "image.hpp"
#include "image_line_segment.hpp"
#include "pixel.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

class Hough_peak {
public:
    double count_percentile;
    double rho;
    int theta;
    Hough_peak(double m_count_percentile, double m_rho, int m_theta);
    static bool comp(Hough_peak &x, Hough_peak &y);
    std::string to_string() const;
};

class Hough {
    friend class Histogram;
    int pixel_threshold{};
    int unit{};
    int min_theta{};
    int max_theta{};
    int nbins{};
    std::unique_ptr<Polar_trig> polar_trig;
    std::unique_ptr<int[]> accumulator;
    Variance_stats accumulator_stats;
    std::list<Polar_line> lines;
    std::list<Image_line_segment> image_line_segments;

public:
    ~Hough();
    Hough();
    Hough(double m_min_x, double m_max_x, double m_min_y, double m_max_y, int m_rho_inc, int m_theta_inc,
          int m_pixel_threshold, bool m_unit, int m_min_theta, int m_max_theta);
    void clear();
    void find_peaks(std::vector<Hough_peak> &filtered_peaks, double threshold, double rho_suppress,
                    int theta_suppress) const;
    int get(int rho_index, int theta_index) const;
    int get_max_theta() const;
    double get_max_x() const;
    double get_max_y() const;
    int get_min_theta() const;
    double get_min_x() const;
    double get_min_y() const;
    int get_nrhos() const;
    int get_nthetas() const;
    int get_rho_inc() const;
    int get_theta_inc() const;
    void initialize(Image *image, int pixel_threshold, bool unit);
    void log(std::list<WB_log_entry> &log_entries);
    static Hough *read(const std::string &path, Errors &errors);
    static Hough *read(FILE *fp, Errors &errors);
    Hough *read_text(std::ifstream &ifs, Errors &errors);
    int rho_index_theta_index_to_index(int rho_index, int theta_index) const;
    void set(int rho_index, int theta_index, int value);
    int to_rho_index(double rho) const;
    int to_theta_index(int theta) const;
    void update(int rho_index, int theta_index, int value) const;
    void update_accumulator_stats();
    void write(const std::string &path, Errors &errors) const;
    void write(FILE *fp, Errors &errors) const;
    void write_peak_lines(FILE *fp, Errors &errors) const;
    void write_peak_lines_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
    void write_text(const std::string &path, const std::string &delim, Errors &errors);
    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors);
};

#endif // CV_WORKBENCH_SRC_HOUGH_HPP_
