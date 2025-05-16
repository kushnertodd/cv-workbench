#include "image.hpp"
#include <cassert>
#include <cmath>
#include <csetjmp>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "file_utils.hpp"
#include "image_depth.hpp"
#include "jpeglib.h"
#include "wb_utils.hpp"

extern bool debug;

/**
 * @brief
 */
Pixel_RGB::Pixel_RGB() {}
/**
 * @brief
 * @param m_red
 * @param m_green
 * @param m_blue
 */
Pixel_RGB::Pixel_RGB(double m_red, double m_green, double m_blue) : red(m_red), green(m_green), blue(m_blue) {};
/**
 * @brief
 * @param other
 * @return
 */
double Pixel_RGB::diff(const Pixel_RGB &other) const {
    return sqrt((other.red - red) * (other.red - red) + (other.green - green) * (other.green - green) +
                (other.blue - blue) * (other.blue - blue));
}
/**
 * @brief
 */
Image::~Image() {}
/**
 * @brief
 */
Image::Image() = default;
/**
 * @brief
 * @param m_ncols
 * @param m_nrows
 * @param m_components
 * @param m_depth
 * @param value
 */
Image::Image(int m_ncols, int m_nrows, int m_components, Image_depth m_depth) :
    image_header(m_ncols, m_nrows, m_components, m_depth) {
    allocate();
}
/**
 * @brief
 * @param m_ncols
 * @param m_nrows
 * @param m_components
 * @param m_depth
 * @param value
 */
Image::Image(int m_ncols, int m_nrows, int m_components, Image_depth m_depth, double m_value) :
    Image(m_ncols, m_nrows, m_components, m_depth) {
    initialize(m_value);
}
/**
 * @brief
 * @param image
 */
Image::Image(const Image &image) :
    image_header(image.get_ncols(), image.get_nrows(), image.get_ncomponents(), image.get_depth()) {
    Errors errors;
    allocate();
    copy(&image, errors);
}
/**
 * @brief
 * @param m_image_header
 * @param value
 */
Image::Image(const Image_header &m_image_header) : image_header(m_image_header) {
    if (debug)
        std::cout << "Image::Image: " << to_string() << std::endl;
    allocate();
}
/**
 * @brief
 * @param m_image_header
 * @param value
 */
Image::Image(const Image_header &m_image_header, double m_value) : Image(m_image_header) {
    if (debug)
        std::cout << "Image::Image: " << to_string() << std::endl;
    initialize(m_value);
}
/**
 * @brief
 * @param src
 * @param count
 * @param errors
 */
void Image::add_8U(const pixel_8U *src, int count, Errors &errors) {
    assert(next_pixel + count <= get_npixels());
    for (int i = 0; i < count; i++) {
        switch (get_depth()) {
            case Image_depth::CV_8U:
                buf_8U[next_pixel++] = src[i];
                break;

            case Image_depth::CV_32S:
                buf_32S[next_pixel++] = src[i];
                break;

            case Image_depth::CV_32F:
                buf_32F[next_pixel++] = src[i];
                break;

            default:
                break;
        }
    }
}
/**
 * @brief
 * @param src
 * @param count
 * @param errors
 */
void Image::add_32F(const pixel_32F *src, int count, Errors &errors) {
    assert(next_pixel + count <= get_npixels());
    for (int i = 0; i < count; i++) {
        switch (get_depth()) {
            case Image_depth::CV_8U:
                errors.add("Image::add_32F", "", "cannot update_input_value to 8U buffer");
                break;

            case Image_depth::CV_32S:
                buf_32S[next_pixel++] = wb_utils::float_to_int_round(src[i]);
                break;

            case Image_depth::CV_32F:
                buf_32F[next_pixel++] = src[i];
                break;

            default:
                break;
        }
    }
}
/**
 * @brief
 * @param src
 * @param count
 * @param errors
 */
void Image::add_32S(const pixel_32S *src, int count, Errors &errors) {
    assert(next_pixel + count <= get_npixels());
    if (get_depth() == Image_depth::CV_8U) {
        errors.add("Image::add_32S", "", "cannot update_input_value to 8U buffer");
        return;
    }
    for (int i = 0; i < count; i++) {
        switch (get_depth()) {
            case Image_depth::CV_8U:
                break;

            case Image_depth::CV_32S:
                buf_32S[next_pixel++] = src[i];
                break;

            case Image_depth::CV_32F:
                buf_32F[next_pixel++] = wb_utils::int_to_float(src[i]);
                break;

            default:
                break;
        }
    }
}
/**
 * @brief
 * @param value
 */
void Image::allocate() {
    int size = get_npixels();
    switch (get_depth()) {
        case Image_depth::CV_8U: {
            buf_8U = std::make_unique<pixel_8U[]>(size);
            break;
        }
        case Image_depth::CV_32S: {
            buf_32S = std::make_unique<pixel_32S[]>(size);
            break;
        }
        case Image_depth::CV_32F: {
            buf_32F = std::make_unique<pixel_32F[]>(size);
            break;
        }
        default:
            break;
    }
}
/**
 * @brief
 * @param module
 * @param errors
 * @return
 */
