#ifndef SRC__PIXEL_HPP_
#define SRC__PIXEL_HPP_
#include <string>

class Pixel {
    friend class Image;
    friend class Image_header;
    friend class Image_line_segment;
    int col{};
    int row{};

public:
    Pixel();
    Pixel(int m_col, int m_row);
    Pixel(const Pixel &pixel);
    void init(int m_col, int m_row);
    std::string to_string() const;
};

#endif // SRC__PIXEL_HPP_
