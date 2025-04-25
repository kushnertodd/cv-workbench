//
// Created by kushn on 6/11/2022.
//

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

Pixel_RGB::Pixel_RGB() {}
Pixel_RGB::Pixel_RGB(double m_red, double m_green, double m_blue) : red(m_red), green(m_green), blue(m_blue) {};
double Pixel_RGB::diff(const Pixel_RGB &other) const {
    return sqrt((other.red - red) * (other.red - red) + (other.green - green) * (other.green - green) +
                (other.blue - blue) * (other.blue - blue));
}
Image::~Image() {
    delete[] buf_8U;
    delete[] buf_32S;
    delete[] buf_32F;
}
Image::Image() = default;
Image::Image(const int m_nrows, const int m_ncols, const int m_components, const Image_depth m_depth,
             const double value) : image_header(m_nrows, m_ncols, m_components, m_depth) {
    init(value);
}
Image::Image(const Image &image) :
    image_header(image.get_nrows(), image.get_ncols(), image.get_ncomponents(), image.get_depth()) {
    int size = get_npixels();
    switch (get_depth()) {
        case Image_depth::CV_8U:
            buf_8U = new pixel_8U[size];
            for (int i = 0; i < size; i++)
                buf_8U[i] = image.buf_8U[i];
            break;

        case Image_depth::CV_32S:
            buf_32S = new pixel_32S[size];
            for (int i = 0; i < size; i++)
                buf_32S[i] = image.buf_32S[i];
            break;

        case Image_depth::CV_32F:
            buf_32F = new pixel_32F[size];
            for (int i = 0; i < size; i++)
                buf_32F[i] = image.buf_32F[i];
            break;

        default:
            break;
    }
}
Image::Image(const Image_header &m_image_header, double value) : image_header(m_image_header) {
    if (debug)
        std::cout << "Image::Image: " << to_string() << std::endl;
    init(value);
}
void Image::add_8U(const pixel_8U *src, int count, Errors &errors) {
    if (next_pixel + count > get_npixels())
        errors.add("Image::add_8U", "",
                   "adding " + wb_utils::int_to_string(count) + " pixels at position " +
                           wb_utils::int_to_string(next_pixel) + " too large for buffer length " +
                           wb_utils::int_to_string(get_npixels()));
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
void Image::add_32F(const pixel_32F *src, int count, Errors &errors) {
    if (next_pixel + count > get_npixels())
        errors.add("Image::add_32F", "",
                   "adding " + wb_utils::int_to_string(count) + " pixels at position " +
                           wb_utils::int_to_string(next_pixel) + " too large for buffer length " +
                           wb_utils::int_to_string(get_npixels()));
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
void Image::add_32S(const pixel_32S *src, int count, Errors &errors) {
    if (debug)
        std::cout << "Image::add_32S src " << src << " count " << count << " " << to_string() << std::endl;
    if (next_pixel + count > get_npixels()) {
        errors.add("Image::add_32S", "",
                   "adding " + wb_utils::int_to_string(count) + " pixels at position " +
                           wb_utils::int_to_string(next_pixel) + " too large for buffer length " +
                           wb_utils::int_to_string(get_npixels()));
        return;
    }
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
bool Image::check_color(const std::string &module, Errors &errors) const {
    if (get_ncomponents() != 3) {
        errors.add(module, "", "image not color");
        return false;
    }
    return true;
}
bool Image::check_grayscale(const std::string &module, Errors &errors) const {
    if (get_ncomponents() != 1) {
        errors.add(module, "", "image not grayscale");
        return false;
    }
    return true;
}
void Image::clear(double value) {
    int size = get_npixels();
    switch (get_depth()) {
        case Image_depth::CV_8U:
            for (int i = 0; i < size; i++)
                buf_8U[i] = value;
            break;

        case Image_depth::CV_32S:
            for (int i = 0; i < size; i++)
                buf_32S[i] = value;
            break;

        case Image_depth::CV_32F:
            for (int i = 0; i < size; i++)
                buf_32F[i] = value;
            break;

        default:
            break;
    }
}
/***
 * Not really what want. Doesn't copy contents.
 * @param image
 * @param depth
 * @param errors
 * @return
 */
Image *Image::clone(const Image *image, Image_depth depth, Errors &errors) {
    auto *new_image = new Image(image->get_nrows(), image->get_ncols(), image->get_ncomponents(), depth);
    new_image->copy(image, errors);
    return new_image;
}


// color edge detection
Image *Image::color_edge(Errors &errors) {
#ifdef IMAGE_COMPONENT_CHECK
    assert(is_color());
#endif
    int nrows = get_nrows();
    int ncols = get_ncols();
    int row_lower = 1;
    int row_upper = nrows - 2;
    int col_lower = 1;
    int col_upper = ncols - 2;
    auto *out = new Image(nrows, ncols, COMPONENTS_GRAYSCALE, Image_depth::CV_32F);
    out->clear(0.0);
    if (debug)
        std::cout << "row_lower " << row_lower << ", row_upper " << row_upper << ", col_lower " << col_lower
                  << ", col_upper " << col_upper << std::endl;
    for (int row = row_lower; row <= row_upper; row++) {
        if (debug)
            std::cout << "row " << row << std::endl;
        for (int col = col_lower; col <= col_upper; col++) {
            if (debug)
                std::cout << "col " << col << std::endl;
            Pixel_RGB image_center;
            to_pixel_RGB(image_center, row, col);
            Pixel_RGB image_up;
            to_pixel_RGB(image_up, row - 1, col);
            Pixel_RGB image_down;
            to_pixel_RGB(image_down, row + 1, col);
            Pixel_RGB image_left;
            to_pixel_RGB(image_left, row, col - 1);
            Pixel_RGB image_right;
            to_pixel_RGB(image_right, row, col + 1);
            double sum = image_up.diff(image_center) + image_down.diff(image_center) + image_left.diff(image_center) +
                         image_right.diff(image_center);
            out->set(row, col, sum);
        }
    }
    return out;
}
/**
 * return linear combination of input images:
 * pixel_32F output-pixel = image1-pixel * scale1 + image2-pixel * scale2 + offset;
 * @param image
 * @param image1
 * @param image2
 * @param scale1
 * @param scale2
 * @param offset
 * @param errors
 * @return
 */
Image *Image::combine(Image *input1, Image *input2, double scale1, double scale2, double offset, Errors &errors) {
    int nrows1;
    int nrows2;
    int ncols1;
    int ncols2;

    nrows1 = input1->get_nrows();
    nrows2 = input2->get_nrows();
    ncols1 = input1->get_ncols();
    ncols2 = input2->get_ncols();
    if (nrows1 != nrows2 || ncols1 != ncols2) {
        std::ostringstream os;
        os << "input1 size (" << nrows1 << ", " << ncols1 << ") not the same as input2 size (" << nrows2 << ", "
           << ncols2 << ")";
        errors.add("Operator_transform_image_combine::run", "", os.str());
    }
    Image *output = nullptr;
    if (!errors.has_error()) {
        output = new Image(nrows1, ncols1, 1, Image_depth::CV_32F);
        for (int row = 0; row < nrows1; row++)
            for (int col = 0; col < ncols1; col++) {
                double pixel1 = input1->get(row, col);
                double pixel2 = input2->get(row, col);
                double value = pixel1 * scale1 + pixel2 * scale2 + offset;
                output->set(row, col, value);
            }
    }
    return output;
}
// copies CV_32S and CV_32F to CV_8U with truncation to 0..255
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
    switch (get_depth()) {
        case Image_depth::CV_8U:
            for (int i = 0; i < get_npixels(); i++) {
                buf_8U[i] = image->buf_8U[i];
            }
            break;

        case Image_depth::CV_32S:
            switch (image->get_depth()) {
                case Image_depth::CV_8U:
                    for (int i = 0; i < get_npixels(); i++) {
                        buf_32S[i] = image->buf_8U[i];
                    }
                    break;
                case Image_depth::CV_32S:
                    for (int i = 0; i < get_npixels(); i++) {
                        buf_32S[i] = image->buf_32S[i];
                    }
                    break;
                case Image_depth::CV_32F:
                    for (int i = 0; i < get_npixels(); i++) {
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
                    for (int i = 0; i < get_npixels(); i++) {
                        buf_32F[i] = image->buf_8U[i];
                    }
                    break;
                case Image_depth::CV_32S:
                    for (int i = 0; i < get_npixels(); i++) {
                        buf_32F[i] = wb_utils::int_to_float(image->buf_32S[i]);
                    }
                    break;
                case Image_depth::CV_32F:
                    for (int i = 0; i < get_npixels(); i++) {
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
void Image::draw_line_segment(const Line_segment &line_segment, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    for (Point pixel: line_segment.line_points) {
        set(pixel, value, component);
    }
}
void Image::draw_line_segment(int row1, int col1, int row2, int col2, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    Line_segment line_segment(row1, col1, row2, col2);
    for (Point pixel: line_segment.line_points) {
        set(pixel, value, component);
    }
}
void Image::draw_line_segments(const std::list<Line_segment> &line_segments, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    for (const Line_segment &line_segment: line_segments) {
        draw_line_segment(line_segment, value, component);
    }
}
void Image::draw_rectangle(int row1, int col1, int row2, int col2, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    Line_segment line_segment1(row1, col1, row1, col2);
    Line_segment line_segment2(row1, col2, row2, col2);
    Line_segment line_segment3(row2, col2, row2, col1);
    Line_segment line_segment4(row2, col1, row1, col1);
    draw_line_segment(line_segment1, value, component);
    draw_line_segment(line_segment2, value, component);
    draw_line_segment(line_segment3, value, component);
    draw_line_segment(line_segment4, value, component);
}
void Image::draw_rectangle_filled(int row1, int col1, int row2, int col2, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int row_min = std::min(row1, row2);
    int col_min = std::min(col1, col2);
    int row_max = std::max(row1, row2);
    int col_max = std::max(col1, col2);
    for (int row = row_min; row <= row_max; row++)
        for (int col = col_min; col <= col_max; col++)
            set(row, col, value, component);
}
double Image::get(const int row, const int col, const int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int index;
    switch (get_depth()) {
        case Image_depth::CV_8U:
            index = col_row_to_index(row, col, component);
            return buf_8U[index];

        case Image_depth::CV_32S:
            index = col_row_to_index(row, col, component);
            return static_cast<pixel_32F>(buf_32S[index]);

        case Image_depth::CV_32F:
            index = col_row_to_index(row, col, component);
            return buf_32F[index];

        default:
            return 0.0;
    }
}
double Image::get(const Point &pixel, const int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    return get(pixel.row, pixel.col, component);
}
auto Image::get_8U(const int row, const int col, const int component) const -> pixel_8U {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int index = col_row_to_index(row, col, component);
    return buf_8U[index];
}
auto Image::get_32F(const int row, const int col, const int component) const -> pixel_32F {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int index = col_row_to_index(row, col, component);
    return buf_32F[index];
}
pixel_32S Image::get_32S(const int row, const int col, const int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    int index = col_row_to_index(row, col, component);
    return buf_32S[index];
}
double Image::get_blue(const int row, const int col) const { return get(row, col, RGB_BLUE); }
int Image::get_ncomponents() const { return image_header.ncomponents; }
Image_depth Image::get_depth() const { return image_header.depth; }
double Image::get_green(const int row, const int col) const { return get(row, col, RGB_GREEN); }
int Image::get_ncols() const { return image_header.ncols; }
int Image::get_npixels() const { return image_header.npixels; }
int Image::get_nrows() const { return image_header.nrows; }
double Image::get_red(const int row, const int col) const { return get(row, col, RGB_RED); }
int Image::get_row_stride() const { return image_header.row_stride; }
double Image::get_scaled(int col, int row, double lower_in, double upper_in, double lower_out, double upper_out,
                         int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    double pixel_in = get(row, col, component);
    double pixel_out = scale_pixel(pixel_in, lower_in, upper_in, lower_out, upper_out);
    return pixel_out;
}
void Image::get_stats(Variance_stats &stats) const {
    for (int row = 0; row < get_nrows(); row++) {
        for (int col = 0; col < get_ncols(); col++) {
            double value = get(row, col);
            stats.update(value);
        }
    }
}
void Image::init(double value) {
    int size = get_npixels();
    ;
    switch (get_depth()) {
        case Image_depth::CV_8U: {
            int int_value = wb_utils::double_to_int(value);
            buf_8U = new pixel_8U[size];
            for (int i = 0; i < size; i++)
                buf_8U[i] = int_value;
            break;
        }
        case Image_depth::CV_32S: {
            int int_value = wb_utils::double_to_int(value);
            buf_32S = new pixel_32S[size];
            for (int i = 0; i < size; i++)
                buf_32S[i] = int_value;
            break;
        }
        case Image_depth::CV_32F: {
            float float_value = wb_utils::double_to_float(value);
            buf_32F = new pixel_32F[size];
            for (int i = 0; i < size; i++)
                buf_32F[i] = float_value;
            break;
        }
        default:
            break;
    }
}
bool Image::is_color() const { return get_ncomponents() == 3; }
bool Image::is_grayscale() const { return get_ncomponents() == 1; }
void Image::log(std::list<WB_log_entry> &log_entries) const {
    Variance_stats stats;
    get_stats(stats);
    WB_log_entry log_entry_nrows("nrows", wb_utils::int_to_string(get_nrows()));
    log_entries.push_back(log_entry_nrows);
    WB_log_entry log_entry_ncols("ncols", wb_utils::int_to_string(get_ncols()));
    log_entries.push_back(log_entry_ncols);
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
void Image::to_pixel_RGB(Pixel_RGB &pixel_RGB, int col, int row) {
    pixel_RGB.red = get_red(row, col);
    pixel_RGB.red = get_green(row, col);
    pixel_RGB.red = get_blue(row, col);
};
Image *Image::read(const std::string &path, Errors &errors) {
    FILE *fp = file_utils::open_file_read(path, errors);
    Image *image = nullptr;
    if (fp) {
        image = Image::read(fp, errors);
        fclose(fp);
    }
    return image;
}
Image *Image::read(FILE *fp, Errors &errors) {
    Image_header image_header;
    image_header.read(fp, errors);
    if (errors.has_error())
        return nullptr;
    auto *image = new Image(image_header);

    // Read the data into buffer.
    switch (image_header.depth) {
        case Image_depth::CV_8U:
            wb_utils::read_byte_buffer(fp, image->buf_8U, image->get_npixels(), "Image::read", "",
                                       "cannot read 8U image data", errors);
            if (errors.has_error()) {
                delete image;
                return nullptr;
            }
            break;

        case Image_depth::CV_32S:
            wb_utils::read_int_buffer(fp, image->buf_32S, image->get_npixels(), "Image::read", "",
                                      "cannot read 32S image data", errors);
            if (errors.has_error()) {
                delete image;
                return nullptr;
            }
            break;

        case Image_depth::CV_32F:
            wb_utils::read_float_buffer(fp, image->buf_32F, image->get_npixels(), "Image::read", "",
                                        "cannot read 32F image data", errors);
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
// for read_jpeg()
struct my_error_mgr {
    struct jpeg_error_mgr pub; /* "public" fields */
    jmp_buf setjmp_buffer; /* for return to caller */
};

typedef struct my_error_mgr *my_error_ptr;

// for read_jpeg()
void my_error_exit(j_common_ptr cinfo) {
    my_error_ptr myerr = reinterpret_cast<my_error_ptr>(cinfo->err);
    (*cinfo->err->output_message)(cinfo);
    longjmp(myerr->setjmp_buffer, 1);
}
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
    auto *image = new Image(cinfo.output_height, cinfo.output_width, cinfo.num_components, Image_depth::CV_8U);
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
Image *Image::read_text(const std::string &path, Errors &errors) {
    std::ifstream ifs = file_utils::open_file_read_text(path, errors);
    Image *image = nullptr;
    if (ifs) {
        image = read_text(ifs, errors);
        ifs.close();
    }
    return image;
}
Image *Image::read_text(std::ifstream &ifs, Errors &errors) {
    int nrows = 0;
    int ncols = 0;
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
            os << "invalid image file: initial column length " << ncols << " row " << nrows << " column length "
               << values.size();
            errors.add("Image::read_text", "", os.str());
            return nullptr;
        } else {
            lines.push_back(values);
        }
        nrows++;
    }
    auto *image = new Image(nrows, ncols, 1, Image_depth::CV_32S);
    pixel_32S *buf_ptr = image->buf_32S;
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
// component 1 only
Image *Image::resize(const Image *image, int area_nrows, int area_ncols, WB_resize_types::Resize_type resize_type) {
    int out_nrows = image->get_nrows() / area_nrows;
    int out_ncols = image->get_ncols() / area_ncols;
    int area = area_nrows * area_ncols;
    auto *resize_image = new Image(out_nrows, out_ncols, 1, image->get_depth());
    for (int row = 0; row < out_nrows; row++) {
        for (int col = 0; col < out_ncols; col++) {
            double value = 0.0;
            for (int area_row = 0; area_row < area_nrows; area_row++) {
                for (int area_col = 0; area_col < area_ncols; area_col++)
                    switch (resize_type) {
                        case WB_resize_types::Resize_type::AVERAGE: {
                            value += image->get(row * area_nrows + area_row, col * area_ncols + area_col);
                            break;
                        }
                        case WB_resize_types::Resize_type::MAX: {
                            value = std::max(value,
                                             image->get(row * area_nrows + area_row, col * area_ncols + area_col));
                            break;
                        }
                        case WB_resize_types::Resize_type::MIN: {
                            value = std::min(value,
                                             image->get(row * area_nrows + area_row, col * area_ncols + area_col));
                            break;
                        }
                        case WB_resize_types::Resize_type::SUM: {
                            value += image->get(row * area_nrows + area_row, col * area_ncols + area_col);
                            break;
                        }
                    }
            }
            if (resize_type == WB_resize_types::Resize_type::AVERAGE)
                value /= area;
            resize_image->set(row, col, value, 0);
        }
    }
    return resize_image;
}
int Image::col_row_to_index(int col, int row, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
    if (!(row >= 0 && row < get_nrows() && col >= 0 && col < get_ncols()))
        int i = 0;
    assert(row >= 0 && row < get_nrows() && col >= 0 && col < get_ncols());
#endif
    return row * get_row_stride() + col * image_header.ncomponents + component;
}
/***
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
    auto *convert_image = new Image(image->get_nrows(), image->get_ncols(), image->get_ncomponents(), depth);
    for (int row = 0; row < image->get_nrows(); row++) {
        for (int col = 0; col < image->get_ncols(); col++) {
            double value = image->get_scaled(row, col, lower_in, upper_in, lower_out, upper_out, component);
            convert_image->set(row, col, value, component);
        }
    }
    return convert_image;
}
double Image::scale_pixel(double pixel_in, double in_lower, double in_upper, double out_lower, double out_upper) {
    Bounds in_bounds(in_lower, in_upper);
    Bounds out_bounds(out_lower, out_upper);
    double pixel_out = Bounds::map_input_to_output_bounds(pixel_in, in_bounds, out_bounds);
    return pixel_out;
}
// -> CV_8U may lose precision/overflow
void Image::set(int col, int row, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    switch (get_depth()) {
        case Image_depth::CV_8U:
            buf_8U[col_row_to_index(row, col, component)] = wb_utils::double_to_int_round(value);
            break;

        case Image_depth::CV_32S:
            buf_32S[col_row_to_index(row, col, component)] = wb_utils::double_to_int_round(value);
            break;

        case Image_depth::CV_32F:
            buf_32F[col_row_to_index(row, col, component)] = wb_utils::double_to_float(value);
            break;

        default:
            break;
    }
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

void Image::set(const Point &pixel, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    set(pixel.row, pixel.col, value, component);
}
void Image::set_8U(int col, int row, pixel_8U value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    buf_8U[col_row_to_index(row, col, component)] = value;
}
void Image::set_32F(int col, int row, pixel_32F value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    buf_32F[col_row_to_index(row, col, component)] = value;
}
void Image::set_32S(int col, int row, pixel_32S value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    assert(component <= get_ncomponents());
#endif
    buf_32S[col_row_to_index(row, col, component)] = value;
}
std::string Image::to_string(const std::string &prefix) const {
    std::ostringstream os;
    os << prefix << image_header.to_string(prefix + "    ");
    return os.str();
}
void Image::write(const std::string &path, Errors &errors) const {
    if (FILE *fp = file_utils::open_file_write(path, errors)) {
        write(fp, errors);
        fclose(fp);
    }
}
void Image::write(FILE *fp, Errors &errors) const {
    image_header.write(fp, errors);
    if (errors.has_error())
        return;
    // Write the data from the buffer.
    size_t newLen;
    switch (get_depth()) {
        case Image_depth::CV_8U:
            newLen = fwrite(buf_8U, sizeof(pixel_8U), get_npixels(), fp);
            if (ferror(fp) != 0 || newLen != get_npixels()) {
                errors.add("Image::write", "", "cannot write 8U image data");
            }
            break;
        case Image_depth::CV_32S:
            newLen = fwrite(buf_32S, sizeof(pixel_32S), get_npixels(), fp);
            if (ferror(fp) != 0 || newLen != get_npixels()) {
                errors.add("Image::write", "", "cannot write 32S image data");
            }
            break;
        case Image_depth::CV_32F:
            newLen = fwrite(buf_32F, sizeof(pixel_32F), get_npixels(), fp);
            if (ferror(fp) != 0 || newLen != get_npixels()) {
                errors.add("Image::write", "", "cannot write 32F image data");
            }
            break;
        default:
            break;
    }
}
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
void Image::write_text(const std::string &path, const std::string &delim, Errors &errors) const {
    if (std::ofstream ofs = file_utils::open_file_write_text(path, errors)) {
        write_text(ofs, "\t", errors);
        ofs.close();
    }
}
void Image::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
    for (int row = 0; row < get_nrows(); row++) {
        for (int col = 0; col < get_ncols(); col++) {
            for (int component = 0; component < get_ncomponents(); component++) {
                double value = get(row, col, component);
                ofs << value << delim;
            }
        }
        ofs << std::endl;
    }
    ofs.close();
}