bool Image::check_color(const std::string &module, Errors &errors) const {
    if (get_ncomponents() != 3) {
        errors.add(module, "", "image not color");
        return false;
    }
    return true;
}
/**
 * @brief
 * @param module
 * @param errors
 * @return
 */
bool Image::check_grayscale(const std::string &module, Errors &errors) const {
    if (get_ncomponents() != 1) {
        errors.add(module, "", "image not grayscale");
        return false;
    }
    return true;
}
/**
 * @brief
 * @param col
 * @param row
 */
void Image::check_pixel_valid(int col, int row) const { assert(!is_pixel_valid(col, row)); }
/**
 * @brief
 * @param value
 */
void Image::clear(double value) { initialize(0.0); }
/***
 * Not really what want. Doesn't copy contents.
 * @param image
 * @param depth
 * @param errors
 * @return
 */
Image *Image::clone(const Image *image, Image_depth depth, Errors &errors) {
    auto *new_image = new Image(image->get_ncols(), image->get_nrows(), image->get_ncomponents(), depth);
    new_image->copy(image, errors);
    return new_image;
}
/**
 * @brief
 * @param col
 * @param row
 * @param component
 * @return
 */
int Image::col_row_to_index(int col, int row, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
    if (!is_pixel_valid(col, row))
        int i = 0;
    assert(is_pixel_valid(col, row));
#endif
    return row * get_row_stride() + col * get_ncomponents() + component;
}
/**
 * @brief color edge detection
 * @param errors
 * @return
 */
Image *Image::color_edge(Errors &errors) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(is_color());
#endif
    int nrows = get_nrows();
    int ncols = get_ncols();
    int row_lower = 1;
    int row_upper = nrows - 2;
    int col_lower = 1;
    int col_upper = ncols - 2;
    auto *out = new Image(ncols, nrows, COMPONENTS_GRAYSCALE, Image_depth::CV_32F);
    out->clear(0.0);
    if (debug)
        std::cout << "col_lower " << col_lower << " col_upper " << col_upper << " row_lower " << row_lower
                  << " row_upper " << row_upper << std::endl;
    for (int col = col_lower; col <= col_upper; col++) {
        if (debug)
            std::cout << "col " << col << std::endl;
        for (int row = row_lower; row <= row_upper; row++) {
            if (debug)
                std::cout << "row " << row << std::endl;
            Pixel_RGB image_center;
            to_pixel_RGB(image_center, col, row);
            Pixel_RGB image_up;
            to_pixel_RGB(image_up, col, row - 1);
            Pixel_RGB image_down;
            to_pixel_RGB(image_down, col, row + 1);
            Pixel_RGB image_left;
            to_pixel_RGB(image_left, col, row - 1);
            Pixel_RGB image_right;
            to_pixel_RGB(image_right, col, row + 1);
            double sum = image_up.diff(image_center) + image_down.diff(image_center) + image_left.diff(image_center) +
                         image_right.diff(image_center);
            out->set(col, row, sum);
        }
    }
    return out;
}
/**
 * @brief return linear combination of input images:
 * pixel_32F output-pixel = image1-pixel * scale1 + image2-pixel * scale2 + offset;
 * @param input1
 * @param input2
 * @param scale1
 * @param scale2
 * @param offset
 * @param errors
 * @return
 */
Image *Image::combine(Image *input1, Image *input2, double scale1, double scale2, double offset, Errors &errors) {
    int ncols1;
    int ncols2;
    int nrows1;
    int nrows2;

    ncols1 = input1->get_ncols();
    ncols2 = input2->get_ncols();
    nrows1 = input1->get_nrows();
    nrows2 = input2->get_nrows();
    if (ncols1 != ncols2 || nrows1 != nrows2) {
        std::ostringstream os;
        os << "input1 size (" << ncols1 << ", " << nrows1 << ") not the same as input2 size (" << ncols2 << ", "
           << nrows2 << ")";
        errors.add("Operator_transform_image_combine::run", "", os.str());
    }
    auto combine_image = new Image(ncols1, nrows1, 1, Image_depth::CV_32F);
    for (int col = 0; col < ncols1; col++) {
        for (int row = 0; row < nrows1; row++) {
            double pixel1 = input1->get(col, row);
            double pixel2 = input2->get(col, row);
            double value = pixel1 * scale1 + pixel2 * scale2 + offset;
            combine_image->set(col, row, value);
        }
    }
    return combine_image;
}
/**
 * @brief
 * @param image
 * @param errors
 */
