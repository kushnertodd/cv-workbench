#include "polar_line.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include "point.hpp"
#include "polar_trig.hpp"

/**
 * initialize_image (rho, theta) line
 * @param m_rho
 * @param m_theta
 */
Polar_line::Polar_line(double m_rho, int m_theta) { init(m_rho, m_theta); }
/**
 * @brief
 * @param m_rho
 * @param m_theta
 */
void Polar_line::init(double m_rho, int m_theta) {
    rho = m_rho;
    theta = m_theta;
    cos_t = Polar_trig::to_cos(theta);
    sin_t = Polar_trig::to_sin(theta);
}
/**
 * @brief
 * @return
 */
std::string Polar_line::to_string() const {
    std::ostringstream os;
    os << " rho " << rho << " theta " << theta << " cos_t " << cos_t << " sin_t " << sin_t;
    return os.str();
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Polar_line::write(FILE *fp, Errors &errors) const {
    fwrite(&rho, sizeof(double), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Polar_line::write", "", "cannot write Hough rho");
        return;
    }
    fwrite(&theta, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Polar_line::write", "", "cannot write Hough theta");
        return;
    }
}
/**
 * @brief
 * @param ofs
 * @param delim
 * @param errors
 */
void Polar_line::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
    ofs << theta << delim << rho << delim << rho << std::endl;
}
