#ifndef CV_WORKBENCH_SRC_IMAGE_HPP_
#define CV_WORKBENCH_SRC_IMAGE_HPP_

#include <memory>
#include <string>
#include "errors.hpp"
#include "image_header.hpp"
#include "image_line_segment.hpp"
#include "pixel.hpp"
#include "variance_stats.hpp"
#include "wb_convert_types.hpp"
#include "wb_defs.hpp"
#include "wb_log.hpp"
#include "wb_resize_types.hpp"

/**
 * Numerically Stable Parallel Computation of (Co-)Variance, Erich Schubert, Michael Gertz
 * https://dbs.ifi.uni-heidelberg.de/files/Team/eschubert/publications/SSDBM18-covariance-authorcopy.pdf
 * https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
 */

// comment for production
#define IMAGE_COMPONENT_CHECK

class Pixel_RGB {
    friend class Image;
    double red{};
    double green{};
    double blue{};

public:
    Pixel_RGB();
    Pixel_RGB(double m_red, double m_green, double m_blue);
    double diff(const Pixel_RGB &other) const;
};

class Image {
    friend class Kernel;
    Image_header image_header;
    int next_pixel{};
    // image stores one buffer per image_header->depth
    std::unique_ptr<pixel_8U[]> buf_8U;
    std::unique_ptr<pixel_32F[]> buf_32F;
    std::unique_ptr<pixel_32S[]> buf_32S;

public:
    virtual ~Image();
    Image();
    Image(int m_ncols, int m_nrows, int m_components, Image_depth m_depth, bool no_init);
    Image(int m_ncols, int m_nrows, int m_components, Image_depth m_depth, double m_value = 0.0);
    Image(const Image &image);
    Image(const Image_header &image_header);
    Image(const Image_header &image_header, double value);
    void add_8U(const pixel_8U *src, int count, Errors &errors);
    void add_32F(const pixel_32F *src, int count, Errors &errors);
    void add_32S(const pixel_32S *src, int count, Errors &errors);
    void allocate();
    bool check_color(const std::string &module, Errors &errors) const;
    bool check_grayscale(const std::string &module, Errors &errors) const;
    void check_pixel_valid(int col, int row) const;
    void clear(double value = 0.0);
    static Image *clone(const Image *image, Image_depth depth, Errors &errors);
    int col_row_to_index(int col, int row, int component = 0) const;
    Image *color_edge(Errors &errors) const;
    static Image *combine(Image *image1, Image *image2, double scale1, double scale2, double offset, Errors &errors);
    static Image *convert(const Image *image, WB_convert_types::Convert_type convert_type, Errors &errors);
    void copy(const Image *image, Errors &errors) const;
    Image *copy(int min_col, int min_row, int max_col, int max_row, Errors &errors) const;
    void draw_line_segment(const Image_line_segment &image_line_segment, double value, int component = 0) const;
    void draw_line_segment(int col1, int row1, int col2, int row2, double value, int component = 0) const;
    void draw_line_segments(const std::vector<Image_line_segment> &image_line_segments, double value,
                            int component = 0) const;
    void draw_rectangle(int col1, int row1, int col2, int row2, double value, int component = 0) const;
    void draw_rectangle_filled(int col1, int row1, int col2, int row2, double value, int component = 0) const;
    double ellipse_dist(int col, int row) const;
    double get(int col, int row, int component = 0) const;
    double get(const Pixel &pixel, int component = 0) const;
    pixel_8U get_8U(int col, int row, int component = 0) const;
    pixel_32F get_32F(int col, int row, int component = 0) const;
    pixel_32S get_32S(int col, int row, int component = 0) const;
    double get_blue(const int col, const int row) const;
    Image_depth get_depth() const;
    double get_green(const int col, const int row) const;
    int get_ncols() const;
    int get_ncomponents() const;
    int get_npixels() const;
    int get_nrows() const;
    double get_red(const int col, const int row) const;
    int get_row_stride() const;
    double get_scaled(int col, int row, double lower_in, double upper_in, double lower_out, double upper_out,
                      int component = 0) const;
    void get_stats(Variance_stats &stats) const;
    bool in_ellipse(int col, int row) const;
    void initialize(double value = 0.0);
    bool is_color() const;
    bool is_grayscale() const;
    bool is_pixel_valid(int col, int row) const;
    void log(std::vector<WB_log_entry> &log_entries) const;
    static Image *read(const std::string &path, Errors &errors);
    static Image *read(FILE *fp, Errors &errors);
    static Image *read_jpeg(const std::string &path, Errors &errors);
    static Image *read_text(const std::string &path, Errors &errors);
    static Image *read_text(std::ifstream &ifs, Errors &errors);
    static Image *resize(const Image *image, int area_ncols, int area_nrows, WB_resize_types::Resize_type resize_type);
    static Image *scale_image(const Image *image, double lower_in, double upper_in, double lower_out, double upper_out,
                              Image_depth depth, int component = 0);
    static double scale_pixel(double in_value, double lower_in, double upper_in, double lower_out, double upper_out);
    void set(int col, int row, double value, int component = 0) const;
    void set(const Pixel &pixel, double value, int component = 0) const;
    void set_8U(int col, int row, pixel_8U value, int component = 0) const;
    void set_32F(int col, int row, pixel_32F value, int component = 0) const;
    void set_32S(int col, int row, pixel_32S value, int component = 0) const;
    static Image *subtract(const Image *src_image, const Image *subtract_image, Errors &errors);
    void to_image_line_segment(Image_line_segment &image_line_segment, Line_segment &line_segment);
    void to_line_segment(Line_segment &line_segment, Image_line_segment &image_line_segment);
    void to_pixel(Pixel &pixel, double x, double y);
    void to_pixel(Pixel &pixel, Point &point);
    void to_pixel_RGB(Pixel_RGB &pixel_RGB, int col, int row) const;
    void to_point(Point &point, int col, int row);
    void to_point(Point &point, Pixel &pixel);
    std::string to_string(const std::string &prefix = "") const;
    double to_x(int col) const;
    static double to_x(int col, int ncols);
    double to_y(int row) const;
    static double to_y(int row, int nrows);
    void write(const std::string &path, Errors &errors) const;
    void write(FILE *fp, Errors &errors) const;
    void write_jpeg(const std::string &path, Errors &errors) const;
    void write_text(const std::string &path, const std::string &delim, Errors &errors) const;
    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};

#endif // CV_WORKBENCH_SRC_IMAGE_HPP_
