#ifndef SRC__HOUGH_ACCUM_HPP_
#define SRC__HOUGH_ACCUM_HPP_

#include <cmath>
#include <fstream>
#include "bounds.hpp"
#include "errors.hpp"
#include "file_utils.hpp"
#include "image.hpp"
#include "line_segment.hpp"
#include "pixel.hpp"
#include "polar_line.hpp"
#include "polar_trig.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"
#include "wb_utils.hpp"

class Hough_accum {
    int nbins{};
    Polar_trig *polar_trig{};
    int *rho_theta_counts{};
    Variance_stats accumulator_stats;

public:
    ~Hough_accum();
    Hough_accum();
    Hough_accum(int m_ncols, int m_nrows, int m_rho_inc, int m_theta_inc);
    //  bool clip_window(Line_segment &line_segment, Polar_line &line) const;
    //  double col_to_x(int col) const;
    static Hough_accum *create_image(Image *image, int rho_inc, int theta_inc, int pixel_threshold = 0);
    void find_peaks(std::list<Polar_line> &lines, double threshold);
    int get(int rho_index, int theta_index);
    int get_nrhos();
    int get_nthetas();
    void initialize(Image *image, int image_theshold);
    static Hough_accum *read(FILE *fp, Errors &errors);
    static Hough_accum *read_text(std::ifstream &ifs, Errors &errors);
    int rho_theta_to_index(int rho_index, int theta_index);
    void set(int rho_index, int theta_index, int value);
    void update(int rho_index, int theta_index, int value);
    void update_accumulator_stats();
    void write(FILE *fp, Errors &errors) const;
    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors);
};
#endif // SRC__HOUGH_ACCUM_HPP_
