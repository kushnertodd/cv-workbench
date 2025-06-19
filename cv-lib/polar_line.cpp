#include "polar_line.hpp"
#include <cmath>
#include "pixel.hpp"
#include "polar_trig_static.hpp"
#include "wb_utils.hpp"

/**
 * @brief
 */
Polar_line::Polar_line() = default;
/**
 * @brief
 * @param m_rho
 * @param m_theta
 */
Polar_line::Polar_line(double m_rho, int m_theta) { init(m_rho, m_theta); }
/**
 * @brief
 * @return
 */
double Polar_line::get_rho() const { return rho; }
/**
 * @brief
 * @return
 */
double Polar_line::get_theta() const { return theta; }
/**
 * @brief
 * @param m_rho
 * @param m_theta
 */
void Polar_line::init(double m_rho, int m_theta) {
    rho = m_rho;
    theta = m_theta;
    cos_t = to_cos(theta);
    sin_t = to_sin(theta);
}
/**
 * @brief
 * @param theta
 * @return
 */
bool Polar_line::singular_cos() const { return singular_cos(theta); }
/**
 * @brief
 * @param theta
 * @return
 */
bool Polar_line::singular_cos(int theta) { return theta == theta_pi / 2; }
/**
 * @brief
 * @param theta
 * @return
 */
bool Polar_line::singular_sin() const { return singular_sin(theta); }
/**
 * @brief
 * @param theta
 * @return
 */
bool Polar_line::singular_sin(int theta) { return theta == 0; }
/**
 * @brief
 * @param theta
 * @return
 */
double Polar_line::to_cos(int theta) { return polar_cos[theta]; }
/**
 * @brief
 * @param theta
 * @return
 */
double Polar_line::to_sin(int theta) { return polar_sin[theta]; }
/**
 * @brief
 * @return
 */
std::string Polar_line::to_string() const {
    std::ostringstream os{};
    os << "rho=" << rho << " theta=" << theta << " cos_t=" << cos_t << " sin_t=" << sin_t;
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
/**
 * can have a singularity if theta ~= 180, sin ~= 0
 * @brief
 * @param rho
 * @param theta
 * @param x
 * @return
 */
double Polar_line::x_to_y(double x) const {
    assert(!singular_sin(theta));
    double y = (rho - x * cos_t) / sin_t;
    return y;
}

/**
 * can have a singularity if theta ~= 90, cos ~= 0
 * @brief
 * @param rho
 * @param theta
 * @param y
 * @return
 */
double Polar_line::y_to_x(double y) const {
    assert(!singular_cos(theta));
    double x = (rho - y * sin_t) / cos_t;
    return x;
}
