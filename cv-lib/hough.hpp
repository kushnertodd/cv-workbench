#ifndef CV_WORKBENCH_SRC_HOUGH_HPP_
#define CV_WORKBENCH_SRC_HOUGH_HPP_

#include <cmath>
#include <fstream>
#include <string>
#include "bounds.hpp"
#include "errors.hpp"
#include "file_utils.hpp"
#include "hough_accum.hpp"
#include "image.hpp"
#include "line_segment.hpp"
#include "pixel.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

class Hough {
public:
    int *accumulator{};
    Variance_stats accumulator_stats;
    std::list<Polar_line> lines;
    std::list<Line_segment> line_segments;
    int nbins{};
    Polar_trig polar_trig;

    ~Hough();
    Hough(Image *inimageput, int rho_inc, int theta_inc, int pixel_threshold);
    void clear();
    void find_peaks(std::list<Polar_line> &lines, double threshold);
    int get(int rho_index, int theta_index);
    int get_nrhos();
    int get_nthetas();
    void initialize(Image *image, int image_theshold);
    int pixel_theta_to_rho(int col, int row, int theta_index);
    static Hough *read(const std::string &path, Errors &errors);
    Hough *read(FILE *fp, Errors &errors);
    static Hough *read_text(std::ifstream &ifs, Errors &errors);
    int rho_theta_to_index(int rho_index, int theta_index);
    void set(int rho_index, int theta_index, int value);
    void update(int rho_index, int theta_index, int value);
    void update_accumulator_stats();
    void write(const std::string &path, Errors &errors) const;
    void write(FILE *fp, Errors &errors) const;
    void write_text(const std::string &path, const std::string &delim, Errors &errors) const;
    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
    void write_peak_lines(FILE *fp, Errors &errors) const;
    void write_peak_lines_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;

    // void find_lines(int ncols, int nrows, int nrhos, int nthetas);
    // void find_peaks(int npeaks);
    // void lines_to_line_segments(int ncols, int nrows, int nrhos, int nthetas);
};

#endif // CV_WORKBENCH_SRC_HOUGH_HPP_
