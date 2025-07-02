#include <cstring>
#include <iomanip>
#include <iostream>
#include "errors.hpp"
#include "hough.hpp"

extern bool debug;

Hough_peak::Hough_peak(double m_count_percentile, double m_rho, int m_theta) :
    count_percentile(m_count_percentile), rho(m_rho), theta(m_theta) {}
std::string Hough_peak::to_string() const {
    std::ostringstream os{};
    os << "count_percentile=" << count_percentile << " rho=" << rho << " theta=" << theta;
    return os.str();
}
bool Hough_peak::comp(Hough_peak &x, Hough_peak &y) { return x.count_percentile > y.count_percentile; }
/**
 * @brief
 * @param fp
 * @param errors
 */
void Hough_peak::write(FILE *fp, Errors &errors) const {
    wb_utils::write_double(fp, count_percentile, "Hough_peak::write", "", "cannot write Hough peak count_percentile",
                           errors);
    if (!errors.has_error())
        wb_utils::write_double(fp, rho, "Hough_peak::write", "", "cannot write Hough peak rho", errors);
    if (!errors.has_error())
        wb_utils::write_int(fp, theta, "Hough_peak::write", "", "cannot write Hough peak theta", errors);
}
/**
 * @brief
 * @param ofs
 * @param delim
 * @param errors
 */
void Hough_peak::write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const {
    ofs << std::fixed << std::setprecision(1) << rho << delim << theta << delim << count_percentile << std::endl;
}
