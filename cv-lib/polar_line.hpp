#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include <fstream>
#include "errors.hpp"

/**
 * @brief
 */
class Polar_line {
    double rho{};
    int theta{};
    double cos_t{};
    double sin_t{};

public:
    Polar_line(double m_rho, int m_theta);
    double get_rho() const;
    double get_theta() const;
    void init(double m_rho, int m_theta);
    std::string to_string() const;
    void write(FILE *fp, Errors &errors) const;
    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};
#endif // SRC__POLAR_LINE_HPP_