void Image::copy(const Image *image, Errors &errors) const {
    if (get_npixels() != image->get_npixels()) {
        errors.add("Image::copy", "", "images not the same size ");
        return;
    }
    if (get_depth() != image->get_depth()) {
        errors.add("Image::copy", "", "images not the same depth ");
        return;
    }
    if (get_depth() == Image_depth::CV_8U && image->get_depth() == Image_depth::CV_32S) {
        errors.add("Image::copy", "", "cannot copy CV_32S image to CV_8U image ");
        return;
    }
    if (get_depth() == Image_depth::CV_8U && image->get_depth() == Image_depth::CV_32F) {
        errors.add("Image::copy", "", "cannot copy CV_32F image to CV_8U image ");
        return;
    }
    if (get_depth() == Image_depth::UNDEFINED || image->get_depth() == Image_depth::UNDEFINED) {
        errors.add("Image::copy", "", "cannot copy images of undefined depth ");
        return;
    }
    int size = get_npixels();
    switch (get_depth()) {
        case Image_depth::CV_8U:
            for (int i = 0; i < size; i++) {
                buf_8U[i] = image->buf_8U[i];
            }
            break;

        case Image_depth::CV_32S:
            switch (image->get_depth()) {
                case Image_depth::CV_8U:
                    for (int i = 0; i < size; i++) {
                        buf_32S[i] = image->buf_8U[i];
                    }
                    break;
                case Image_depth::CV_32S:
                    for (int i = 0; i < size; i++) {
                        buf_32S[i] = image->buf_32S[i];
                    }
                    break;
                case Image_depth::CV_32F:
                    for (int i = 0; i < size; i++) {
                        buf_32S[i] = wb_utils::float_to_int_round(image->buf_32F[i]);
                    }
                    break;
                default:
                    break;
            }
            break;

        case Image_depth::CV_32F:
            switch (image->get_depth()) {
                case Image_depth::CV_8U:
                    for (int i = 0; i < size; i++) {
                        buf_32F[i] = image->buf_8U[i];
                    }
                    break;
                case Image_depth::CV_32S:
                    for (int i = 0; i < size; i++) {
                        buf_32F[i] = wb_utils::int_to_float(image->buf_32S[i]);
                    }
                    break;
                case Image_depth::CV_32F:
                    for (int i = 0; i < size; i++) {
                        buf_32F[i] = image->buf_32F[i];
                    }
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}
/**
 * @brief
 * @param line_segment
 * @param value
 * @param component
 */
void Image::draw_line_segment(const Image_line_segment &image_line_segment, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    for (Pixel pixel: image_line_segment.line_pixels) {
        set(pixel, value, component);
    }
}
/**
 * @brief
 * @param col1
 * @param row1
 * @param col2
 * @param row2
 * @param value
 * @param component
 */
void Image::draw_line_segment(int col1, int row1, int col2, int row2, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    Image_line_segment image_line_segment(col1, row1, col2, row2);
    for (Pixel pixel: image_line_segment.line_pixels) {
        set(pixel, value, component);
    }
}
/**
 * @brief
 * @param line_segments
 * @param value
 * @param component
 */
void Image::draw_line_segments(const std::list<Image_line_segment> &image_line_segments, double value,
                               int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    for (const Image_line_segment &image_line_segment: image_line_segments) {
        draw_line_segment(image_line_segment, value, component);
    }
}
/**
 * @brief
 * @param col1
 * @param row1
 * @param col2
 * @param row2
 * @param value
 * @param component
 */
void Image::draw_rectangle(int col1, int row1, int col2, int row2, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    Image_line_segment line_segment1(col1, row1, col1, row2);
    Image_line_segment line_segment2(col1, row2, col2, row2);
    Image_line_segment line_segment3(col2, row2, col2, row1);
    Image_line_segment line_segment4(col2, row1, col1, row1);
    draw_line_segment(line_segment1, value, component);
    draw_line_segment(line_segment2, value, component);
    draw_line_segment(line_segment3, value, component);
    draw_line_segment(line_segment4, value, component);
}
/**
 * @brief
 * @param col1
 * @param row1
 * @param col2
 * @param row2
 * @param value
 * @param component
 */
void Image::draw_rectangle_filled(int col1, int row1, int col2, int row2, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int col_min = std::min(col1, col2);
    int row_min = std::min(row1, row2);
    int col_max = std::max(col1, col2);
    int row_max = std::max(row1, row2);
    for (int col = col_min; col <= col_max; col++)
        for (int row = row_min; row <= row_max; row++)
            set(col, row, value, component);
}
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
double Image::ellipse_dist(int col, int row) const {
    double a_sq = get_ncols() * get_ncols() / 4.0;
    double b_sq = get_nrows() * get_nrows() / 4.0;
    double x = to_x(col);
    double y = to_y(row);
    double dist = x * x / a_sq + y * y / b_sq;
    return dist;
}
/**
 * @brief
 * @param col
 * @param row
 * @param component
 * @return
 */
double Image::get(const int col, const int row, const int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int index;
    switch (get_depth()) {
        case Image_depth::CV_8U:
            index = col_row_to_index(col, row, component);
            return buf_8U[index];

        case Image_depth::CV_32S:
            index = col_row_to_index(col, row, component);
            return static_cast<pixel_32F>(buf_32S[index]);

        case Image_depth::CV_32F:
            index = col_row_to_index(col, row, component);
            return buf_32F[index];

        default:
            return 0.0;
    }
}
/**
 * @brief
 * @param pixel
 * @param component
 * @return
 */
double Image::get(const Pixel &pixel, const int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    return get(pixel.col, pixel.row, component);
}
/**
 * @brief
 * @param col
 * @param row
 * @param component
 * @return
 */
auto Image::get_8U(const int col, const int row, const int component) const -> pixel_8U {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int index = col_row_to_index(col, row, component);
    return buf_8U[index];
}
/**
 * @brief
 * @param col
 * @param row
 * @param component
 * @return
 */
auto Image::get_32F(const int col, const int row, const int component) const -> pixel_32F {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int index = col_row_to_index(col, row, component);
    return buf_32F[index];
}
/**
 * @brief
 * @param col
 * @param row
 * @param component
 * @return
 */
pixel_32S Image::get_32S(const int col, const int row, const int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int index = col_row_to_index(col, row, component);
    return buf_32S[index];
}
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
double Image::get_blue(const int col, const int row) const { return get(col, row, RGB_BLUE); }
/**
 * @brief
 * @return
 */
Image_depth Image::get_depth() const { return image_header.get_depth(); }
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
double Image::get_green(const int col, const int row) const { return get(col, row, RGB_GREEN); }
/**
 * @brief
 * @return
 */
int Image::get_ncols() const { return image_header.get_ncols(); }
/**
 * @brief
 * @return
 */
int Image::get_ncomponents() const { return image_header.get_ncomponents(); }
/**
 * @brief
 * @return
 */
int Image::get_npixels() const { return image_header.get_npixels(); }
/**
 * @brief
 * @return
 */
int Image::get_nrows() const { return image_header.get_nrows(); }
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
double Image::get_red(const int col, const int row) const { return get(col, row, RGB_RED); }
/**
 * @brief
 * @return
 */
int Image::get_row_stride() const { return image_header.get_row_stride(); }
/**
 * @brief
 * @param col
 * @param row
 * @param lower_in
 * @param upper_in
 * @param lower_out
 * @param upper_out
 * @param component
 * @return
 */
double Image::get_scaled(int col, int row, double lower_in, double upper_in, double lower_out, double upper_out,
                         int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    double pixel_in = get(col, row, component);
    double pixel_out = scale_pixel(pixel_in, lower_in, upper_in, lower_out, upper_out);
    return pixel_out;
}
/**
 * @brief
 * @param stats
 */
void Image::get_stats(Variance_stats &stats) const {
    for (int col = 0; col < get_ncols(); col++) {
        for (int row = 0; row < get_nrows(); row++) {
            double value = get(col, row);
            stats.update(value);
        }
    }
}
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
bool Image::in_ellipse(int col, int row) const {
    double dist = ellipse_dist(col, row);
    return dist <= 1.0;
}
/**
 * @brief
 * @param value
 */
void Image::initialize(double value) {
    int size = get_npixels();
    switch (get_depth()) {
        case Image_depth::CV_8U: {
            int int_value = wb_utils::double_to_int(value);
            for (int i = 0; i < size; i++)
                buf_8U[i] = int_value;
            break;
        }
        case Image_depth::CV_32S: {
            int int_value = wb_utils::double_to_int(value);
            for (int i = 0; i < size; i++)
                buf_32S[i] = int_value;
            break;
        }
        case Image_depth::CV_32F: {
            float float_value = wb_utils::double_to_float(value);
            for (int i = 0; i < size; i++)
                buf_32F[i] = float_value;
            break;
        }
        default:
            break;
    }
}
/**
 * @brief
 * @return
 */
bool Image::is_color() const { return get_ncomponents() == 3; }
/**
 * @brief
 * @return
 */
bool Image::is_grayscale() const { return get_ncomponents() == 1; }
/**
 * @brief
 * @param col
 * @param row
 * @return
 */
bool Image::is_pixel_valid(int col, int row) const {
    return (col >= 0 && col < get_ncols() && row >= 0 && row < get_nrows());
}
/**
 * @brief
 * @param log_entries
 */
void Image::log(std::list<WB_log_entry> &log_entries) const {
    Variance_stats stats;
    get_stats(stats);
    WB_log_entry log_entry_ncols("ncols", wb_utils::int_to_string(get_ncols()));
    log_entries.push_back(log_entry_ncols);
    WB_log_entry log_entry_nrows("nrows", wb_utils::int_to_string(get_nrows()));
    log_entries.push_back(log_entry_nrows);
    WB_log_entry log_entry_components("components", wb_utils::int_to_string(get_ncomponents()));
    log_entries.push_back(log_entry_components);
    WB_log_entry log_entry_depth("depth", WB_image_depth::to_string(get_depth()));
    log_entries.push_back(log_entry_depth);
    WB_log_entry log_entry_count("pixel count", wb_utils::int_to_string(get_npixels()));
    log_entries.push_back(log_entry_count);
    WB_log_entry log_entry_mean("pixel mean", wb_utils::double_to_string(stats.get_mean()));
    log_entries.push_back(log_entry_mean);
    WB_log_entry log_entry_standard_deviation("pixel standard deviation",
                                              wb_utils::double_to_string(stats.get_standard_deviation()));
    log_entries.push_back(log_entry_standard_deviation);
    WB_log_entry log_entry_min_value("min pixel value", wb_utils::double_to_string(stats.bounds.min_value));
    log_entries.push_back(log_entry_min_value);
    WB_log_entry log_entry_max_value("max pixel value", wb_utils::double_to_string(stats.bounds.max_value));
    log_entries.push_back(log_entry_max_value);
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
Image *Image::read(const std::string &path, Errors &errors) {
    FILE *fp = file_utils::open_file_read(path, errors);
    if (errors.has_error())
        return nullptr;
    Image *image = nullptr;
    if (fp) {
        image = Image::read(fp, errors);
        fclose(fp);
    }
    return image;
}
/**
 * @brief
 * @param fp
 * @param errors
 * @return
 */
Image *Image::read(FILE *fp, Errors &errors) {
    Image_header image_header;
    image_header.read(fp, errors);
    if (errors.has_error())
        return nullptr;
    auto *image = new Image(image_header);

    // Read the data into buffer.
    int size = image->get_npixels();
    switch (image_header.get_depth()) {
        case Image_depth::CV_8U:
            wb_utils::read_byte_buffer(fp, image->buf_8U.get(), size, "Image::read", "", "cannot read 8U image data",
                                       errors);
            if (errors.has_error()) {
                delete image;
                return nullptr;
            }
            break;

        case Image_depth::CV_32S:
            wb_utils::read_int_buffer(fp, image->buf_32S.get(), size, "Image::read", "", "cannot read 32S image data",
                                      errors);
            if (errors.has_error()) {
                delete image;
                return nullptr;
            }
            break;

        case Image_depth::CV_32F:
            wb_utils::read_float_buffer(fp, image->buf_32F.get(), size, "Image::read", "", "cannot read 32F image data",
                                        errors);
            if (errors.has_error()) {
                delete image;
                return nullptr;
            }
            break;

        default:
            break;
    }
    return image;
}
/**
 * @brief for read_jpeg()
 */
struct my_error_mgr {
    struct jpeg_error_mgr pub; /* "public" fields */
    jmp_buf setjmp_buffer; /* for return to caller */
};

typedef struct my_error_mgr *my_error_ptr;
/**
 * @brief for read_jpeg()
 * @param cinfo
 */
void my_error_exit(j_common_ptr cinfo) {
    my_error_ptr myerr = reinterpret_cast<my_error_ptr>(cinfo->err);
    (*cinfo->err->output_message)(cinfo);
    longjmp(myerr->setjmp_buffer, 1);
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
Image *Image::read_jpeg(const std::string &path, Errors &errors) {
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;
    JSAMPARRAY buffer;
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == nullptr) {
        errors.add("Image::read_jpeg", "", "invalid file '" + path + "'");
        return nullptr;
    }
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        fclose(fp);
        errors.add("Image::read_jpeg", "", "jpeg read error");
        return nullptr;
    }
    /* Step 1: allocate and initialize JPEG decompression object */
    jpeg_create_decompress(&cinfo);
    /* Step 2: specify data source (eg, a file) */
    jpeg_stdio_src(&cinfo, fp);
    /* Step 3: read file parameters with jpeg_read_header() */
    (void) jpeg_read_header(&cinfo, TRUE);
    /* Step 4: set parameters for decompression */
    /* Step 5: Start decompressor */
    (void) jpeg_start_decompress(&cinfo);
    /* JSAMPLEs per row in output buffer */
    // auto *image = new Image(cinfo.output_height, cinfo.output_width, cinfo.num_components, Image_depth::CV_8U, 0.0);
    auto *image = new Image(cinfo.output_width, cinfo.output_height, cinfo.num_components, Image_depth::CV_8U);
    /* Make a one-row-high sample array that will go away when done with image */
    buffer =
            (*cinfo.mem->alloc_sarray)(reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE, image->get_row_stride(), 1);
    /* Step 6: while (scan lines remain to be read) */
    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        /* Assume put_scanline_someplace wants a pointer and sample count. */
        image->add_8U((pixel_8U *) buffer[0], image->get_row_stride(), errors);
    }
    /* Step 7: Finish decompression */
    (void) jpeg_finish_decompress(&cinfo);
    /* Step 8: Release JPEG decompression object */
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);
    return image;
}
/**
 * @brief
 * @param path
 * @param errors
 * @return
 */
