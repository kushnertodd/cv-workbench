#ifndef SRC__IMAGE_LINE_SEGMENT_HPP_
#define SRC__IMAGE_LINE_SEGMENT_HPP_

#include <list>
#include "pixel.hpp"
#include "point.hpp"
#include "wb_log.hpp"

class Image_line_segment {

public:
    Pixel pixel1;
    Pixel pixel2;
    std::list<Pixel> line_pixels;
    Image_line_segment();
    Image_line_segment(const Pixel &m_pixel1, const Pixel &m_pixel2);
    Image_line_segment(int col1, int row1, int col2, int row2);
    void add(int col, int row);
    void add(const Pixel &pixel);
    void init(const Pixel &m_pixel1, const Pixel &m_pixel2);
    void log(std::list<WB_log_entry> &log_entries) const;
    std::string to_string() const;
};

#endif // SRC__IMAGE_LINE_SEGMENT_HPP_
