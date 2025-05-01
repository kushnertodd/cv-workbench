#include "polar_line.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include "point.hpp"
#include "polar_trig.hpp"

/**
 * initialize_image (rho, theta) line
 * @param m_rho
 * @param m_theta_index
 */
Polar_line::Polar_line(int m_rho_index, int m_theta_index) : rho_index(m_rho_index), theta_index(m_theta_index) {
    // TODO: fix
    // rho = Polar_trig::to_rho(rho_index);
    // theta = Polar_trig::to_theta(theta_index);
    // cos_t = Polar_trig::to_cos_index(theta_index);
    // sin_t = Polar_trig::to_sin_index(theta_index);
}
/**
 * @brief
 * @param m_rho_index
 * @param m_theta_index
 */
void Polar_line::init(int m_rho_index, int m_theta_index) {
    rho_index = m_rho_index;
    theta_index = m_theta_index;
    // TODO: fix
    // rho = Polar_trig::to_rho(rho_index);
    // theta = Polar_trig::to_theta(theta_index);
    // cos_t = Polar_trig::to_cos_index(theta_index);
    // sin_t = Polar_trig::to_sin_index(theta_index);
}
/**
 * @brief
 * @return
 */
std::string Polar_line::to_string() const {
    std::ostringstream os;
    os << " rho_index " << rho_index << " rho " << rho << " theta_index " << theta_index << " theta " << theta
       << " cos_t " << cos_t << " sin_t " << sin_t;
    return os.str();
}
/**
 * @brief
 * @param fp
 * @param errors
 */
void Polar_line::write(FILE *fp, Errors &errors) {
    fwrite(&rho_index, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Polar_line::write", "", "cannot write Hough rho_index");
        return;
    }
    fwrite(&theta_index, sizeof(int), 1, fp);
    if (ferror(fp) != 0) {
        errors.add("Polar_line::write", "", "cannot write Hough theta_index");
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
    ofs << theta_index << delim << rho << delim << rho_index << std::endl;
}
