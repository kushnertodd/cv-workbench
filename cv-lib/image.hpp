//
// Created by kushn on 6/11/2022.
//

#ifndef CV_WORKBENCH_SRC_IMAGE_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HPP_

#include <string>
#include "errors.hpp"
#include "image_header.hpp"
#include "line_segment.hpp"
#include "wb_log.hpp"
#include "point.hpp"
#include "variance_stats.hpp"
#include "wb_defs.hpp"

/**
 * Numerically Stable Parallel Computation of (Co-)Variance, Erich Schubert, Michael Gertz
 * https://dbs.ifi.uni-heidelberg.de/files/Team/eschubert/publications/SSDBM18-covariance-authorcopy.pdf
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
 */

// comment for production
#define IMAGE_COMPONENT_CHECK

class Image {
    friend class Kernel;
    Image_header image_header;
    int next_pixel{};
    // image stores one buffer per image_header->depth
    pixel_8U *buf_8U{};
    pixel_32F *buf_32F{};
    pixel_32S *buf_32S{};

public:
    virtual ~Image();

    Image();

    Image(int m_rows, int m_cols, int m_components, Image_depth m_depth, double value = 0.0);

    Image(const Image &image);

    explicit Image(const Image_header &image_header, double value = 0.0);

    void add_8U(const pixel_8U *src, int count, Errors &errors);

    void add_32F(const pixel_32F *src, int count, Errors &errors);

    void add_32S(const pixel_32S *src, int count, Errors &errors);

    bool check_color(const std::string &module, Errors &errors) const;

    bool check_grayscale(const std::string &module, Errors &errors) const;

    static Image *clone(const Image *image, Image_depth depth, Errors &errors);

    Image *color_edge(Image *src, Errors &errors) const;

    static Image *combine(Image *image1, Image *image2, double scale1, double scale2, double offset,
                          Errors &errors);

    void copy(const Image *image, Errors &errors) const;

    void draw_line_segment(const Line_segment &line_segment, double value, int component = 0) const;

    void draw_line_segment(int row1, int col1, int row2, int col2, double value, int component = 0) const;

    void draw_line_segments(const std::list<Line_segment> &line_segments, double value, int component = 0) const;

    void draw_rectangle(int row1, int col1, int row2, int col2, double value, int component = 0) const;

    void draw_rectangle_filled(int row1, int col1, int row2, int col2, double value, int component = 0) const;

    double get(int row, int col, int component = 0) const;

    double get(const Point &point, int component = 0) const;

    pixel_8U get_8U(int row, int col, int component = 0) const;

    pixel_32F get_32F(int row, int col, int component = 0) const;

    pixel_32S get_32S(int row, int col, int component = 0) const;

    double get_blue(const int row, const int col) const;

    int get_cols() const;

    double get_green(const int row, const int col) const;

    double get_red(const int row, const int col) const;

    int get_components() const;

    Image_depth get_depth() const;

    int get_npixels() const;

    int get_row_stride() const;

    int get_rows() const;

    double get_scaled(int row, int col, double lower_in,
                      double upper_in, double lower_out,
                      double upper_out, int component = 0) const;

    void get_stats(Variance_stats &stats) const;
    void init(double value = 0.0);

    bool is_color() const;

    bool is_grayscale() const;

    void log(std::list<WB_log_entry> &log_entries) const;

    static Image *read(const std::string &path, Errors &errors);

    static Image *read(FILE *fp, Errors &errors);

    static Image *read_text(const std::string &path, Errors &errors);

    static Image *read_text(std::ifstream &ifs, Errors &errors);

    static Image *read_jpeg(const std::string &path, Errors &errors);

    int row_col_to_index(int row, int col, int component = 0) const;

    static Image *scale_image(const Image *image, double lower_in,
                              double upper_in, double lower_out,
                              double upper_out, Image_depth depth, int component = 0);

    static double scale_pixel(double in_value, double lower_in,
                              double upper_in, double lower_out,
                              double upper_out);

    static Image *subtract(const Image *src_image, const Image *subtract_image, Errors &errors);

    void set(int row, int col, double value, int component = 0) const;

    void set(const Point &point, double value, int component = 0) const;

    void set_8U(int row, int col, pixel_8U value, int component = 0) const;

    void set_32F(int row, int col, pixel_32F value, int component = 0) const;

    void set_32S(int row, int col, pixel_32S value, int component = 0) const;

    std::string to_string(const std::string &prefix = "") const;

    void write(const std::string &path, Errors &errors) const;

    void write(FILE *fp, Errors &errors) const;

    void write_text(const std::string &path, const std::string &delim, Errors &errors) const;

    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;

    void write_jpeg(const std::string &path, Errors &errors) const;
};

#endif //CV_WORKBENCH_SRC_IMAGE_HPP_
