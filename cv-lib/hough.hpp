#ifndef CV_WORKBENCH_SRC_HOUGH_HPP_
#define CV_WORKBENCH_SRC_HOUGH_HPP_

#include <cmath>
#include <fstream>
#include <memory>
#include <string>
#include "errors.hpp"
#include "file_utils.hpp"
#include "hough_peak.hpp"
#include "image_line_segment.hpp"
#include "polar_trig.hpp"
#include "variance_stats.hpp"
#include "view.hpp"
#include "wb_utils.hpp"

/**
 * @brief
 */
class Polar_index {
    friend class Polar_trig;
    int rho_index{};
    int theta_index{};

public:
    Polar_index();
    Polar_index(int m_rho_index, int m_theta_index);
    void init(int m_rho_index, int m_theta_index);
};

class Hough {
    friend class Histogram;
    int pixel_threshold{};
    int unit{};
    int nbins{};
    bool saw_nrhos{};
    int nrhos{};
    bool saw_rho_inc{};
    double rho_inc{};
    double max_rho{};
    double min_rho{};
    View *view;
    std::unique_ptr<Polar_trig> polar_trig;
    std::unique_ptr<int[]> accumulator;
    Variance_stats accumulator_stats;
    std::vector<Image_line_segment> image_line_segments;

public:
    // TODO: make private
    std::vector<Hough_peak> peaks;
    ~Hough();
    Hough();
    Hough(View *m_view, double m_min_x, double m_max_x, double m_min_y, double m_max_y, bool m_saw_nrhos, int m_nrhos,
          bool m_saw_rho_inc, double m_rho_inc, int m_theta_inc, int m_pixel_threshold, bool m_unit, int m_min_theta,
          int m_max_theta);
    void clear();
    void find_peaks(double threshold, double rho_suppress, int theta_suppress);
    int get(int rho_index, int theta_index) const;
    int get_max_theta() const;
    double get_max_x() const;
    double get_max_y() const;
    int get_min_theta() const;
    double get_min_x() const;
    double get_min_y() const;
    int get_nrhos() const;
    int get_nthetas() const;
    int get_theta_inc() const;
    void initialize(int pixel_threshold, bool unit, int min_col, int min_row, int max_col, int max_row, Errors &errors);
    void initialize_accumulator();
    void initialize_nrhos();
    void initialize_rhos();
    bool is_rho_index_valid(int rho_index) const;
    void log(std::vector<WB_log_entry> &log_entries);
    double point_theta_index_to_rho(Point &point, int theta_index);
    double point_theta_index_to_rho(double x, double y, int theta_index) const;
    int point_theta_index_to_rho_index(Point &point, int theta_index);
    int point_theta_index_to_rho_index(double x, double y, int theta_index);
    double point_theta_to_rho(Point &point, int theta) const;
    double point_theta_to_rho(double x, double y, int theta) const;
    int point_theta_to_rho_index(Point &point, int theta);
    int point_theta_to_rho_index(double x, double y, int theta);
    static Hough *read(const std::string &path, Errors &errors);
    static Hough *read(FILE *fp, Errors &errors);
    Hough *read_text(std::ifstream &ifs, Errors &errors);
    int rho_index_theta_index_to_index(int rho_index, int theta_index) const;
    double rho_index_to_rho(int rho_index) const;
    int rho_to_rho_index(double rho) const;
    void set(int rho_index, int theta_index, int value);
    int theta_index_to_theta(int theta_index) const;
    int theta_to_theta_index(int theta) const;
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
