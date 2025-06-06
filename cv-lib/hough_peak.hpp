#ifndef CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_
#define CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_

#include <fstream>
#include <string>
#include "errors.hpp"

class Hough_peak {
public:
    double count_percentile;
    double rho;
    int theta;
    Hough_peak(double m_count_percentile, double m_rho, int m_theta);
    static bool comp(Hough_peak &x, Hough_peak &y);
    std::string to_string() const;
    void write(FILE *fp, Errors &errors) const;
    void write_text(std::ofstream &ofs, const std::string &delim, Errors &errors) const;
};

#endif // CV_WORKBENCH_SRC_HOUGH_PEAK_HPP_