Image *Image::read_text(const std::string &path, Errors &errors) {
    std::ifstream ifs = file_utils::open_file_read_text(path, errors);
    Image *image = nullptr;
    if (ifs) {
        image = read_text(ifs, errors);
        ifs.close();
    }
    return image;
}
/**
 * @brief
 * @param ifs
 * @param errors
 * @return
 */
Image *Image::read_text(std::ifstream &ifs, Errors &errors) {
    int ncols = 0;
    int nrows = 0;
    bool first = true;
    std::string line;
    std::vector<std::vector<std::string>> lines;
    while (getline(ifs, line)) {
        std::vector<std::string> values = wb_utils::string_split(line);
        if (first) {
            first = false;
            ncols = values.size();
            lines.push_back(values);
        } else if (values.size() != ncols) {
            std::ostringstream os;
            os << "invalid image file: initial column length " << ncols << " nrow " << nrows << " column length "
               << values.size();
            errors.add("Image::read_text", "", os.str());
            return nullptr;
        } else {
            lines.push_back(values);
        }
        nrows++;
    }
    auto *image = new Image(ncols, nrows, 1, Image_depth::CV_32S);
    pixel_32S *buf_ptr = image->buf_32S.get();
    for (const std::vector<std::string> &row_values: lines) {
        for (const std::string &value_str: row_values) {
            int value;
            if (wb_utils::string_to_int(value_str, value)) {
                *buf_ptr++ = value;
            } else {
                errors.add("Image::read_text", "", "invalid value '" + value_str + "'");
                delete image;
                return nullptr;
            }
        }
    }
    return image;
}
/**
 * @brief
 * component 1 only
 * @param image
 * @param area_ncols
 * @param area_nrows
 * @param resize_type
 * @return
 */
