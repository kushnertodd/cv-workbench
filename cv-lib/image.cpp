//
// Created by kushn on 6/11/2022.
//

#include <cassert>
#include <csetjmp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "file_utils.hpp"
#include "image.hpp"
#include "jpeglib.h"
#include "image_depth.hpp"
#include "wb_utils.hpp"

extern bool debug;

Image::~Image() {
    delete[] buf_8U;
    delete[] buf_32S;
    delete[] buf_32F;
}


Image::Image() = default;

Image::Image(const int m_rows, const int m_cols, const int m_components,
             const Image_depth m_depth, const double value) : image_header(m_rows, m_cols, m_components, m_depth) {
    init(value);
}

Image::Image(const Image &image) : image_header(image.get_rows(), image.get_cols(), image.get_components(),
                                                image.get_depth()) {
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
        errors.add("Image::add_8U", "", "adding "
                                        + wb_utils::int_to_string(count) + " pixels at position " +
                                        wb_utils::int_to_string(next_pixel)
                                        + " too large for buffer length "
                                        + wb_utils::int_to_string(get_npixels()));
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
        errors.add("Image::add_32F", "", "adding "
                                         + wb_utils::int_to_string(count) + " pixels at position " +
                                         wb_utils::int_to_string(next_pixel)
                                         + " too large for buffer length "
                                         + wb_utils::int_to_string(get_npixels()));
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
        errors.add("Image::add_32S", "", "adding "
                                         + wb_utils::int_to_string(count) + " pixels at position " +
                                         wb_utils::int_to_string(next_pixel)
                                         + " too large for buffer length "
                                         + wb_utils::int_to_string(get_npixels()));
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
    if (get_components() != 3) {
        errors.add(module, "", "image not color");
        return false;
    }
    return true;
}

bool Image::check_grayscale(const std::string &module, Errors &errors) const {
    if (get_components() != 1) {
        errors.add(module, "", "image not grayscale");
        return false;
    }
    return true;
}


/***
 * Not really what want. Doesn't copy contents.
 * @param image
 * @param depth
 * @param errors
 * @return
 */
