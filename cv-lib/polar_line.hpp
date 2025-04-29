#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include <fstream>

class Polar_line {
    double rho{};
    int rho_index{};
    int theta{};
    int theta_index{};
    double cos_t{};
    double sin_t{};

public:
    Polar_line(int m_rho_index, int m_theta_index);
    void init(int m_rho_index, int m_theta_index);
    std::string to_string() const;
    void write(FILE *fp, Errors &errors);
    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};
#endif // SRC__POLAR_LINE_HPP_