Image *Image::resize(const Image *image, int area_ncols, int area_nrows, WB_resize_types::Resize_type resize_type) {
    int out_ncols = image->get_ncols() / area_ncols;
    int out_nrows = image->get_nrows() / area_nrows;
    int area = area_ncols * area_nrows;
    auto *resize_image = new Image(out_ncols, out_nrows, 1, image->get_depth());
    for (int col = 0; col < out_ncols; col++) {
        for (int row = 0; row < out_nrows; row++) {
            double value = 0.0;
            for (int area_col = 0; area_col < area_ncols; area_col++)
                for (int area_row = 0; area_row < area_nrows; area_row++) {
                    switch (resize_type) {
                        case WB_resize_types::Resize_type::AVERAGE: {
                            value += image->get(col * area_ncols + area_col, row * area_nrows + area_row);
                            break;
                        }
                        case WB_resize_types::Resize_type::MAX: {
                            value = std::max(value,
                                             image->get(col * area_ncols + area_col, row * area_nrows + area_row));
                            break;
                        }
                        case WB_resize_types::Resize_type::MIN: {
                            value = std::min(value,
                                             image->get(col * area_ncols + area_col, row * area_nrows + area_row));
                            break;
                        }
                        case WB_resize_types::Resize_type::SUM: {
                            value += image->get(col * area_ncols + area_col, row * area_nrows + area_row);
                            break;
                        }
                    }
                }
            if (resize_type == WB_resize_types::Resize_type::AVERAGE)
                value /= area;
            resize_image->set(col, row, value, 0);
        }
    }
    return resize_image;
}
/***
 * @brief
 * preconditions not checked:
 *   lower_in < lower_out
 *   upper_in < upper_out
 *   lower_out >= pixel_8U_MIN
 *   upper_out <= pixel_8U_MAX
 * @param image
 * @param lower_in
 * @param upper_in
 * @param lower_out
 * @param upper_out
 * @param depth
 * @param component
 * @return
 */