Image *Image::clone(const Image *image, Image_depth depth, Errors &errors) {
    auto *new_image = new Image(image->get_rows(),
                                image->get_cols(),
                                image->get_components(),
                                depth);
    new_image->copy(image, errors);
    return new_image;
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
Image *Image::combine(Image *input1, Image *input2, double scale1, double scale2, double offset,
                      Errors &errors) {
    int rows1;
    int rows2;
    int cols1;
    int cols2;

    rows1 = input1->get_rows();
    rows2 = input2->get_rows();
    cols1 = input1->get_cols();
    cols2 = input2->get_cols();
    if (rows1 != rows2 || cols1 != cols2) {
        std::ostringstream os;
        os << "input1 size (" << rows1 << ", " << cols1 << ") not the same as input2 size ("
                << rows2 << ", " << cols2 << ")";
        errors.add("Operator_transform_image_combine::run", "", os.str());
    }
    Image *output = nullptr;
    if (!errors.has_error()) {
        output = new Image(rows1, cols1, 1, Image_depth::CV_32F);
        for (int row = 0; row < rows1; row++)
            for (int col = 0; col < cols1; col++) {
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
    if (get_depth() == Image_depth::CV_8U &&
        image->get_depth() == Image_depth::CV_32S) {
        errors.add("Image::copy", "", "cannot copy CV_32S image to CV_8U image ");
        return;
    }
    if (get_depth() == Image_depth::CV_8U &&
        image->get_depth() == Image_depth::CV_32F) {
        errors.add("Image::copy", "", "cannot copy CV_32F image to CV_8U image ");
        return;
    }
    if (get_depth() == Image_depth::UNDEFINED
        || image->get_depth() == Image_depth::UNDEFINED) {
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
    if (component > get_components()) {
        std::cout << "Image::draw_line_segment: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
#endif
    for (Point point: line_segment.line_points) {
        set(point, value, component);
    }
}

void Image::draw_line_segment(int row1, int col1, int row2, int col2, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::draw_line_segment: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
#endif
    Line_segment line_segment(row1, col1, row2, col2);
    for (Point point: line_segment.line_points) {
        set(point, value, component);
    }
}

void Image::draw_line_segments(const std::list<Line_segment> &line_segments, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::draw_line_segments: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
#endif
    for (const Line_segment &line_segment: line_segments) {
        draw_line_segment(line_segment, value, component);
    }
}

void Image::draw_rectangle(int row1, int col1, int row2, int col2, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::draw_rectangle: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
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
    if (component > get_components()) {
        std::cout << "Image::draw_rectangle_filled: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
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
    if (component > get_components()) {
        std::cout << "Image::get: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return 0.0;
    }
#endif
    int index;
    switch (get_depth()) {
        case Image_depth::CV_8U:
            index = row_col_to_index(row, col, component);
            return buf_8U[index];

        case Image_depth::CV_32S:
            index = row_col_to_index(row, col, component);
            return static_cast<pixel_32F>(buf_32S[index]);

        case Image_depth::CV_32F:
            index = row_col_to_index(row, col, component);
            return buf_32F[index];

        default:
            return 0.0;
    }
}

double Image::get(const Point &point, const int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::get: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return 0.0;
    }
#endif
    return get(point.row, point.col, component);
}

auto Image::get_8U(const int row, const int col, const int component) const -> pixel_8U {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::get_8U: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return 0.0;
    }
#endif
    int index = row_col_to_index(row, col, component);
    return buf_8U[index];
}

auto Image::get_32F(const int row, const int col, const int component) const -> pixel_32F {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::get_32F: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return 0.0;
    }
#endif
    int index = row_col_to_index(row, col, component);
    return buf_32F[index];
}

pixel_32S Image::get_32S(const int row, const int col, const int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::get_32S: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return 0.0;
    }
#endif
    int index = row_col_to_index(row, col, component);
    return buf_32S[index];
}

int Image::get_cols() const { return image_header.cols; }

int Image::get_components() const { return image_header.components; }

Image_depth Image::get_depth() const { return image_header.depth; }

int Image::get_npixels() const { return image_header.npixels; }

int Image::get_row_stride() const { return image_header.row_stride; }

int Image::get_rows() const { return image_header.rows; }

double Image::get_scaled(int row, int col, double lower_in,
                         double upper_in, double lower_out,
                         double upper_out, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::get_scaled: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return 0.0;
    }
#endif
    double pixel_in = get(row, col, component);
    double pixel_out = scale_pixel(pixel_in, lower_in,
                                   upper_in, lower_out, upper_out);
    return pixel_out;
}

/*
void Image::get_stats(Variance_stats &stats) const {
  for (int row = 0; row < get_rows(); row++) {
    for (int col = 0; col < get_cols(); col++) {
      double value = get(row, col);
      stats.update(value);
    }
  }
}
*/

void Image::init(double value) {
    int size = get_npixels();;
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

bool Image::is_color() const {
    return get_components() == 3;
}

bool Image::is_grayscale() const {
    return get_components() == 1;
}

void Image::log(std::list<WB_log_entry> &log_entries) const {
    Variance_stats stats;
    //get_stats(stats);
    WB_log_entry log_entry_rows("rows", wb_utils::int_to_string(get_rows()));
    log_entries.push_back(log_entry_rows);
    WB_log_entry log_entry_cols("cols", wb_utils::int_to_string(get_cols()));
    log_entries.push_back(log_entry_cols);
    WB_log_entry log_entry_components("components", wb_utils::int_to_string(get_components()));
    log_entries.push_back(log_entry_components);
    WB_log_entry log_entry_depth("depth", WB_image_depth::to_string(get_depth()));
    log_entries.push_back(log_entry_depth);
    WB_log_entry log_entry_count("pixel count", wb_utils::int_to_string(get_npixels()));
    log_entries.push_back(log_entry_count);
    WB_log_entry log_entry_mean("pixel mean", wb_utils::double_to_string(stats.mean));
    log_entries.push_back(log_entry_count);
    WB_log_entry
            log_entry_standard_deviation("pixel standard deviation",
                                         wb_utils::double_to_string(stats.standard_deviation));
    log_entries.push_back(log_entry_standard_deviation);
    WB_log_entry log_entry_min_value("min pixel value", wb_utils::double_to_string(stats.bounds.min_value));
    log_entries.push_back(log_entry_min_value);
    WB_log_entry log_entry_max_value("max pixel value", wb_utils::double_to_string(stats.bounds.max_value));
    log_entries.push_back(log_entry_max_value);
}

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
            wb_utils::read_byte_buffer(fp,
                                       image->buf_8U,
                                       image->get_npixels(),
                                       "Image::read",
                                       "",
                                       "cannot read 8U image data",
                                       errors);
            if (errors.has_error()) {
                delete image;
                return nullptr;
            }
            break;

        case Image_depth::CV_32S:
            wb_utils::read_int_buffer(fp,
                                      image->buf_32S,
                                      image->get_npixels(),
                                      "Image::read",
                                      "",
                                      "cannot read 32S image data",
                                      errors);
            if (errors.has_error()) {
                delete image;
                return nullptr;
            }
            break;

        case Image_depth::CV_32F:
            wb_utils::read_float_buffer(fp,
                                        image->buf_32F,
                                        image->get_npixels(),
                                        "Image::read",
                                        "",
                                        "cannot read 32F image data",
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
    auto *image =
            new Image(cinfo.output_height, cinfo.output_width, cinfo.num_components, Image_depth::CV_8U);
    /* Make a one-row-high sample array that will go away when done with image */
    buffer = (*cinfo.mem->alloc_sarray)
            (reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE, image->get_row_stride(), 1);
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
    int rows = 0;
    int cols = 0;
    bool first = true;
    std::string line;
    std::vector<std::vector<std::string> > lines;
    while (getline(ifs, line)) {
        std::vector<std::string> values = wb_utils::string_split(line);
        if (first) {
            first = false;
            cols = values.size();
            lines.push_back(values);
        } else if (values.size() != cols) {
            std::ostringstream os;
            os << "invalid image file: initial column length " << cols
                    << " row " << rows << " column length " << values.size();
            errors.add("Image::read_text", "", os.str());
            return nullptr;
        } else {
            lines.push_back(values);
        }
        rows++;
    }
    auto *image = new Image(rows, cols, 1, Image_depth::CV_32S);
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

int Image::row_col_to_index(int row, int col, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::row_col_to_index: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return 0;
    }
#endif
    assert(row >= 0 && row < get_rows() && col >= 0 && col < get_cols());
    return row * get_row_stride() + col * image_header.components + component;
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
Image *Image::scale_image(const Image *image, double lower_in,
                          double upper_in, double lower_out,
                          double upper_out, Image_depth depth, int component) {
    if (debug)
        std::cout << "Image *Image::scale_image: lower_in " << lower_in
                << " upper_in " << upper_in
                << " lower_out " << lower_out
                << " upper_out " << upper_out << " depth " << WB_image_depth::to_string(depth) << std::endl;
#ifdef IMAGE_COMPONENT_CHECK
    if (component > image->get_components()) {
        std::cout << "Image::scale_image: component " << component << " too large (" <<
                wb_utils::int_to_string(image->get_components()) << ")" << std::endl;
        return nullptr;
    }
#endif
    auto *convert_image = new Image(image->get_rows(),
                                    image->get_cols(),
                                    image->get_components(),
                                    depth);
    for (int row = 0; row < image->get_rows(); row++) {
        for (int col = 0; col < image->get_cols(); col++) {
            double value = image->get_scaled(row, col, lower_in,
                                             upper_in, lower_out, upper_out, component);
            convert_image->set(row, col, value, component);
        }
    }
    return convert_image;
}

double Image::scale_pixel(double pixel_in,
                          double in_lower,
                          double in_upper,
                          double out_lower,
                          double out_upper) {
    Bounds in_bounds(in_lower, in_upper);
    Bounds out_bounds(out_lower, out_upper);
    double pixel_out = Bounds::map_input_to_output_bounds(pixel_in, in_bounds, out_bounds);
    return pixel_out;
}

// -> CV_8U may lose precision/overflow
void Image::set(int row, int col, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::set: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
#endif
    switch (get_depth()) {
        case Image_depth::CV_8U:
            buf_8U[row_col_to_index(row, col, component)] = wb_utils::double_to_int_round(value);
            break;

        case Image_depth::CV_32S:
            buf_32S[row_col_to_index(row, col, component)] = wb_utils::double_to_int_round(value);
            break;

        case Image_depth::CV_32F:
            buf_32F[row_col_to_index(row, col, component)] = wb_utils::double_to_float(value);
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

void Image::set(const Point &point, double value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::set: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
#endif
    set(point.row, point.col, value, component);
}

void Image::set_8U(int row, int col, pixel_8U value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::set_8U: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
#endif
    buf_8U[row_col_to_index(row, col, component)] = value;
}

void Image::set_32F(int row, int col, pixel_32F value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::set_32F: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
#endif
    buf_32F[row_col_to_index(row, col, component)] = value;
}

void Image::set_32S(int row, int col, pixel_32S value, int component) const {
#ifdef IMAGE_COMPONENT_CHECK
    if (component > get_components()) {
        std::cout << "Image::set_32S: component " << component << " too large (" <<
                wb_utils::int_to_string(get_components()) << ")" << std::endl;
        return;
    }
#endif
    buf_32S[row_col_to_index(row, col, component)] = value;
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
        errors.add("Image::write_jpeg", "", "cannot write "
                                            + WB_image_depth::to_string(get_depth())
                                            + " image");
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
    cinfo.image_width = get_cols();
    cinfo.image_height = get_rows();
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
    for (int row = 0; row < get_rows(); row++) {
        for (int col = 0; col < get_cols(); col++) {
            for (int component = 0; component < get_components(); component++) {
                double value = get(row, col, component);
                ofs << value << delim;
            }
        }
        ofs << std::endl;
    }
    ofs.close();
}
