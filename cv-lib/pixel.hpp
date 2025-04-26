//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__PIXEL_HPP_
#define SRC__PIXEL_HPP_
#include <string>

class Pixel {
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