Image *Image::scale_image(const Image *image, double lower_in, double upper_in, double lower_out, double upper_out,
                          Image_depth depth, int component) {
    if (debug)
        std::cout << "Image *Image::scale_image: lower_in " << lower_in << " upper_in " << upper_in << " lower_out "
                  << lower_out << " upper_out " << upper_out << " depth " << WB_image_depth::to_string(depth)
                  << std::endl;
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= image->get_ncomponents());
#endif
    auto *convert_image = new Image(image->get_ncols(), image->get_nrows(), image->get_ncomponents(), depth);
    for (int col = 0; col < image->get_ncols(); col++) {
        for (int row = 0; row < image->get_nrows(); row++) {
            double value = image->get_scaled(col, row, lower_in, upper_in, lower_out, upper_out, component);
            convert_image->set(col, row, value, component);
        }
    }
    return convert_image;
}
/**
 * @brief
 * @param pixel_in
 * @param in_lower
 * @param in_upper
 * @param out_lower
 * @param out_upper
 * @return
 */
double Image::scale_pixel(double pixel_in, double in_lower, double in_upper, double out_lower, double out_upper) {
    Bounds in_bounds(in_lower, in_upper);
    Bounds out_bounds(out_lower, out_upper);
    double pixel_out = Bounds::map_input_to_output_bounds(pixel_in, in_bounds, out_bounds);
    return pixel_out;
}
/**
 * @brief
 * CV_8U may lose precision/overflow
 * @param col
 * @param row
 * @param value
 * @param component
 */
