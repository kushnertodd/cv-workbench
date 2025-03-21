//
// Created by kushn on 6/14/2022.
//

#include <iomanip>
#include <iostream>
#include "wb_utils.hpp"
#include "image_header.hpp"

extern bool debug;

Image_header::Image_header() = default;

/**
 * 
 * @param m_rows 
 * @param m_cols 
 * @param m_components 
 * @param m_depth 
 */
Image_header::Image_header(const int m_rows, const int m_cols, const int m_components,
                           const Image_depth m_depth) : rows(m_rows),
                                                        cols(m_cols),
                                                        components(m_components),
                                                        row_stride(cols * components),
                                                        depth(m_depth),
                                                        npixels(rows * row_stride) {
    if (debug)
        std::cout << "Image_header::Image_header: " << to_string() << std::endl;
}

Image_header::Image_header(const Image_header &image_header) : Image_header(image_header.rows,
                                                                            image_header.cols,
                                                                            image_header.components,
                                                                            image_header.depth) {
}

void Image_header::read(FILE *fp, Errors &errors) {
    wb_utils::read_int(fp, rows, "Image_header::read_header", "", "missing image rows", errors);
    if (!errors.has_error())
        wb_utils::read_int(fp, cols, "Image_header::read_header", "", "missing image cols", errors);
    if (!errors.has_error())
        wb_utils::read_int(fp,
                           components,
                           "Image_header::read_header",
                           "",
                           "missing image components",
                           errors);
    if (!errors.has_error()) {
        int depth_int;
        wb_utils::read_int(fp,
                           depth_int,
                           "Image_header::read_header",
                           "",
                           "missing image depth",
                           errors);
        if (!errors.has_error())
            depth = static_cast<Image_depth>(depth_int);
    }
}

void Image_header::write(FILE *fp, Errors &errors) const {
    fwrite(&rows, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Image_header::write_header", "", "cannot write image rows");
        return;
    }
    fwrite(&cols, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Image_header::write_header", "", "cannot write image cols");
        return;
    }
    fwrite(&components, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Image_header::write_header", "", "cannot write image components");
        return;
    }
    fwrite(&depth, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Image_headerZZ::write_header", "", "cannot write image depth");
        return;
    }
}

std::string Image_header::to_string(const std::string &prefix) const {
    std::ostringstream os;
    os << prefix << std::setw(20) << std::left << "rows " << rows << std::endl
            << prefix << std::setw(20) << std::left << "cols " << cols << std::endl
            << prefix << std::setw(20) << std::left << "components " << components << std::endl
            << prefix << std::setw(20) << std::left << "depth " << WB_image_depth::to_string(depth) << std::endl
            << prefix << std::setw(20) << std::left << "row_stride " << row_stride << std::endl
            << prefix << std::setw(20) << std::left << "npixels " << npixels << std::endl;
    return os.str();
}
