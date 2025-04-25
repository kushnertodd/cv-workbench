//
// Created by kushn on 6/27/2022.
//

#ifndef SRC__POLAR_LINE_HPP_
#define SRC__POLAR_LINE_HPP_

#include <fstream>
#include "pixel.hpp"

class Polar_line {
    friend class WB_window;
    int rho_index{};
    double rho{};
    int theta_index{};
    int count{};
    double cos_theta{};
    double sin_theta{};

public:
    Polar_line(int m_rho_index, double m_rho, int m_theta_index,
               double m_cos_theta, double m_sin_theta, int m_count);

    void set(int m_rho_index, double m_rho, int m_theta_index,
             double m_cos_theta, double m_sin_theta, int m_count);

    std::string to_string() const;

    void write(FILE *fp, Errors &errors);

    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};
#endif //SRC__POLAR_LINE_HPP_
