#include "pixel.hpp"
#include <sstream>

Pixel::Pixel() = default;
Pixel::Pixel(int m_col, int m_row) : col(m_col), row(m_row) {}
Pixel::Pixel(const Pixel &pixel) : Pixel::Pixel(pixel.col, pixel.row) {}

/**
 * @brief
 * @param m_col
 * @param m_row
 */
void Pixel::init(int m_col, int m_row) {
    col = m_col;
    row = m_row;
}
/**
 * @brief
 * @return
 */
std::string Pixel::to_string() const {
    std::ostringstream os{};
    os << "col " << col << " row " << row;
    return os.str();
}
void Pixel::translate(int m_col, int m_row) {
    col += m_col;
    row += m_row;
}