void Image::set(int col, int row, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    assert(col <= get_ncols());
    assert(row <= get_nrows());
    int index = col_row_to_index(col, row, component);
    assert(index <= get_npixels());
    switch (get_depth()) {
        case Image_depth::CV_8U:
            buf_8U[index] = wb_utils::double_to_int_round(value);
            break;

        case Image_depth::CV_32S:
            buf_32S[col_row_to_index(col, row, component)] = wb_utils::double_to_int_round(value);
            break;

        case Image_depth::CV_32F:
            buf_32F[col_row_to_index(col, row, component)] = wb_utils::double_to_float(value);
            break;

        default:
            break;
    }
}
/**
 * @brief
 * @param pixel
 * @param value
 * @param component
 */
void Image::set(const Pixel &pixel, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    set(pixel.col, pixel.row, value, component);
}
/**
 * @brief
 * @param col
 * @param row
 * @param value
 * @param component
 */
void Image::set_8U(int col, int row, pixel_8U value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    assert(col <= get_ncols());
    assert(row <= get_nrows());
    int index = col_row_to_index(col, row, component);
    assert(index <= get_npixels());
    buf_8U[index] = value;
}
/**
 * @brief
 * @param col
 * @param row
 * @param value
 * @param component
 */
void Image::set_32F(int col, int row, pixel_32F value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    assert(col <= get_ncols());
    assert(row <= get_nrows());
    int index = col_row_to_index(col, row, component);
    assert(index <= get_npixels());
    buf_32F[index] = value;
}
/**
 * @brief
 * @param col
 * @param row
 * @param value
 * @param component
 */
void Image::set_32S(int col, int row, pixel_32S value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    assert(col <= get_ncols());
    assert(row <= get_nrows());
    int index = col_row_to_index(col, row, component);
    assert(index <= get_npixels());
    buf_32S[index] = value;
}
// subtracts image without underflow checking for CV_8U images
Image *Image::subtract(const Image *src_image, const Image *subtract_image, Errors &errors) {
    if (src_image->get_npixels() != subtract_image->get_npixels()) {
        errors.add("Image::subtract", "", "images not the same size ");
        return nullptr;
    }
    if (src_image->get_depth() != subtract_image->get_depth()) {
        errors.add("Image::subtract", "", "images not the same depth ");
        return nullptr;
    }
    //  if (src_image->get_depth() == Image_depth::CV_8U) {
    //    errors.add("Image::subtract", "", "cannot subtract CV_8U images");
    //    return nullptr;
    //  }

    auto *out_image = new Image(src_image->image_header);

    int size = src_image->get_npixels();
    switch (src_image->get_depth()) {
        case Image_depth::CV_8U:
            for (int i = 0; i < size; i++)
                out_image->buf_8U[i] = src_image->buf_8U[i] - subtract_image->buf_8U[i];
            break;

        case Image_depth::CV_32S:
            for (int i = 0; i < size; i++)
                out_image->buf_32S[i] = src_image->buf_32S[i] - subtract_image->buf_32S[i];
            break;

        case Image_depth::CV_32F:
            for (int i = 0; i < size; i++)
                out_image->buf_32F[i] = src_image->buf_32F[i] - subtract_image->buf_32F[i];
            break;

        default:
            break;
    }
    return out_image;
}
/**
 * @brief
 * @param image_line_segment
 * @param line_segment
 */
void Image::to_image_line_segment(Image_line_segment &image_line_segment, Line_segment &line_segment) {
    Pixel pixel1;
    Pixel pixel2;
    to_pixel(pixel1, line_segment.point1);
    to_pixel(pixel2, line_segment.point2);
    image_line_segment.init(pixel1, pixel2);
}
/**
 * @brief
 * @param line_segment
 * @param image_line_segment
 */
void Image::to_line_segment(Line_segment &line_segment, Image_line_segment &image_line_segment) {
    Point point1;
    Point point2;
    to_point(point1, image_line_segment.pixel1);
    to_point(point2, image_line_segment.pixel2);
    line_segment.init(point1, point2);
}
/**
 * @brief
 * @param pixel
 * @param x
 * @param y
 */
void Image::to_pixel(Pixel &pixel, double x, double y) { image_header.to_pixel(pixel, x, y); }
/**
 * @brief
 * @param pixel
 * @param point
 */
void Image::to_pixel(Pixel &pixel, Point &point) { image_header.to_pixel(pixel, point); }
/**
 * @brief
 * @param pixel_RGB
 * @param col
 * @param row
 */
void Image::to_pixel_RGB(Pixel_RGB &pixel_RGB, int col, int row) const {
    pixel_RGB.red = get_red(col, row);
    pixel_RGB.red = get_green(col, row);
    pixel_RGB.red = get_blue(col, row);
}
/**
 * @brief
 * @param point
 * @param col
 * @param row
 */
