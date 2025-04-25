//
// Created by kushn on 6/27/2022.
//

#include "pixel.hpp"
#include <sstream>

Pixel::Pixel() = default;
Pixel::Pixel(int m_col, int m_row) : row(m_row), col(m_col) {}
Pixel::Pixel(const Pixel &pixel) : Pixel::Pixel(pixel.row, pixel.col) {}

Pixel::init(int m_col, int m_row) {
    col = m_col;
    row = m_row;
}
std::string Pixel::to_string() const {
    std::ostringstream os;
    os << "col " << col << " row " << row;
    return os.str();
}