void Image::to_point(Point &point, int col, int row) { image_header.to_point(point, col, row); }
/**
 * @brief
 * @param point
 * @param pixel
 */
void Image::to_point(Point &point, Pixel &pixel) { image_header.to_point(point, pixel); }
/**
 * @brief
 * @param prefix
 * @return
 */
std::string Image::to_string(const std::string &prefix) const {
    std::ostringstream os;
    os << prefix << image_header.to_string(prefix + "    ");
    return os.str();
}
/**
 * @brief
 * @param col
 * @return
 */
double Image::to_x(int col) const { return image_header.to_x(col); }
/**
 * @brief
 * @param col
 * @param ncols
 * @return
 */
double Image::to_x(int col, int ncols) { return Image_header::to_x(col, ncols); }
/**
 * @brief
 * @param row
 * @return
 */
double Image::to_y(int row) const { return image_header.to_y(row); }
/**
 * @brief
 * @param row
 * @param nrows
 * @return
 */
double Image::to_y(int row, int nrows) { return Image_header::to_y(row, nrows); }
/**
 * @brief
 * @param path
 * @param errors
 */
void Image::write(const std::string &path, Errors &errors) const {
    if (FILE *fp = file_utils::open_file_write(path, errors)) {
        write(fp, errors);
        fclose(fp);
    }
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Image::write(FILE *fp, Errors &errors) const {
    image_header.write(fp, errors);
    if (errors.has_error())
        return;
    // Write the data from the buffer.
    size_t newLen;
    int size = get_npixels();
    switch (get_depth()) {
        case Image_depth::CV_8U:
            newLen = fwrite(buf_8U.get(), sizeof(pixel_8U), size, fp);
            if (ferror(fp) != 0 || newLen != size) {
                errors.add("Image::write", "", "cannot write 8U image data");
            }
            break;
        case Image_depth::CV_32S:
            newLen = fwrite(buf_32S.get(), sizeof(pixel_32S), size, fp);
            if (ferror(fp) != 0 || newLen != size) {
                errors.add("Image::write", "", "cannot write 32S image data");
            }
            break;
        case Image_depth::CV_32F:
            newLen = fwrite(buf_32F.get(), sizeof(pixel_32F), size, fp);
            if (ferror(fp) != 0 || newLen != size) {
                errors.add("Image::write", "", "cannot write 32F image data");
            }
            break;
        default:
            break;
    }
}
/**
 * @brief
 * @param path
 * @param errors
 */
void Image::write_jpeg(const std::string &path, Errors &errors) const {
    if (get_depth() != Image_depth::CV_8U) {
        errors.add("Image::write_jpeg", "", "cannot write " + WB_image_depth::to_string(get_depth()) + " image");
        return;
    }
    int quality = 100; // best
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    /* More stuff */
    FILE *outfile; /* target file */
    JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
    // int row_stride;		/* physical row width in image buffer */

    /* Step 1: allocate and initialize JPEG compression object */
    cinfo.err = jpeg_std_error(&jerr);
    /* Now we can initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);
    /* Step 2: specify data destination (eg, a file) */
    if ((outfile = fopen(path.c_str(), "wb")) == nullptr) {
        errors.add("Image::write_jpeg", "", "invalid file '" + path + "'");
    }
    jpeg_stdio_dest(&cinfo, outfile);
    /* Step 3: set parameters for compression */
    cinfo.image_width = get_ncols();
    cinfo.image_height = get_nrows();
    cinfo.input_components = 1; // hardcode grayscale for now
    cinfo.in_color_space = JCS_GRAYSCALE; /* colorspace of input image */
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
    /* Step 4: Start compressor */
    jpeg_start_compress(&cinfo, TRUE);
    /* Step 5: while (scan lines remain to be written) */
    /*           jpeg_write_scanlines(...); */

    while (cinfo.next_scanline < cinfo.image_height) {
        /* jpeg_write_scanlines expects an array of pointers to scanlines.
         * Here the array is only one element long, but you could pass
         * more than one scanline at a time if that's more convenient.
         */
        row_pointer[0] = (JSAMPROW) &buf_8U[cinfo.next_scanline * get_row_stride()];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    /* Step 6: Finish compression */
    jpeg_finish_compress(&cinfo);
    /* After finish_compress, we can close the output file. */
    fclose(outfile);
    /* Step 7: release JPEG compression object */
    jpeg_destroy_compress(&cinfo);
}
/**
 * @brief
 * @param path
 * @param delim
 * @param errors
 */
void Image::write_text(const std::string &path, const std::string &delim, Errors &errors) const {
    if (std::ofstream ofs = file_utils::open_file_write_text(path, errors)) {
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
void Image::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
    for (int row = 0; row < get_nrows(); row++) {
        for (int col = 0; col < get_ncols(); col++) {
            for (int component = 0; component < get_ncomponents(); component++) {
                double value = get(col, row, component);
                ofs << value << delim;
            }
        }
        ofs << std::endl;
    }
    ofs.close();
}
